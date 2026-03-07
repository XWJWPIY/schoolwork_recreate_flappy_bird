#include "Bird.hpp"

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

  // 3. 碰到預設最低點停住
  // (之後可以改成碰到地板碰撞框 `Ground` 才停住)
  if (m_Transform.translation.y <= -200.0f) {
    m_Transform.translation.y = -200.0f;
    m_Velocity = 0.0f; // 抵達最低點，速度歸零
  }
}

void Bird::Jump() {
  m_IsJumping = true;
  m_JumpTimer = m_JumpDuration; // 重置跳躍計時器
  m_Velocity = m_JumpVelocity;  // 立即獲得向上速度
}
