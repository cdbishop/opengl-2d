#include "onScreenCountdown.hpp"
#include <game/onScreenCountdown.hpp>

OnScreenCountdown::OnScreenCountdown(TextManager::Ptr textManager,
  glm::vec2 position, std::string prefix)
  : _textManager(textManager),
  _position(std::move(position)),
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

  // define update function to remove previous sprite number + display next number in countdown
  auto updateCallack = [this](unsigned int second, unsigned int index) {
    _textManager->RemoveText(_countDown->_secondSprites[index - 1]);
    _countDown->_secondSprites[index] =
      _textManager->AddText(_prefix + std::to_string(second), _position);
  };

  // Add delays for the subsequent numbers
  for (unsigned int i = 1; i < seconds; ++i) {
    _eventManager->After(std::chrono::seconds(i),
      std::bind(updateCallack, seconds - i, i));
  }

  // setup the initial number
  _countDown->_secondSprites[0] =
    _textManager->AddText(_prefix + std::to_string(seconds), _position);

  // handle last value
  _eventManager->After(std::chrono::seconds(seconds), [this]() {
    _textManager->RemoveText(
      _countDown->_secondSprites[_countDown->_secondSprites.size() - 1]);
    _countDown->_callback();
    _countDown = nullptr;
  });
}
