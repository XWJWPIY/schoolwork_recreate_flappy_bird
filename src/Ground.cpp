#include "Ground.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"

Ground::Ground(float x, float y, float scaleX, float scaleY)
    : Util::GameObject(std::make_shared<Util::Image>(
                           RESOURCE_DIR "/images/ground/ground0.png"),
                       0.4f // zIndex
                       ),
      m_ScaleX(scaleX), m_ScaleY(scaleY) {

  m_Transform.translation = {x, y};
  m_Transform.scale = {scaleX, scaleY};
  SetVisible(true);

  LOG_TRACE("Ground created");
}

Ground::~Ground() { LOG_TRACE("Ground destroyed"); }

void Ground::Update() {
  // 未來可以實作地板向左移動的捲動邏輯
}
