#!/usr/bin/env python3
"""
Convert all Mermaid code blocks in a Markdown file to SVG files.

Usage:
    python mermaid_to_svg.py <input.md> [output_dir]

Requirements:
    npm install -g @mermaid-js/mermaid-cli
"""

import re
import os
import sys
import subprocess
import tempfile
import json
import shutil

def find_mermaid_blocks(md_content):
    """Find all ```mermaid ... ``` blocks and return (index, diagram_type, code) tuples."""
    pattern = re.compile(
        r'```mermaid\s*\n(.*?)```',
        re.DOTALL
    )
    blocks = []
    for i, match in enumerate(pattern.finditer(md_content)):
        code = match.group(1).strip()
        # Detect diagram type from first line
        first_line = code.split('\n')[0].strip()
        diagram_type = first_line.split()[0] if first_line else 'unknown'
        blocks.append((i, diagram_type, code))
    return blocks


def sanitize_filename(diagram_type, index):
    """Create a safe filename from diagram type and index."""
    safe_type = re.sub(r'[^a-zA-Z0-9_-]', '', diagram_type)
    return f"mermaid_{index:02d}_{safe_type}"


def main():
    if len(sys.argv) < 2:
        print("Usage: python mermaid_to_svg.py <input.md> [output_dir]")
        sys.exit(1)

    md_path = os.path.abspath(sys.argv[1])
    if not os.path.exists(md_path):
        print(f"Error: File not found: {md_path}")
        sys.exit(1)

    # Output directory: default to same dir as input
    if len(sys.argv) >= 3:
        out_dir = os.path.abspath(sys.argv[2])
    else:
        out_dir = os.path.dirname(md_path)

    os.makedirs(out_dir, exist_ok=True)

    # Puppeteer config path (same dir as script, or next to input file)
    script_dir = os.path.dirname(os.path.abspath(__file__))
    puppeteer_config = os.path.join(script_dir, 'puppeteer-config.json')
    if not os.path.exists(puppeteer_config):
        puppeteer_config = os.path.join(os.path.dirname(md_path), 'puppeteer-config.json')
    if not os.path.exists(puppeteer_config):
        print("Warning: puppeteer-config.json not found, mmdc will use default browser")

    # Read markdown
    with open(md_path, 'r', encoding='utf-8') as f:
        md_content = f.read()

    blocks = find_mermaid_blocks(md_content)
    if not blocks:
        print("No Mermaid blocks found.")
        return

    print(f"Found {len(blocks)} Mermaid block(s):\n")

    # Check mmdc is available
    mmdc_path = shutil.which('mmdc')
    if not mmdc_path:
        # Try npm global path
        npm_root = subprocess.run(
            ['npm', 'root', '-g'], capture_output=True, text=True
        ).stdout.strip()
        mmdc_path = os.path.join(npm_root, '@mermaid-js', 'mermaid-cli', 'node_modules', '.bin', 'mmdc')
        if not os.path.exists(mmdc_path):
            mmdc_path = os.path.join(npm_root, '.bin', 'mmdc')
        if not os.path.exists(mmdc_path):
            print("Error: mmdc not found. Install with: npm install -g @mermaid-js/mermaid-cli")
            sys.exit(1)

    print(f"Using mmdc: {mmdc_path}\n")

    results = []

    for idx, diagram_type, code in blocks:
        name = sanitize_filename(diagram_type, idx)
        svg_path = os.path.join(out_dir, f"{name}.svg")
        mmd_path = os.path.join(out_dir, f"{name}.mmd")

        # Write temporary .mmd file
        with open(mmd_path, 'w', encoding='utf-8') as f:
            f.write(code)

        # Build mmdc command
        cmd = [mmdc_path, '-i', mmd_path, '-o', svg_path, '-b', 'transparent']
        if os.path.exists(puppeteer_config):
            cmd.extend(['-p', puppeteer_config])

        print(f"[{idx+1}/{len(blocks)}] Converting: {name}")
        print(f"    Type: {diagram_type}")
        print(f"    Input:  {mmd_path}")
        print(f"    Output: {svg_path}")

        try:
            result = subprocess.run(
                cmd, capture_output=True, text=True, timeout=60
            )
            if result.returncode == 0:
                svg_size = os.path.getsize(svg_path)
                print(f"    ✅ Done! ({svg_size} bytes)")
                results.append((idx, name, svg_path, True, None))
            else:
                error_msg = result.stderr.strip() or result.stdout.strip()
                print(f"    ❌ Failed: {error_msg[:200]}")
                results.append((idx, name, svg_path, False, error_msg))
        except subprocess.TimeoutExpired:
            print(f"    ❌ Timeout (60s)")
            results.append((idx, name, svg_path, False, "Timeout"))
        except Exception as e:
            print(f"    ❌ Error: {e}")
            results.append((idx, name, svg_path, False, str(e)))

        # Clean up .mmd temp file
        try:
            os.remove(mmd_path)
        except OSError:
            pass

        print()

    # Summary
    success_count = sum(1 for r in results if r[3])
    fail_count = len(results) - success_count
    print("=" * 50)
    print(f"Summary: {success_count} succeeded, {fail_count} failed out of {len(results)} total")
    if fail_count > 0:
        print("\nFailed blocks:")
        for idx, name, svg_path, ok, err in results:
            if not ok:
                print(f"  - {name}: {err[:100] if err else 'Unknown error'}")

    # Generate markdown snippet for embedding SVGs
    print("\n" + "=" * 50)
    print("Markdown embed snippets:\n")
    for idx, name, svg_path, ok, _ in results:
        if ok:
            rel_path = os.path.relpath(svg_path, os.path.dirname(md_path))
            print(f"  ![Mermaid {idx+1}]({rel_path})")


if __name__ == '__main__':
    main()