#include "onScreenCountdown.hpp"
#include <game/onScreenCountdown.hpp>

OnScreenCountdown::OnScreenCountdown(TextManager::Ptr textManager, glm::vec2 position)
  :_textManager(textManager),
   _position(position) {
  _eventManager = std::make_shared<EventManager>();
}

OnScreenCountdown::~OnScreenCountdown()
{
}

void OnScreenCountdown::Update()
{
  _eventManager->Update();
}

void OnScreenCountdown::StartCountdown(unsigned int seconds, Callback cb)
{
  CountDown cd;  
  cd._secondSprites.resize(seconds);  
  cd._callback = cb;

  _countdowns.push_back(cd);

  CountDown& ref = _countdowns[_countdowns.size() - 1];

  auto updateCallack = [this, &ref](unsigned int second, unsigned int index) {

    _textManager->RemoveText(ref._secondSprites[index - 1]);
    ref._secondSprites[index] = _textManager->AddText(std::to_string(second), _position);
  };

  for (unsigned int i = 1; i < seconds; ++i) {
    _eventManager->After(std::chrono::seconds(i), std::bind(updateCallack, seconds - i, i));
  }

  ref._secondSprites[0] = _textManager->AddText(std::to_string(seconds), _position);
  _eventManager->After(std::chrono::seconds(seconds), [&ref, this]() {
    _textManager->RemoveText(ref._secondSprites[ref._secondSprites.size() - 1]);
    ref._callback();
  });
}

