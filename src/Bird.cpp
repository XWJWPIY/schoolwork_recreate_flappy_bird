#include "Bird.hpp"
#include "Ground.hpp"

#include "Util/Image.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

Bird::Bird()
    : Util::GameObject(std::make_shared<Util::Image>(
                           RESOURCE_DIR "/images/bird/flippy_bird.png"),
                       5.0f // zIndex
      ) {
  m_Transform.translation = {-200, 0};
  m_Transform.scale = {0.03f, 0.03f};
  SetVisible(true);
  LOG_TRACE("Bird created");
}

Bird::~Bird() { LOG_TRACE("Bird destroyed"); }

void Bird::Update() {
  float deltaTime = Util::Time::GetDeltaTimeMs();

  if (m_IsJumping) {
    // 跳躍中：無視重力，等速上升
    m_Velocity = m_JumpVelocity;

    // 更新計時器
    m_JumpTimer -= deltaTime;
    if (m_JumpTimer <= 0.0f) {
      m_IsJumping = false; // 跳躍結束，恢復受重力影響
      m_Velocity = 0.0f;   // 可以在最高點速度歸零，讓之後重力自然接手
    }
  } else {
    // 1. 速度受重力影響遞增 (v = v0 + a * dt)
    m_Velocity += m_Gravity * deltaTime;
  }

  // 2. 位置受速度影響改變 (y = y0 + v * dt)
  m_Transform.translation.y += m_Velocity * deltaTime;

  // 3. (已經沒有最低點限制，交給 App 判斷是否撞到地板)
}

void Bird::Jump() {
  m_IsJumping = true;
  m_JumpTimer = m_JumpDuration; // 重置跳躍計時器
  m_Velocity = m_JumpVelocity;  // 立即獲得向上速度
}

void Bird::StopFalling(float targetY) {
  m_Velocity = 0.0f;
  m_Transform.translation.y = targetY;
}
