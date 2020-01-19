#include "onScreenCountdown.hpp"
#include <game/onScreenCountdown.hpp>

OnScreenCountdown::OnScreenCountdown(TextManager::Ptr textManager,
                                     glm::vec2 position, std::string prefix)
    : _textManager(textManager),
      _position(position),
      _prefix(std::move(prefix)),
      _countDown(nullptr) {
  _eventManager = std::make_shared<EventManager>();
}

OnScreenCountdown::~OnScreenCountdown() {}

void OnScreenCountdown::Update() { _eventManager->Update(); }

void OnScreenCountdown::StartCountdown(unsigned int seconds, Callback cb) {
  if (_countDown) {
    throw std::invalid_argument("Already got countdown");
  }

  _countDown = std::make_shared<CountDown>();
  _countDown->_secondSprites.resize(seconds);
  _countDown->_callback = cb;

  //_countdowns.push_back(cd);
  //_countDown = cd;

  // CountDown& ref = _countdowns[_countdowns.size() - 1];
  // CountDown& ref = cd;

  auto updateCallack = [this](unsigned int second, unsigned int index) {
    _textManager->RemoveText(_countDown->_secondSprites[index - 1]);
    _countDown->_secondSprites[index] =
        _textManager->AddText(_prefix + std::to_string(second), _position);
  };

  for (unsigned int i = 1; i < seconds; ++i) {
    _eventManager->After(std::chrono::seconds(i),
                         std::bind(updateCallack, seconds - i, i));
  }

  _countDown->_secondSprites[0] =
      _textManager->AddText(_prefix + std::to_string(seconds), _position);
  _eventManager->After(std::chrono::seconds(seconds), [this]() {
    _textManager->RemoveText(
        _countDown->_secondSprites[_countDown->_secondSprites.size() - 1]);
    _countDown->_callback();
    _countDown = nullptr;
  });
}
