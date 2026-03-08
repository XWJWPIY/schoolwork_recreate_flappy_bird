#include "AppUtil.hpp"
#include "Util/GameObject.hpp"
#include "Util/Logger.hpp"

bool CheckCollision(const std::shared_ptr<Util::GameObject> &a,
                    const std::shared_ptr<Util::GameObject> &b) {
  glm::vec2 pos1 = a->GetTransform().translation;
  glm::vec2 size1 = a->GetScaledSize();
  glm::vec2 pos2 = b->GetTransform().translation;
  glm::vec2 size2 = b->GetScaledSize();

  // 計算自身的上下左右邊界 (假設 Y 軸正向朝上)
  float left1 = pos1.x - (size1.x / 2.0f);
  float right1 = pos1.x + (size1.x / 2.0f);
  float top1 = pos1.y + (size1.y / 2.0f);
  float bottom1 = pos1.y - (size1.y / 2.0f);

  // 計算目標的上下左右邊界
  float left2 = pos2.x - (size2.x / 2.0f);
  float right2 = pos2.x + (size2.x / 2.0f);
  float top2 = pos2.y + (size2.y / 2.0f);
  float bottom2 = pos2.y - (size2.y / 2.0f);

  LOG_TRACE("Bird position: {}", pos1.y);
  LOG_TRACE("Ground position: {}", pos2.y);
  LOG_TRACE("Bird size: {}", size1.y);
  LOG_TRACE("Ground size: {}", size2.y);
  LOG_TRACE("Bird top: {}", top1);
  LOG_TRACE("Bird bottom: {}", bottom1);
  LOG_TRACE("Ground top: {}", top2);
  LOG_TRACE("Ground bottom: {}", bottom2);

  // AABB 碰撞偵測邏輯：當所有方向的投影都有重疊時，即代表發生碰撞
  if (right1 >= left2 && left1 <= right2 && top1 >= bottom2 &&
      bottom1 <= top2) {
    return true;
  }

  return false;
}
