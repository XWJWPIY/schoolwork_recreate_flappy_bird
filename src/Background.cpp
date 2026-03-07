#include "Background.hpp"
#include "Util/Image.hpp"

Background::Background() : Util::GameObject() {
  m_ZIndex = -10.0f; // z-index 底層
  UpdateDisplay();
}

void Background::UpdateDisplay() {
  // 建立背景圖片物件
  auto bgImage = std::make_shared<Util::Image>(
      RESOURCE_DIR "/images/background/classic_background.png");

  auto backgroundObj = std::make_shared<Util::GameObject>(bgImage, m_ZIndex);

  backgroundObj->m_Transform.scale = {0.3f, 0.3f}; // 調整縮放大小

  AddChild(backgroundObj);
}
