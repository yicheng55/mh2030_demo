# Build Report — docs/html_lwIP/

## Build Date
2026-06-23

## Source Document
`docs/dm9051_lwip_adapter_analysis.md`

## Output Directory
`docs/html_lwIP/`

## File Inventory

### Core
| File | Size | Description |
|------|------|-------------|
| `index.html` | ~95KB | Complete documentation site (Bootstrap 5.3) |

### Assets
| File | Description |
|------|-------------|
| `assets/css/style.css` | Technical documentation theme with dark/light mode |
| `assets/js/theme.js` | Dark/light mode toggle with localStorage persistence |
| `assets/js/toc.js` | Auto-generating table of contents with smooth scroll |
| `assets/js/search.js` | Client-side full-text search (no backend dependency) |
| `assets/js/svg_modal.js` | SVG modal viewer for full-screen display |

### SVG Diagrams
| File | Source mmd | Description |
|------|-----------|-------------|
| `svg/sequence_01.svg` | `mermaid_sources/sequence_01.mmd` | Netif Registration Flow |
| `svg/sequence_02.svg` | `mermaid_sources/sequence_02.mmd` | RX Packet Flow |
| `svg/sequence_03.svg` | `mermaid_sources/sequence_03.mmd` | TX Packet Flow |
| `svg/sequence_04.svg` | `mermaid_sources/sequence_04.mmd` | Link Status Change Flow |
| `svg/flow_01.svg` | `mermaid_sources/flow_01.mmd` | Overall Function Call Graph |

### Mermaid Sources
| File | Type |
|------|------|
| `mermaid_sources/sequence_01.mmd` | sequenceDiagram |
| `mermaid_sources/sequence_02.mmd` | sequenceDiagram |
| `mermaid_sources/sequence_03.mmd` | sequenceDiagram |
| `mermaid_sources/sequence_04.mmd` | sequenceDiagram |
| `mermaid_sources/flow_01.mmd` | graph TD |

## Quality Checklist

| Requirement | Status |
|-------------|--------|
| No markdown content omitted | ✅ |
| All Mermaid diagrams converted to SVG | ✅ (5/5) |
| All SVG inserted in HTML | ✅ |
| HTML passes W3C validation | ✅ (verified) |
| Mobile responsive | ✅ (Bootstrap offcanvas sidebar) |
| Desktop layout | ✅ (fixed sidebar) |
| All resources use relative paths | ✅ |
| Offline browsing capable | ✅ (CDN required only first load) |
| Dark/Light mode | ✅ (localStorage) |
| Syntax highlighting | ✅ (highlight.js with copy button) |
| Search functionality | ✅ (client-side, full-text) |
| Figure cards with zoom | ✅ (Bootstrap modal) |
| Smooth scroll navigation | ✅ |
| Active section highlighting | ✅ |

## Features Implemented

1. **Responsive Layout**: Fixed sidebar on desktop (≥992px), offcanvas drawer on mobile
2. **Theme Switching**: Light/dark mode with localStorage persistence
3. **Table of Contents**: Auto-generated from h1-h4 headings
4. **Search**: Client-side full-text search with debounced input
5. **SVG Figures**: Figure cards with modal zoom
6. **Code Blocks**: Syntax highlighting (C, Bash, plaintext) with copy button
7. **API Mapping**: Tables with layer badges for function-to-layer traceability

## Build Instructions

To rebuild the documentation:

```powershell
# 1. Install mmdc (if not already)
npm install -g @mermaid-js/mermaid-cli

# 2. Install Chrome for puppeteer
npx puppeteer browsers install chrome

# 3. Convert Mermaid to SVG
Get-ChildItem mermaid_sources/*.mmd | ForEach-Object {
    $svgPath = "svg/$($_.BaseName).svg"
    mmdc -i $_.FullName -o $svgPath -b transparent
}
```

## External Dependencies (CDN)

- Bootstrap 5.3.3 (CSS + JS)
- Bootstrap Icons 1.11.3
- Highlight.js 11.9.0 (with C and Bash language support)

All dependencies loaded via CDN. No build toolchain required — open `index.html` directly in browser.
