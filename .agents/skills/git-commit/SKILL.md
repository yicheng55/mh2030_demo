---
name: git-commit
description: 建立符合規範的 git 提交訊息，並在提交前 review 將提交的變更。優先遵循專案現有提交規範，支援 Conventional Commits 格式。使用場景：使用者要求建立提交、編寫提交訊息、提交前檢查變更
---

# Git 提交訊息

建立清晰、規範的 git 提交訊息。優先遵循專案現有風格，其次參考 Conventional Commits 標準。

## 執行流程

### 步驟 1：確定專案規範（首次）

**如果對話中已透過本技能確定過專案規範，直接複用，跳過本步驟。**

首次執行時並行收集以下資訊：

```bash
git log -5 --pretty=format:"%s"
git branch --show-current
```

同時檢查專案根目錄是否存在 commitlint 配置（`.commitlintrc.*`、`commitlint.config.*`、`package.json` 中的 `"commitlint"` 欄位）。

#### 確定提交格式規範

按優先級取第一個匹配：

1. **commitlint 配置**：找到則嚴格按其規則生成，提取 `extends`（預設）、`parserPreset`（解析模式）、`rules`（type-enum、scope-enum、header-max-length 等）
2. **提交歷史風格**：從最近 5 條提交推斷類型名稱（`feat`/`feature`）、語言（中文/英文）、issue 引用位置（subject 中/footer 中）
3. **Conventional Commits**：以上均無明確規範時使用預設標準

#### 提交類型

優先使用專案已有類型。無明確類型時參考：

| 類型 | 說明 |
|------|------|
| `feat` / `feature` | 新功能 |
| `fix` / `bugfix` | Bug 修復 |
| `docs` | 文件變更 |
| `style` | 程式碼格式（不影響功能） |
| `refactor` | 重構（功能不變） |
| `perf` | 效能最佳化 |
| `test` | 測試相關 |
| `chore` | 建置/工具鏈 |

#### 提取分支關聯的 Issue

從目前分支名中提取 issue 編號：

- `feature/#1254` → `#1254`
- `fix/123-login-blank` → `#123`
- `feat/new-feature-456` → `#456`
- `issue/789` → `#789`
- `feature/PROJ-123-desc` → `#PROJ-123`

解析到 issue 編號時，按上述確定的引用風格放置（subject 中或 footer 中）。

### 步驟 2：收集變更資料

**一次並行執行以下命令**，不要分步呼叫：

暫存區有內容時：
```bash
git status --short
git diff --cached --stat
git diff --cached
git diff --cached --check
git log @{u}..HEAD --oneline 2>/dev/null
```

暫存區為空時：
```bash
git status --short
git diff --stat
git diff
git diff --check
git log @{u}..HEAD --oneline 2>/dev/null
```

基於收集的資料一次性完成以下判斷：

#### 模組判斷

**先判斷變更目的（按提交類型分類）**：

從 diff 內容將每個檔案歸類到提交類型（feat / fix / docs / refactor / chore 等）。若出現 **不同提交類型的檔案**，視為目的不同質，強烈建議拆分提交。例如：`*.h` 的註解修正（fix）＋ 新增 `docs/*.md`（docs）→ 應拆成兩個 commit。

**再判斷業務模組（已確認目的同質後）**：

**屬於同一模組（一起提交）**：
- 同一功能的不同部分（API、型別、工具函式）
- 功能開發 + 相關文件/配置/依賴

**不相關（分開提交）**：
- 不同業務模組的變更
- 不同提交類型的變更（修復 + 文件、功能 + 重構等）
- 程式碼 + 部署/CI 配置

#### 處理邏輯

**所有變更屬於同一模組**：直接提交。

**大部分屬於同一模組，少量不相關**：
```
主要模組：使用者模組
不相關變更（建議暫不提交）：
- src/api/orders.ts (訂單模組)

跳過不相關內容，僅提交使用者模組相關變更？(y/n)
```

**多個模組變更相當**：
```
使用者模組：70行 | 訂單模組：90行
建議先提交變更較多的模組，是否僅提交訂單模組？(y/n/all)
```

#### 合併提交檢查

基於 `git log @{u}..HEAD` 結果判斷。僅在有領先遠端的本地提交時合併。合併條件：同一類型 + 相同模組檔案、同一 bug 的修復、文件連續更新。其他情況不合併。

### 步驟 3：提交前 Review

**使用者明確要求跳過 review 時（如"不 review"、"直接提交"），跳過本步驟。**

**直接複用步驟 2 已收集的 diff 資料**，不要重新執行 git diff 命令。

先判斷目前執行環境使用的 agent 及其能力，按以下優先級執行：

- **支援 subagent 的 agent**：必須啟動獨立 subagent 執行 review，避免主執行緒上下文、使用者後續追問或已有結論干擾判斷；如果 subagent 環境也支援內置 review 能力，由 subagent 優先使用內置能力。
- **不支援 subagent，但帶內置 review 能力的 agent**：使用該 agent 自帶的 review 能力檢查本次將提交的變更。
- **無內置 review 能力或無法確認能力的 agent**：直接基於步驟 2 收集的 diff 進行 review。
- **使用者明確要求使用某種 review 方式**：遵循使用者要求，同時保留下方阻塞問題處理邏輯。

