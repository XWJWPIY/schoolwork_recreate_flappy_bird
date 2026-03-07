# Flappy Bird Development History

## 目前已完成進度 (Current Progress)

### 2026-03-07
#### Week 2-3：產生小鳥與基礎物理 (Completed)
- [x] **在畫面上載入並繪製小鳥**：已建立 `Bird` 類別，並成功載入 `flippy_bird.png` 素材，透過 `m_Renderer` 繪製在畫面上。
- [x] **實作重力參數，讓小鳥自動下落**：已在 `Bird::Update()` 中實做 `v = v0 + a * dt` 的物理下墜邏輯，並設定最低點碰撞避免飛出畫面。
- [x] **實作讀取空白鍵輸入，讓小鳥向上浮空跳躍**：已實作 `Bird::Jump()` 函式，按下空白鍵時小鳥會獲得固定的向上初速度 (`m_JumpVelocity`)，且等速上升一段時間 (`m_JumpDuration`) 後恢復受重力影響。在 `App::Update()` 的 PLAYING 狀態中偵測空白鍵輸入來觸發跳躍。

#### Week 4-5：背景移動與視覺回饋 (Partially Completed)
- [x] **載入並繪製背景與地板**：
  - 已建立 `Background` 類別。
  - 使用私有函式 `UpdateDisplay()` 載入 `classic_background.png`。
  - 將背景設定為底層 `z-index = -10.0f` 並縮放以填滿畫面。
- [ ] 實作背景和地板向左持續移動，產生前進感
- [ ] 處理背景連續無縫銜接捲動

#### Week 11-12：計分系統與狀態完善 (Partially Completed)
- [x] **在畫面上顯示與更新當前分數**：
  - 已建立 `Numbers` 類別管理分數的圖片顯示。
  - 實作了依據字串長度與 `Util::Image::GetSize()` 動態計算圖片寬度，並自動置中排列數字圖片（支援0~9動態切換、多重位數防偏移與統一縮放比例設定）。
  - 目前將得分邏輯暫時綁定在空白鍵（跳躍即得分）作為測試。

## 待開發項目 (To-Do List)

1. **背景 / 地板的無縫捲動 (Scrolling Ground & Background)**
2. **水管系統 (Pipe & PipeManager)**：定時生成不同高度破口的水管，並向左移動。
3. **精確的碰撞偵測 (Collision Detection)**：小鳥撞擊水管、撞擊地面。
4. **狀態機機制切換**：Start Screen (準備畫面) -> Playing (遊玩中) -> Game Over (結算畫面)。
5. **音效整合 (Audio)**：加入跳躍、得分與死亡音效。
6. **動畫狀態更新**：小鳥隨不同速度（上升/下降）改變自身的圖片與旋轉角度。

---
*Last updated: 2026-03-07*
