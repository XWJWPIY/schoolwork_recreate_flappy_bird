#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "Util/GameObject.hpp"

class Background : public Util::GameObject {
public:
  Background();

private:
  void UpdateDisplay();
};

#endif
