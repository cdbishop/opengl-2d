#pragma once
#include <chrono>
#include <functional>

class EventManager {
public:
  using Id = size_t;
  using Clock = std::chrono::system_clock;
  using AfterFn = std::function<void()>;
  using Ptr = std::shared_ptr<EventManager>;

  EventManager();

  ~EventManager();

  template <typename Rep>
  Id After(std::chrono::duration<Rep> offset, AfterFn callback) {
    _after_events.emplace_back(EventManager::Clock::now() + offset, callback);
    return _after_events.size() - 1;
  }

  template <typename Rep>
  Id After(Id event, std::chrono::duration<Rep> offset, AfterFn callback) {
    return After(_after_events[event].first + offset, callback);
  }

  void Update();

private:
  using AfterPair = std::pair<Clock::time_point, AfterFn>;
  std::vector<AfterPair> _after_events;
};