#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
  LOG_TRACE("Start");

  m_Bird = std::make_shared<Bird>();
  m_Numbers = std::make_shared<Numbers>();
  m_Background = std::make_shared<Background>();
  m_Ground = std::make_shared<Ground>();

  m_Renderer.AddChild(m_Bird);
  m_Renderer.AddChild(m_Numbers);
  m_Renderer.AddChild(m_Background);
  m_Renderer.AddChild(m_Ground);

  m_CurrentState = State::UPDATE;
}

void App::Update() {

  switch (m_Phase) {
  case AppUtil::Phase::READY:
    // 等待玩家按下空白鍵開始遊戲
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
      m_Phase = AppUtil::Phase::PLAYING;
      LOG_TRACE("Game Started! Phase: PLAYING");
    }
    break;

  case AppUtil::Phase::PLAYING:
    // 接收玩家輸入
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
      m_Bird->Jump();
      m_Numbers->AddNumber();
    }

    // 遊戲進行中，小鳥才會掉落與更新
    m_Bird->Update();
    // m_Ground->Update();

    // 由 App 統一判斷碰撞
    if (CheckCollision(m_Ground, m_Bird)) {
      // 計算地板上緣 Y 座標 (位置 + 一半的高)
      float groundTop = m_Ground->GetTransform().translation.y +
                        (m_Ground->GetScaledSize().y / 2.0f);

      // 命令小鳥停在地板正上方
      m_Bird->StopFalling(groundTop + (m_Bird->GetScaledSize().y / 2.0f));

      // 觸發遊戲結束
      m_Phase = AppUtil::Phase::GAME_OVER;
      LOG_TRACE("Game Over! Bird hit the ground.");
    }

    break;

  case AppUtil::Phase::GAME_OVER:
    // 遊戲結束，等待重新開始的邏輯 (後續實作)
    break;
  }

  m_Renderer.Update();

  /*
   * Do not touch the code below as they serve the purpose for
   * closing the window.
   */
  if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
    m_CurrentState = State::END;
  }
}

void App::End() { // NOLINT(this method will mutate members in the future)
  LOG_TRACE("End");
}
