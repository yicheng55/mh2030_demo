# DM9051 lwIP HTML Documentation

此目錄為 `docs/dm9051_lwip_adapter_analysis.md` 的可發布 HTML 文件網站輸出。

## 目錄結構

```text
docs/html_lwIP/
├─ index.html
├─ build_report.md
├─ conversion_report.md
├─ assets/
│  ├─ css/
│  │  └─ style.css
│  └─ js/
│     ├─ toc.js
│     ├─ search.js
│     ├─ theme.js
│     └─ svg_modal.js
├─ svg/
│  ├─ sequence_01.svg
│  ├─ sequence_02.svg
│  ├─ sequence_03.svg
│  ├─ sequence_04.svg
│  └─ flow_01.svg
└─ mermaid_sources/
   ├─ sequence_01.mmd
   ├─ sequence_02.mmd
   ├─ sequence_03.mmd
   ├─ sequence_04.mmd
   └─ flow_01.mmd
```

## 開啟方式

直接使用瀏覽器開啟：

- `docs/html_lwIP/index.html`

## Mermaid 轉換

若需重新轉換 SVG，可執行：

```bash
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_01.mmd -o docs/html_lwIP/svg/sequence_01.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_02.mmd -o docs/html_lwIP/svg/sequence_02.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_03.mmd -o docs/html_lwIP/svg/sequence_03.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_04.mmd -o docs/html_lwIP/svg/sequence_04.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/flow_01.mmd -o docs/html_lwIP/svg/flow_01.svg -b transparent -p docs/puppeteer-config.json
```

## 功能

- Bootstrap 5.3 版面
- 桌面固定 Sidebar、手機 Offcanvas Sidebar
- 自動 TOC（`# ## ### ####`）+ Smooth Scroll + Active Highlight
- SVG Figure Card + Modal 全螢幕 + Zoom
- highlight.js 程式碼高亮（C/C++/Bash/Makefile）
- Code Copy Button
- 前端搜尋（標題、內文、圖表標題、API）
- Light/Dark 主題切換（localStorage）
