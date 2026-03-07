#include "Numbers.hpp"
#include "Util/Image.hpp"
#include <string>

Numbers::Numbers() : Util::GameObject() {
  m_ZIndex = 10.0f; // UI 層，確保在最上層

  // 啟動時預先載入 0~9 的圖片存進 Lookup Table
  for (int i = 0; i < 10; i++) {
    std::string path = std::string(RESOURCE_DIR) + "/images/ui/digits/" +
                       std::to_string(i) + ".png";
    m_DigitImages.push_back(std::make_shared<Util::Image>(path));
  }

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
  std::string numberStr = std::to_string(m_Number);

  // 設定統一的縮放比例與間距
  float scaleX = 0.15f;
  float scaleY = 0.15f;
  float padding = 1.0f; // 數字間距

  // 1. 先計算所有數字圖片的總寬度
  float totalWidth = 0.0f;

  for (size_t i = 0; i < numberStr.size(); i++) {
    int digitValue = numberStr[i] - '0';
    auto img = m_DigitImages[digitValue];

    // 累加實際寬度並乘上縮放比例
    totalWidth += img->GetSize().x * scaleX;
  }

  // 加上每個數字之間的間距總和
  if (numberStr.size() > 1) {
    totalWidth += (numberStr.size() - 1) * padding;
  }

  // 計算第一個數字的起始 x 座標，使整體置中
  float currentX = -totalWidth / 2.0f;

  // 如果現有的 GameObject 數量不夠位數顯示，就補新的空節點進去
  while (m_Children.size() < numberStr.size()) {
    auto newObj = std::make_shared<Util::GameObject>(nullptr, // 先不用給圖
                                                     10.0f    // z-index
    );
    AddChild(newObj);
  }

  // 2. 依照圖片寬度與間距，逐個計算並放上 GameObject，並利用 Object Pooling
  for (size_t i = 0; i < m_Children.size(); i++) {
    auto digitObj = m_Children[i];

    // 如果這個 GameObject 在目前的位數範圍內，顯示並更新圖片
    if (i < numberStr.size()) {
      int digitValue = numberStr[i] - '0';
      auto img = m_DigitImages[digitValue];

      digitObj->SetDrawable(img); // 抽換相框裡的相片 (解參考)
      digitObj->SetVisible(true); // 設為顯示

      digitObj->m_Transform.scale = {scaleX, scaleY};

      // 計算當前數字的中心點 x 座標
      float digitScaledWidth = img->GetSize().x * scaleX;
      float posX = currentX + digitScaledWidth / 2.0f;

      digitObj->m_Transform.translation = {posX, 300.0f}; // 數字中心座標

      // 將 currentX 移動到下一個數字的起始位置
      currentX += digitScaledWidth + padding;
    } else {
      // 超出的 GameObject 就隱藏起來留著以後用
      digitObj->SetVisible(false);
    }
  }
}
