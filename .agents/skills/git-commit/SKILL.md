---
name: xin-gitcommit
description: >-
  依照 Xin 專案 Git commit 規範，協助撰寫、確認並執行 commit（與可選的 push）。
  Use when the user wants to commit changes, write a commit message, git commit,
  寫 commit、提交、commit message、推版、push。
---

# Git Commit 助手（xin-gitcommit）

依照 [COMMIT_CONVENTION.md](COMMIT_CONVENTION.md) 為本專案產生符合規範的 commit message，
並依使用者需求執行 commit / push。

---

## 模式說明

| 模式 | 觸發方式 | 行為 |
|------|----------|------|
| **草稿模式** | 只要求寫 commit msg | 產出草稿供使用者自行執行，不執行任何 git 指令 |
| **半自動模式** | 要求「幫我 commit」 | 顯示草稿 → 使用者確認 → 執行 `git commit`，不 push |
| **全自動模式** | 要求「幫我 commit 並 push」 | 顯示草稿 → 使用者確認 → 執行 `git commit` + `git push` |

> ⚠️ **全自動模式強制確認**：不論使用者說「直接做」或「不用問我」，
> commit message 草稿**一定要讓使用者看到並明確批准後**才能執行 commit 與 push。
> Push 是對共用遠端的不可逆操作，禁止跳過確認步驟。

---

## 執行流程

### Step 1 — 確認 Staging 範圍

先執行 `git status` 與 `git diff --cached --name-only` 取得目前狀態，再依以下情況處理：

**情況 A：使用者在指令中已指定檔案或路徑**
（例如：`/xin-gitcommit Assets/GameXXX/Scripts/`）

- 僅對指定範圍執行 `git add <paths>`，其他異動檔案保持原狀
- 執行前列出將要 stage 的檔案清單，讓使用者確認

**情況 B：目前已有 staged 變更（且使用者未另外指定）**

- 直接使用現有 staged 內容，不額外 `git add`
- 顯示已 staged 的檔案清單供使用者確認範圍正確

**情況 C：無任何 staged 變更，使用者也未指定檔案**

- 列出所有 unstaged 異動檔案（含路徑），讓使用者選擇：
  1. 指定要 stage 的檔案或目錄（可多個）
  2. 或輸入「全部」代為執行 `git add -A`（需再次確認）
- 不可自行判斷並 stage 所有變更

收集完 staged 範圍後，再執行：

```bash
git diff --cached          # 已 stage 的完整 diff（用於分析 commit 內容）
git log --oneline -5       # 最近 5 筆 commit（用於對齊風格）
```

- 若使用者有提供 QC 編號，記下備用。

#### 模組分離判斷

分析 `git diff --cached` 結果是否涉及多個業務模組路徑
（如 Assets/GameXXX/ 與 Assets/GameYYY/ 分屬不同模組）：

- 所有變更屬同一模組 → 繼續
- 涉及多個模組 → 列出各模組變更行數，詢問使用者：
  - 是否要拆分個別 commit？
  - 或維持同一個 commit 一起提交？

#### 從 Branch 名稱提取 QC 編號

若使用者未提供 QC 編號，也可從目前分支名稱解析：

- `feature/#1234` → `1234`
- `fix/567-login-bug` → `567`
- `issue/890` → `890`

解析到的 QC 編號併入 Step 5 Footer 處理。

### Step 2 — 判斷 Type

依 COMMIT_CONVENTION.md 規則選出**唯一**一個 Type：

- 同時有 fix 與 feat → 優先用 `fix`
- Localization / GameStreet 更動 → 用 `feat` 或 `fix`（非 `docs`）
- 僅格式調整 → `style`；僅重構 → `refactor`；第三方更新 → `chore`

### Step 3 — 撰寫 Subject

- 祈使句、50 字以內、不加句號
- 必須描述**實際改動內容**，不可只寫 QC 編號
- 優先以繁體中文撰寫（與既有 commit 風格一致）

### Step 4 — 判斷 Body（選填）

