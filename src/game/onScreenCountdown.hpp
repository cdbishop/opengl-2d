#pragma once
#include <chrono>
#include <functional>

#include <system/EventManager.hpp>
#include <system/TextManager.hpp>

class OnScreenCountdown {
public:
  using Ptr = std::shared_ptr<OnScreenCountdown>;
  using Callback = std::function<void()>;

  OnScreenCountdown(TextManager::Ptr textManager, glm::vec2 position);
  ~OnScreenCountdown();
   
  void Update();

  void StartCountdown(unsigned int seconds, Callback cb);

private:
  struct CountDown {
    std::vector<TextManager::Id> _secondSprites;
    Callback _callback;
  };

  TextManager::Ptr _textManager;
  EventManager::Ptr _eventManager;
  glm::vec2 _position;

  std::vector<CountDown> _countdowns;
};