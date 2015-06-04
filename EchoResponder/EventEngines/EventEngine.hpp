#ifndef EVENT_ENGINE_HPP
#define EVENT_ENGINE_HPP

#include <memory>
#include <thread>

class EventEngine {
public:
  typedef std::shared_ptr<EventEngine> Ptr;
  virtual ~EventEngine() {};
  virtual void start() = 0;
  virtual void stop(bool) = 0;
};

#endif //EVENT_ENGINE_HPP