優先 review 暫存區；如果沒有暫存內容，則 review 工作區變更；如果步驟 2 決定拆分提交，只 review 將納入本次提交的檔案。

#### Subagent Review 要求

使用 subagent review 時，只傳遞客觀材料：本次提交範圍、`git diff --stat`、完整 diff、相關使用者需求和本步驟檢查項。不要傳遞主執行緒的判斷結論、期望結果或提交訊息草稿。subagent 輸出應優先列出阻塞問題，其次列出非阻塞風險；無問題時明確說明未發現阻塞問題。

#### Review 檢查項

- **敏感資訊**：密碼、金鑰、token、私有憑證、真實生產憑據
- **臨時程式碼**：除錯日誌、中斷點、TODO 佔位、硬編碼測試資料
- **衝突與格式**：衝突標記、尾隨空格、縮排異常、格式化噪音
- **提交範圍**：是否混入不相關檔案、生成物、大檔案或本地環境配置
- **行為風險**：明顯的空值風險、錯誤處理缺失、破壞性變更未說明
- **測試影響**：是否需要執行或補充測試；不能執行時在結果中說明原因

#### Review 處理邏輯

**無阻塞問題**：繼續生成提交訊息，並可在回覆中簡要說明 review 通過。

**發現阻塞問題**：先停止提交，向使用者列出問題、檔案位置和建議修復方式；不要生成會掩蓋問題的提交訊息。

**發現非阻塞風險**：繼續生成提交訊息，但在回覆中提示風險和建議驗證項。

### 步驟 4：生成提交訊息

基於專案規範和變更內容生成訊息：

```
<type>(<scope>): <subject>

<body>

<footer>
```

**必需**：`type` + `subject`（10-72 字元） **可選**：`scope`、`body`、`footer`

#### Subject 規則

- 一句話精準概括，不囉嗦、不拆分描述
- 祈使句：`add` 而非 `added`
- 英文首字母小寫，中文正常大小寫
- 句尾不加標點

#### Body 規則

- **簡單變更不寫 body**：單一檔案小修改（<10 行）、純格式/拼字修正等，subject 已經足夠說明
- **以下情況建議寫 body**：
  - 新增檔案 > 50 行（解釋檔案用途、包含的主要內容）
  - 多個檔案的非簡單修改（說明變更的動機和各部分關聯）
  - 實現邏輯需補充上下文（為什麼這樣做，而非做了什麼）
  - 破壞性變更（說明影響範圍和遷移指引）
- **以下情況強制寫 body**：
  - 破壞性變更
  - Commit 同時包含兩種不同目的的變更（若無法拆分時，需在 body 說明各部分的理由）
- 每行限制 72 字元
- 不要僅羅列修改的檔案列表，不要重複 subject 已表達的內容
- body 與 subject 之間保留一個空行

#### Footer 規則

```
BREAKING CHANGE: API endpoints now require authentication
Closes #123
Refs #456
```

#### Scope 使用規範

- 使用小寫字母，不超過 15 字元
- 跨模組或不確定時省略 scope
- 從專案已有提交或 commitlint `scope-enum` 中取得可用值

#### 破壞性變更

兩種標記方式（均為 Conventional Commits 標準）：

**方式 1：類型後加 `!`**
```
feat!: remove deprecated endpoints
feat(api)!: remove deprecated endpoints
```

**方式 2：Footer 中宣告**
```
feat(api): remove deprecated endpoints

BREAKING CHANGE: v1 endpoints are no longer available.
Migration guide: docs/migration.md
```

## 注意事項

- 僅負責建立提交，不執行推送
- 不提交密碼、金鑰、token 等敏感資訊
- 簡單變更不寫 body；新增大文件、複雜變更、破壞性變更應寫 body
- 不要在提交訊息中包含 `Co-Authored-By` 等元資訊

## 範例

### 基礎

```
feat: add dark mode support
fix: 修復登入逾時問題
docs: 更新安裝指南
```

### 帶 Scope

```
feat(auth): 實作 OAuth2 登入
fix(ui): 修復行動端按鈕對齊問題
```

### 帶 Issue

```
feat(auth): #1254 實作 OAuth2 登入
fix(ui): #123 修復行動端按鈕對齊問題
```

### 帶 Body — 破壞性變更

```
feat(api)!: 重構分頁介面為 cursor-based

舊的 page/limit 參數不再支援，遷移方式見 docs/migration.md

Closes #42
```

### 新增大型文件（建議寫 body）

```
docs: add lwIP adapter architecture analysis document

Covering HAL vtable binding mechanism, RX/TX data flow,
netif integration points, and error handling strategy
for the DM9051-lwIP adapter layer.
```

### 不同目的需拆分（反例 → 正例）

❌ **錯誤：修復 + 文件混在同一個 commit**
```
fix(dm9051_lwip.h): remove stale _E suffix in doc comments, add lwIP analysis doc
```

✅ **正確：拆成兩個 commit**
```
fix(dm9051_lwip.h): correct function name references in comments

ethernetif_init_E -> ethernetif_init
ethernetif_input_E -> ethernetif_input
(comment-only change, no behavioral impact)
```

```
docs: add lwIP adapter architecture analysis

1264-line design doc covering HAL vtable binding, RX/TX
data flow, netif integration, and error handling strategy.
```
