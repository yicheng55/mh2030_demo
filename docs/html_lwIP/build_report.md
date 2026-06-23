# Build Report

## Scope

- Input: `docs/dm9051_lwip_adapter_analysis.md`
- Output root: `docs/html_lwIP/`
- Output website entry: `docs/html_lwIP/index.html`

## Build Steps Executed

1. 建立輸出目錄：`assets/css`、`assets/js`、`svg`、`mermaid_sources`
2. 從來源 Markdown 抽取 5 個 Mermaid 區塊到 `mermaid_sources/*.mmd`
3. 使用 `mmdc` 將 5 個 `.mmd` 全部轉為 `svg/*.svg`
4. 將原始 Markdown 全量轉成 HTML（不修改原始文件）
5. 以 Figure Card 置換 Mermaid 區塊，加入 SVG modal/zoom
6. 加入 TOC、搜尋、主題切換、highlight.js、Copy 按鈕
7. 新增 API Mapping Table 到頁面內文

## Self Check

- [x] 不覆蓋來源 Markdown
- [x] 所有 Mermaid 均有 `.mmd` 原始碼
- [x] 所有 Mermaid 均成功轉為 SVG
- [x] 所有 SVG 均已插入 `index.html`（Figure Card）
- [x] 桌面版固定 Sidebar
- [x] 手機版 Bootstrap Offcanvas Sidebar
- [x] 支援 `# ## ### ####` TOC、Smooth Scroll、Active Highlight
- [x] 支援 Light / Dark 主題切換並保存到 `localStorage`
- [x] 支援 C/C++/Bash/Makefile 程式碼高亮與 Copy
- [x] 所有本地資源使用相對路徑
- [x] HTML 結構檢查通過（`npx html-validate docs/html_lwIP/index.html`）

## Notes

- Bootstrap 與 highlight.js 使用 CDN 載入（符合需求）。
- 離線瀏覽時若外網不可用，CDN 資源可能無法載入；本地 HTML 內容與 SVG 仍可開啟。

## Commands Used

```bash
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_01.mmd -o docs/html_lwIP/svg/sequence_01.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_02.mmd -o docs/html_lwIP/svg/sequence_02.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_03.mmd -o docs/html_lwIP/svg/sequence_03.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/sequence_04.mmd -o docs/html_lwIP/svg/sequence_04.svg -b transparent -p docs/puppeteer-config.json
npx --yes @mermaid-js/mermaid-cli -i docs/html_lwIP/mermaid_sources/flow_01.mmd -o docs/html_lwIP/svg/flow_01.svg -b transparent -p docs/puppeteer-config.json
```
