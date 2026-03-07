# OOP 設計

## include/

### 遊戲物件

**Bird.hpp** — 小鳥（繼承 `Util::GameObject`）
- 重力與速度（`velocity += gravity * deltaTime`）
- 跳躍（按鍵設定向上初速）
- 飛行動畫（使用 `Util::Animation` 切換翅膀幀）
- 旋轉角度（根據 Y 軸速度計算）

**Pipe.hpp** — 水管 + PipePair
- `Pipe`：單根水管（繼承 `Util::GameObject`），持有 `Util::Image`
- `PipePair`：上下一組水管，管理缺口高度與位置

**PipeManager.hpp** — 水管管理器
- 定時生成新的 `PipePair`
- 移動所有水管（向左）
- 刪除超出畫面的水管
- 判定小鳥是否通過水管（得分觸發）

### 背景元素

**Background.hpp** — 背景圖塊（繼承 `Util::GameObject`）
- 載入背景圖，向左持續捲動
- 無縫銜接（兩張圖交替繪製）

**Ground.hpp** — 地板圖塊（繼承 `Util::GameObject`）
- 載入地板圖，向左持續捲動
- 無縫銜接
- 提供地面 Y 座標供碰撞偵測使用

### UI 與計分

**Numbers.hpp** — 數字系統
- `m_Score` 記錄當前分數
- 持有多個 `Util::GameObject`（用 `Util::Image` 顯示數字圖 0-9）
- `AddPoint()` / `Reset()` / `UpdateDisplay()`

**TaskText.hpp** — UI 文字顯示
- 顯示 "Get Ready"、"Game Over" 等畫面文字
- 使用 `Util::Image` 或 `Util::Text`

### 工具與管理

**AppUtil.hpp** — 常數定義與碰撞偵測工具
- 遊戲常數（重力、跳躍力、水管速度、缺口大小等）
- `CheckAABB(Bird, PipePair)` — 矩形碰撞偵測
- `CheckGround(Bird, groundY)` — 地面碰撞偵測
- `CheckCeiling(Bird)` — 天花板邊界偵測

**PhaseManager.hpp** — 遊戲狀態機
- `enum Phase { READY, PLAYING, GAME_OVER }`
- 管理狀態轉換與各狀態下允許的操作

**App.hpp** — 主程式框架
- 持有所有物件的 `shared_ptr`
- `Start()` / `Update()` / `End()`

---

## src/

**main.cpp** — 程式進入點

**App.cpp** — App 類別主體（或拆分為以下三個）

**AppStart.cpp** — 初始化
- 載入所有圖片與音效資源
- 建立 Bird、PipeManager、Background、Ground、Score 物件
- 設定初始狀態為 READY

**AppUpdate.cpp** — 遊戲主循環
- 根據 `PhaseManager` 的狀態執行不同邏輯
- READY：等待輸入開始
- PLAYING：更新物理、移動水管、偵測碰撞、計分
- GAME_OVER：顯示結束畫面、等待重新開始

**AppEnd.cpp** — 遊戲結束清理

**Bird.cpp** — 小鳥邏輯實作

**Pipe.cpp** — 水管 & PipePair 實作

**PipeManager.cpp** — 水管管理器實作

**Background.cpp** — 背景捲動實作

**Ground.cpp** — 地板捲動實作

**Numbers.cpp** — 數字物件實作



