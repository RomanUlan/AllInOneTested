#ifndef REACTOR_EE_HPP
#define REACTOR_EE_HPP

#include "EventEngine.hpp"
#include "EventEngines/Reactor.hpp"

class ReactorEE: public EventEngine {
public:
  ReactorEE(EventEngines::Reactor::Ptr);
  virtual ~ReactorEE();
  virtual void start();
  virtual void stop(bool);
private:
  EventEngines::Reactor::Ptr m_reactor;
};

#endif //REACTOR_EE_HPP
