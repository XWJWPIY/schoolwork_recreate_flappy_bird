#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <memory>
#include <vector>

class Numbers : public Util::GameObject {
public:
  Numbers();

  void SetNumber(int number);
  void AddNumber();
  void Reset();

private:
  void UpdateDisplay();

  int m_Number = 0;
  std::vector<std::shared_ptr<Util::Image>> m_DigitImages;
};

#endif
