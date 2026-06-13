<!-- gitnexus:start -->
# GitNexus — Code Intelligence

This project is indexed by GitNexus as **mh2030_demo** (24441 symbols, 38661 relationships, 300 execution flows). Use the GitNexus MCP tools to understand code, assess impact, and navigate safely.

> Index stale? Run `node .gitnexus/run.cjs analyze` from the project root — it auto-selects an available runner. No `.gitnexus/run.cjs` yet? `npx gitnexus analyze` (npm 11 crash → `npm i -g gitnexus`; #1939).

## Always Do

- **MUST run impact analysis before editing any symbol.** Before modifying a function, class, or method, run `impact({target: "symbolName", direction: "upstream"})` and report the blast radius (direct callers, affected processes, risk level) to the user.
- **MUST run `detect_changes()` before committing** to verify your changes only affect expected symbols and execution flows. For regression review, compare against the default branch: `detect_changes({scope: "compare", base_ref: "master"})`.
- **MUST warn the user** if impact analysis returns HIGH or CRITICAL risk before proceeding with edits.
- When exploring unfamiliar code, use `query({query: "concept"})` to find execution flows instead of grepping. It returns process-grouped results ranked by relevance.
- When you need full context on a specific symbol — callers, callees, which execution flows it participates in — use `context({name: "symbolName"})`.

## Never Do

- NEVER edit a function, class, or method without first running `impact` on it.
- NEVER ignore HIGH or CRITICAL risk warnings from impact analysis.
- NEVER rename symbols with find-and-replace — use `rename` which understands the call graph.
- NEVER commit changes without running `detect_changes()` to check affected scope.

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
| Work in the Ppp area (674 symbols) | `.claude/skills/generated/ppp/SKILL.md` |
| Work in the USER area (603 symbols) | `.claude/skills/generated/user/SKILL.md` |
| Work in the Api area (239 symbols) | `.claude/skills/generated/api/SKILL.md` |
| Work in the Http area (174 symbols) | `.claude/skills/generated/http/SKILL.md` |
| Work in the Freertos area (157 symbols) | `.claude/skills/generated/freertos/SKILL.md` |
| Work in the Snmp area (142 symbols) | `.claude/skills/generated/snmp/SKILL.md` |
| Work in the Ipv4 area (105 symbols) | `.claude/skills/generated/ipv4/SKILL.md` |
| Work in the Tcp area (76 symbols) | `.claude/skills/generated/tcp/SKILL.md` |
| Work in the Uip area (58 symbols) | `.claude/skills/generated/uip/SKILL.md` |
| Work in the Delay area (55 symbols) | `.claude/skills/generated/delay/SKILL.md` |
| Work in the Mh2030a area (52 symbols) | `.claude/skills/generated/mh2030a/SKILL.md` |
| Work in the Lwiperf area (48 symbols) | `.claude/skills/generated/lwiperf/SKILL.md` |
| Work in the Mdns area (44 symbols) | `.claude/skills/generated/mdns/SKILL.md` |
| Work in the Netif area (33 symbols) | `.claude/skills/generated/netif/SKILL.md` |
| Work in the Bsp area (31 symbols) | `.claude/skills/generated/bsp/SKILL.md` |
| Work in the Smtp area (31 symbols) | `.claude/skills/generated/smtp/SKILL.md` |
| Work in the Include area (30 symbols) | `.claude/skills/generated/include/SKILL.md` |
| Work in the Mqtt area (29 symbols) | `.claude/skills/generated/mqtt/SKILL.md` |
| Work in the Develop area (28 symbols) | `.claude/skills/generated/develop/SKILL.md` |
| Work in the Tcp_ area (27 symbols) | `.claude/skills/generated/tcp-2/SKILL.md` |

<!-- gitnexus:end -->
