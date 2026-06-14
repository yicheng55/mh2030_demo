# MH2030 Demo 專案結構與目標總覽

報告產出日期：2026-06-14

專案根部：C:\Users\user1.DESKTOP-NPR7KBV\mh2030_demo

---

## 1 專案屬性與目的

- 平台：MH2030A MCU
- 核心：DM9051A SPI 乙太網路驅動
- 通訊協議展示：uIP / lwIP 雙版本
- 工具鏈：Keil MDK（大量 .uvprojx / .uvoptx）
- 類型：教學 / 模組展示 / 周邊範例整合專案

---

## 2 頂層目錄結構

- drivers/：DM9051 舊版 beta driver（v1.6.1a_beta）
- ModuleDemo/：MH2030A 周邊範例、DM9051A 驅動、Keil 專案（主要開發區域）
- middlewares/：第三方協議 Stack（目前為 lwip-2.1.2）
- apps/：uIP + DM9051 乙太網路應用範例
- Libraries/：CMSIS / CORE / MH20xxLib
- tools/keil/：Keil 專案校驗工具（validate-dm9051-targets.ps1）
- docs/：硬體 schematic PDF 與記憶體位址圖
- .gitnexus/：GitNexus 索引設定（run.cjs）

---

## 3 ModuleDemo/DM9051A 內部結構

- USER/：Keil 專案入口、main.c 與組態檔
- bsp/：舊式 BSP/dm9051 封裝
- dm9051_driver/：重構中的新分層驅動
  - core/inc + core/src：DM9051 晶片核心邏輯
  - hal/inc：HAL vtable 定義
  - ports/mh2030a/：平台移植（SPI1/DMA/IRQ）
  - adapters/lwip/ / adapters/uip/：上層 protocol stack 適配
  - examples/：uIP與lwIP範例程式
- port/：舊版 HAL / adapter 實作（尚未完全取代）
- SYSTEM/：delay 等系統共用程式
- OBJ / OBJ_LWIP / OBJ_UIP / OBJ_UIP_INT/：Keil 編譯輸出資料夾

---

## 4 DM9051 驅動：關鍵兩套並存（重點）

| 版本 | 路徑 | 設計風格 |
|------|------|----------|
| 舊版 | drivers/dm9051_edriver_v1.6.1a_beta | 集中式架構 |
| 新版 | ModuleDemo/DM9051A/dm9051_driver | 分層架構 |

新版已按 Core -> HAL -> Adapter -> Stack 分層，但新版 port/ 與舊 port/ 尚未完全整合。

---

## 5 Keil 專案對照

- DM9051A.uvprojx：純 DM9051 功能測試
- DM9051A_uip.uvprojx：uIP + DM9051 整合
- DM9051A_lwip.uvprojx：lwIP + DM9051 整合

---

## 6 語言與技術組成統計

- C 原始檔：.c = 469
- Header：.h = 493
- Keil 專案：.uvprojx = 54
- Keil 選項：.uvoptx/.uvopt = 19
- Makefile：2
- 組合語言：.s = 4
- 編譯產物：.o/.map/.axf/.hex/.d/.crf/.lnp/.dep/.lst 等大量存在
- 文件與網頁資源：.md/.json/.html 數十個

---

## 7 高層級相依關係

DM9051A 網路範例
- apps/uip_dm9051_example_e1
  - 上層：uIP stack
  - 下層：ModuleDemo/DM9051A/dm9051_driver/adapters/uip
  - 底層：ports/mh2030a 或 hal binding
- ModuleDemo/DM9051A/dm9051_driver/examples/
  - uip_mh2030a_demo
  - lwip_mh2030a_demo（依賴 middlewares/3rd_party/lwip-2.1.2）

---

## 8 已知 Open Items / 重構議題（來自文件）

- 目標架構（Core->HAL->Adapter->Stack）已定義，但尚未完全完成。
- 兩個 DM9051 driver 並存，可能造成 include 路徑衝突。
- 多個 main 進入點，需釐清標準流程。
- 舊 port/ 與新 ports/mh2030a/ 可能需要合併。
- Keil 專案中的 Include Path、Source Group 需配合新目錄結構更新。

---

## 9 後續可能分析路徑

- 逐層追蹤 DM9051 的呼叫圖（core -> hal -> spi -> main loop）
- 比對兩套 driver 的實際重疊度（哪些函式在舊版/新版都出現）
- 拆解 uIP / lwIP adapter 細節，提出最小風險的 lwIP 接入手冊
- 整理出 GitNexus MCP 應優先 impact 分析的符號清單
