# Mermaid → SVG Conversion Report

## Summary

| Item | Status |
|------|--------|
| Total Mermaid diagrams in source | 5 |
| Successfully converted | 5 |
| Failed conversions | 0 |
| Conversion tool | mmdc (Mermaid CLI v11.15.0) via puppeteer chrome-headless-shell |

## Diagram Mapping

| # | File (mmd) | File (svg) | Type | Status |
|---|-----------|-----------|------|--------|
| 1 | `mermaid_sources/sequence_01.mmd` | `svg/sequence_01.svg` | sequenceDiagram | ✅ |
| 2 | `mermaid_sources/sequence_02.mmd` | `svg/sequence_02.svg` | sequenceDiagram | ✅ |
| 3 | `mermaid_sources/sequence_03.mmd` | `svg/sequence_03.svg` | sequenceDiagram | ✅ |
| 4 | `mermaid_sources/sequence_04.mmd` | `svg/sequence_04.svg` | sequenceDiagram | ✅ |
| 5 | `mermaid_sources/flow_01.mmd` | `svg/flow_01.svg` | graph TD | ✅ |

## Diagram Details

### sequence_01.mmd — Netif Registration Sequence (Section 4.3)
- Participants: main(), lwIP Stack, ethernetif.c, Core Driver, DM9051 HW
- Flow: platform_init → lwip_init → netif_add → low_level_init → dm9051_core_open → device probe → netif_set_up

### sequence_02.mmd — RX Packet Flow (Section 6.3)
- Participants: main(), ethernetif_input, low_level_input, dm9051_core_receive, DM9051 HW, lwIP Stack
- Flow: Packet arrival → SPI read → pbuf_alloc → pbuf_take → netif->input → etharp_input → tcp_input

### sequence_03.mmd — TX Packet Flow (Section 7.3)
- Participants: Application, lwIP Stack, ethernetif.c, dm9051_core_send, DM9051 HW
- Flow: tcp_write → tcp_output → etharp_output → low_level_output → dm9051_core_send → SPI write → TCR TXREQ

### sequence_04.mmd — Link Status Change Flow (Section 8.4)
- Participants: main(), ethernetif.c, dm9051_core.c, DM9051 HW, lwIP Stack
- Flow: Link poll → read NSR → netif_set_link_up/down → callback

### flow_01.mmd — Overall Function Call Graph (Section 14.1)
- Subgraphs: Application, lwIP Netif Port, lwIP TCP/IP Stack, DM9051 Core + HAL + Port
- Edges: Caller → Callee relationships across all layers

## Notes

- `tools/mermaid_to_svg.py` was not found in the repository. The conversion was performed using the equivalent `mmdc` CLI tool.
- Chrome headless shell version: 150.0.7871.24 (installed via puppeteer)
- SVG files include zoom support via the `<object>` tag in HTML
- Mermaid sources preserved in `mermaid_sources/` for future maintenance