需要 Body 的情況：
- 標題無法完整說明複雜改動（多個修正點）
- 需補充測試方式或排除 QA 測項
- 有場景異動（格式：`+場景異動: GameXXX、GameYYY。`）
- 盡量精簡，不需要有太具體改動的描述(例如實際把檔案更動內容說出來)

### Step 5 — 判斷 Footer（有 QC 編號時必填）

```
issue 4831
issue 4832
```

每個 QC 獨立一行，格式嚴格為 `issue XXXX`。
若有實際說QC是單檔的，格式為 `單檔issue XXXX`。

### Step 6 — 提交前 Review（使用 Subagent）

基於 Step 1 收集的 diff 執行獨立 review：

- 啟動 subagent，僅傳遞客觀材料（staged file list、完整 diff）
- 不傳遞主執行緒對 Type/Subject 的判斷結論，避免引導

檢查項：

- **敏感資訊**：密碼、金鑰、token、私有憑證
- **臨時程式碼**：除錯日誌、TODO 佔位、硬編碼測試資料
- **衝突與格式**：衝突標記、尾隨空格、縮排異常
- **提交範圍**：不相關檔案、生成物、大檔案混入

處理邏輯：

- **無阻塞問題** → 繼續執行 Step 7
- **有阻塞問題** → 列出問題檔案位置與建議修復方式，暫停提交
- **有非阻塞風險** → 繼續 Step 7，但輸出草稿時一併提示風險

---

### Step 7 — 輸出草稿並確認

以下方模板呈現草稿，**等待使用者明確回覆「確認」或修改意見**：

```
────────────────────────────────
📝 Commit Message 草稿
────────────────────────────────
<Type>: <Subject>

<Body（若有）>

<Footer（若有）>
────────────────────────────────
模式：[草稿 / commit / commit + push]

請確認內容。若需調整請直接告知，確認後輸入「ok」或「確認」即可執行。
```

### Step 8 — 執行（半自動 / 全自動模式）

Step 7 使用者確認後：

1. **Commit**：
   ```bash
   git commit -m "$(cat <<'EOF'
   <Type>: <Subject>

   <Body>

   <Footer>
   EOF
   )"
   ```
   使用 heredoc 確保多行訊息格式正確，**禁止使用 `--no-verify`**。

2. **Push**（全自動模式）：

   Push 前先執行：
   ```bash
   git log @{u}..HEAD --oneline
   ```
   確認本地領先提交內容符合預期，避免誤推。

   若目前 branch 無 upstream 追蹤，告知使用者並詢問是否要設定 upstream。

   確認後執行：
   ```bash
   git push
   ```

3. 回報執行結果（成功 commit hash / 失敗錯誤訊息）。

---

## 格式自我檢查清單

執行前確認 commit message 符合以下規則：

- [ ] Type 只有一個，來自規範表
- [ ] Subject ≤ 50 字，祈使句，不加句號
- [ ] Body 與 Subject 之間有空行（若有 Body）
- [ ] Footer 與 Body 之間有空行（若有 Footer）
- [ ] 有 QC 編號時 Footer 必填，格式為 `issue XXXX` or `單檔issue XXXX`
- [ ] 沒有捏造 QC 編號

---

## 邊界情況

| 情況 | 處理方式 |
|------|----------|
| 無 staged 變更且未指定檔案 | 列出所有 unstaged 檔案，要求使用者指定範圍後再繼續 |
| 使用者提供 QC 但未在 diff 中出現 | 仍加入 Footer，但標注「由使用者提供」 |
| Push 遠端需要驗證或 force-push | 停止並告知，不自動加 `--force` |
| Pre-commit hook 失敗 | 回報錯誤內容，不 amend，協助排查後重新 commit |
| 使用者要修改草稿 | 重新輸出修改後的草稿，再次等待確認 |
| Subagent review 發現阻塞問題 | 列出問題檔案位置與建議修復方式，暫停提交流程 |
| 變更涉及多個業務模組 | 列出各模組行數，詢問是否拆分 commit |
| 本地 branch 無 upstream 追蹤 | 告知無法自動 push，詢問是否要設定 upstream |

---

## 參考資源

- 完整規範：[COMMIT_CONVENTION.md](COMMIT_CONVENTION.md)
