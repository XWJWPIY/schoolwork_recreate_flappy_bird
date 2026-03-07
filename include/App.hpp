#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export

#include "AppUtil.hpp"
#include "Bird.hpp"
#include "Numbers.hpp"
#include "Util/Renderer.hpp"

#include <memory>

class App {
public:
  enum class State {
    START,
    UPDATE,
    END,
  };

  State GetCurrentState() const { return m_CurrentState; }

  void Start();

  void Update();

  void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
  void ValidTask();

private:
  State m_CurrentState = State::START;
  AppUtil::Phase m_Phase = AppUtil::Phase::READY;

  std::shared_ptr<Bird> m_Bird;
  std::shared_ptr<Numbers> m_Numbers;
  Util::Renderer m_Renderer;
};

#endif
