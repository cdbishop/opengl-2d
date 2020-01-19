#include "EventManager.hpp"

#include <algorithm>

EventManager::EventManager() {}

EventManager::~EventManager() {}

void EventManager::Update() {
  auto now = EventManager::Clock::now();

  _after_events.erase(std::remove_if(_after_events.begin(), _after_events.end(),
    [&now](EventManager::AfterPair event) {
    if (now >= event.first) {
      event.second();
      return true;
    }

    return false;
  }),
    _after_events.end());
}
