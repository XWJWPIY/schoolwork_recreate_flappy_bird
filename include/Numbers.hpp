#ifndef NUMBERS_HPP
#define NUMBERS_HPP

#include "Util/GameObject.hpp"
#include <memory>

class Numbers : public Util::GameObject {
public:
  Numbers();

  void SetNumber(int number);
  void AddNumber();
  void Reset();

private:
  void UpdateDisplay();

  int m_Number = 0;
};

#endif
