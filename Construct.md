# OOP 設計

## include/

### 遊戲物件

**Bird.hpp** — 小鳥（繼承 `Util::GameObject`）
- **用途**：處理主角小鳥的重力下墜、跳躍邏輯與物理狀態更新。
- **變數**：
  - `m_Velocity` (float)：當前垂直速度。
  - `m_Gravity` (float)：重力常數（`-0.0015f`）。
  - `m_IsJumping` (bool)，`m_JumpVelocity` (float)，`m_JumpTimer` (float)，`m_JumpDuration` (float)：處理跳躍與持續時間、上升速度的參數。
- **函式**：
  - `Update()`：每幀更新小鳥的物理狀態與位置。
  - `Jump()`：觸發跳躍動作，設定相關跳躍參數。
- **待實作**
  - 運用無反傳值，單一整數的函式，可以讀取依據目前狀態，小鳥是在上升(無視重力)、下墜、或淘汰三種狀態，給出對應的角度的設定
  - 製作小鳥拍翅動畫

**Pipe.hpp** — 水管 + PipePair（尚未實作）
- `Pipe`：單根水管（繼承 `Util::GameObject`），持有 `Util::Image`
    - Pipe 與 bird 物件可以進行碰撞偵測
- `PipePair`：上下一組水管，管理缺口高度與位置

**PipeManager.hpp** — 水管管理器（尚未實作）
- 定時生成新的 `PipePair`
- 移動所有水管（向左）
- 刪除超出畫面的水管
- 判定小鳥是否通過水管（得分觸發）

### 背景元素

**Background.hpp** — 背景圖塊（繼承 `Util::GameObject`）
- **用途**：載入背景圖並處理畫面更新（將處理向左捲動與無縫銜接）。
- **變數**：目前僅繼承自父類別，無自訂公開變數。
- **函式**：
  - `UpdateDisplay()`：私有函式，更新並重繪背景畫面。
- **待實作**
  - 運用無反傳值，單一整數的函式，設定背景圖片

**Ground.hpp** — 地板圖塊（繼承 `Util::GameObject`）（尚未實作）
- 載入地板圖，向左持續捲動
- 無縫銜接
- 與 bird 物件可以進行碰撞偵測

### UI 與計分

**Numbers.hpp** — 數字系統（繼承 `Util::GameObject`）
- **用途**：自訂數字渲染系統，使用數字貼圖拼接顯示當前分數與各數值。
- **變數**：
  - `m_Number` (int)：記錄當前要顯示的數值。
  - `m_DigitImages` (`std::vector<std::shared_ptr<Util::Image>>`)：儲存對應數字的圖片集合。
- **函式**：
  - `SetNumber(int number)`：設定要顯示的數值。
  - `AddNumber()`：將現有數值增加並更新。
  - `Reset()`：將數值重置。
  - `UpdateDisplay()`：私有函式，負責動態生成或排列對應的數字貼圖。

**TaskText.hpp** — UI 文字顯示（尚未實作）
- 顯示 "Get Ready"、"Game Over" 等畫面文字
- 使用 `Util::Image` 或 `Util::Text`

### 工具與管理

**AppUtil.hpp** — 常數定義與狀態工具
- **用途**：定義遊戲中共用的狀態、碰撞或物理判定常數（碰撞部分尚未實作）。
- **變數與定義**：
  - `enum class Phase`：包含 `READY`（預備）、`PLAYING`（遊玩中）、`GAME_OVER`（結束判定）三種狀態。

**PhaseManager.hpp** — 遊戲狀態機（尚未實作）
- `enum Phase { READY, PLAYING, GAME_OVER }`
- 管理狀態轉換與各狀態下允許的操作

**App.hpp** — 主程式框架
- **用途**：控制遊戲的主生命週期，並持有所有核心的遊戲物件（Background、Bird、Numbers 等）。
- **變數**：
  - `m_CurrentState` (`State`)：程式層級狀態（`START`、`UPDATE`、`END`）。
  - `m_Phase` (`AppUtil::Phase`)：遊戲進程層級狀態（`READY`、`PLAYING`、`GAME_OVER`）。
  - `m_Background`、`m_Bird`、`m_Numbers`：主要遊戲物件的智慧指標（`shared_ptr`）。
  - `m_Renderer` (`Util::Renderer`)：PTSD 框架的渲染器物件。
- **函式**：
  - `GetCurrentState()`：取得當前程式狀態。
  - `Start()`、`Update()`、`End()`：主程式的三大生命週期。
  - `ValidTask()`：私有函式，負責框架層級的有效性更新或任務處理。

  - 待製作
    進行 enum 關卡編號常數設定
    設計關卡結構
    

---

## src/

**main.cpp** — 程式進入點

**App.cpp** — App 類別主體（或拆分為以下三個）

**AppStart.cpp** — 初始化（尚未實作，可能與App.cpp合併）
- 載入所有圖片與音效資源
- 建立 Bird、PipeManager、Background、Ground、Score 物件
- 設定初始狀態為 READY

**AppUpdate.cpp** — 遊戲主循環（尚未實作，可能與App.cpp合併）
- 根據 `PhaseManager` 的狀態執行不同邏輯
- READY：等待輸入開始
- PLAYING：更新物理、移動水管、偵測碰撞、計分
- GAME_OVER：顯示結束畫面、等待重新開始

**AppEnd.cpp** — 遊戲結束清理（尚未實作，可能與App.cpp合併）

**Bird.cpp** — 小鳥邏輯實作

**Pipe.cpp** — 水管 & PipePair 實作（尚未實作）

**PipeManager.cpp** — 水管管理器實作（尚未實作）

**Background.cpp** — 原版背景是固定位置

**Ground.cpp** — 地板捲動實作（尚未實作）

**Numbers.cpp** — 數字物件實作 (包含最高分、時間、分數、關卡號等，都會以此物件製作顯示)



