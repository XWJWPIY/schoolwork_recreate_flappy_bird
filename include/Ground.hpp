#ifndef GROUND_HPP
#define GROUND_HPP

#include "Util/GameObject.hpp"

class Ground : public Util::GameObject {
public:
  Ground(float x = 0.0f, float y = -310.0f, float scaleX = 0.4f,
         float scaleY = 0.4f);
  ~Ground();

  void Update(); // 未來可能需要的更新邏輯，例如捲動

private:
  float m_ScaleX;
  float m_ScaleY;
};

#endif // GROUND_HPP
