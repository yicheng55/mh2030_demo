<!-- gitnexus:start -->
# GitNexus — Code Intelligence

This project is indexed by GitNexus as **mh2030_demo** (12614 symbols, 19286 relationships, 300 execution flows). Use the GitNexus MCP tools to understand code, assess impact, and navigate safely.

> If any GitNexus tool warns the index is stale, run `npx gitnexus analyze` in terminal first.

## Always Do

- **MUST run impact analysis before editing any symbol.** Before modifying a function, class, or method, run `gitnexus_impact({target: "symbolName", direction: "upstream"})` and report the blast radius (direct callers, affected processes, risk level) to the user.
- **MUST run `gitnexus_detect_changes()` before committing** to verify your changes only affect expected symbols and execution flows.
- **MUST warn the user** if impact analysis returns HIGH or CRITICAL risk before proceeding with edits.
- When exploring unfamiliar code, use `gitnexus_query({query: "concept"})` to find execution flows instead of grepping. It returns process-grouped results ranked by relevance.
- When you need full context on a specific symbol — callers, callees, which execution flows it participates in — use `gitnexus_context({name: "symbolName"})`.

## Never Do

- NEVER edit a function, class, or method without first running `gitnexus_impact` on it.
- NEVER ignore HIGH or CRITICAL risk warnings from impact analysis.
- NEVER rename symbols with find-and-replace — use `gitnexus_rename` which understands the call graph.
- NEVER commit changes without running `gitnexus_detect_changes()` to check affected scope.

## Resources

| Resource | Use for |
|----------|---------|
| `gitnexus://repo/mh2030_demo/context` | Codebase overview, check index freshness |
| `gitnexus://repo/mh2030_demo/clusters` | All functional areas |
| `gitnexus://repo/mh2030_demo/processes` | All execution flows |
| `gitnexus://repo/mh2030_demo/process/{name}` | Step-by-step execution trace |

## CLI

| Task | Read this skill file |
|------|---------------------|
| Understand architecture / "How does X work?" | `.claude/skills/gitnexus/gitnexus-exploring/SKILL.md` |
| Blast radius / "What breaks if I change X?" | `.claude/skills/gitnexus/gitnexus-impact-analysis/SKILL.md` |
| Trace bugs / "Why is X failing?" | `.claude/skills/gitnexus/gitnexus-debugging/SKILL.md` |
| Rename / extract / split / refactor | `.claude/skills/gitnexus/gitnexus-refactoring/SKILL.md` |
| Tools, resources, schema reference | `.claude/skills/gitnexus/gitnexus-guide/SKILL.md` |
| Index, status, clean, wiki CLI commands | `.claude/skills/gitnexus/gitnexus-cli/SKILL.md` |
| Work in the USER area (578 symbols) | `.claude/skills/generated/user/SKILL.md` |
| Work in the Freertos area (157 symbols) | `.claude/skills/generated/freertos/SKILL.md` |
| Work in the Delay area (54 symbols) | `.claude/skills/generated/delay/SKILL.md` |
| Work in the Uip_mh2030a area (43 symbols) | `.claude/skills/generated/uip-mh2030a/SKILL.md` |
| Work in the Bsp area (38 symbols) | `.claude/skills/generated/bsp/SKILL.md` |
| Work in the Oled area (28 symbols) | `.claude/skills/generated/oled/SKILL.md` |
| Work in the Develop area (25 symbols) | `.claude/skills/generated/develop/SKILL.md` |
| Work in the Include area (25 symbols) | `.claude/skills/generated/include/SKILL.md` |
| Work in the IOT area (20 symbols) | `.claude/skills/generated/iot/SKILL.md` |
| Work in the At24C02 area (19 symbols) | `.claude/skills/generated/at24c02/SKILL.md` |
| Work in the W25qxx area (17 symbols) | `.claude/skills/generated/w25qxx/SKILL.md` |
| Work in the AT - do area (16 symbols) | `.claude/skills/generated/at-do/SKILL.md` |
| Work in the SPI1 area (15 symbols) | `.claude/skills/generated/spi1/SKILL.md` |
| Work in the Cluster_139 area (15 symbols) | `.claude/skills/generated/cluster-139/SKILL.md` |
| Work in the At32f415_dm9051 area (13 symbols) | `.claude/skills/generated/at32f415-dm9051/SKILL.md` |
| Work in the DM area (13 symbols) | `.claude/skills/generated/dm/SKILL.md` |
| Work in the Cluster_124 area (10 symbols) | `.claude/skills/generated/cluster-124/SKILL.md` |
| Work in the Dhcpc area (10 symbols) | `.claude/skills/generated/dhcpc/SKILL.md` |
| Work in the Udp_app area (9 symbols) | `.claude/skills/generated/udp-app/SKILL.md` |
| Work in the Cluster_35 area (8 symbols) | `.claude/skills/generated/cluster-35/SKILL.md` |

<!-- gitnexus:end -->
