#include "Numbers.hpp"
#include "Util/Image.hpp"
#include <string>

Numbers::Numbers() : Util::GameObject() {
  m_ZIndex = 10.0f; // UI 層，確保在最上層
  UpdateDisplay();
}

void Numbers::SetNumber(int number) {
  m_Number = number;
  UpdateDisplay();
}

void Numbers::AddNumber() {
  m_Number++;
  UpdateDisplay();
}

void Numbers::Reset() {
  m_Number = 0;
  UpdateDisplay();
}

void Numbers::UpdateDisplay() {
  m_Children.clear(); // 清除舊的數字物件

  std::string numberStr = std::to_string(m_Number);

  // 設定統一的縮放比例與間距
  float scaleX = 0.15f;
  float scaleY = 0.15f;
  float padding = 1.0f; // 數字間距

  // 1. 先計算所有數字圖片的總寬度
  float totalWidth = 0.0f;
  std::vector<std::shared_ptr<Util::Image>> cachedImages;

  for (size_t i = 0; i < numberStr.size(); i++) {
    char digit = numberStr[i];
    std::string path =
        std::string(RESOURCE_DIR) + "/images/ui/digits/" + digit + ".png";

    // 建立並暫存圖片物件
    auto img = std::make_shared<Util::Image>(path);
    cachedImages.push_back(img);

    // 累加實際寬度並乘上縮放比例
    totalWidth += img->GetSize().x * scaleX;
  }

  // 加上每個數字之間的間距總和
  if (numberStr.size() > 1) {
    totalWidth += (numberStr.size() - 1) * padding;
  }

  // 計算第一個數字的起始 x 座標，使整體置中
  float currentX = -totalWidth / 2.0f;

  // 2. 依照圖片寬度與間距，逐個計算並放上 GameObject
  for (size_t i = 0; i < numberStr.size(); i++) {
    auto img = cachedImages[i];

    auto digitObj = std::make_shared<Util::GameObject>(img,
                                                       10.0f // z-index
    );

    digitObj->m_Transform.scale = {scaleX, scaleY};

    // 計算當前數字的中心點 x 座標
    // 將 currentX 推到圖形的中心點：currentX + (圖形縮放後寬度 / 2)
    float digitScaledWidth = img->GetSize().x * scaleX;
    float posX = currentX + digitScaledWidth / 2.0f;

    digitObj->m_Transform.translation = {posX, 200.0f}; // 顯示在畫面上半部
    AddChild(digitObj);

    // 將 currentX 移動到下一個數字的起始位置
    currentX += digitScaledWidth + padding;
  }
}
