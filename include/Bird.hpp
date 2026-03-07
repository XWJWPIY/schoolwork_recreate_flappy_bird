#ifndef BIRD_HPP
#define BIRD_HPP

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class Bird : public Util::GameObject {
public:
  Bird();
  ~Bird();

  void Update();

  void Jump();

private:
  float m_Velocity = 0.0f;
  float m_Gravity = -0.0015f; // 重力常數

  // 跳躍相關變數
  bool m_IsJumping = false;
  float m_JumpVelocity = 0.5f; // 跳躍時的等速上升速度
  float m_JumpTimer = 0.0f;
  float m_JumpDuration = 150.0f; // 跳躍持續時間 (毫秒)
};

#endif
