#ifndef REACTOR_HPP
#define REACTOR_HPP

#include "EventHandler.hpp"
#include "EventDemultiplexer.hpp"

#include <map>
#include <mutex>
namespace EventEngines {
class Reactor
{
public:
  typedef std::shared_ptr<Reactor> Ptr;

public:
  explicit Reactor(EventDemultiplexer::Ptr);
  ~Reactor();

  void add(EventHandler::Ptr);
  void modify(EventSource::Ptr);
  void remove(EventSource::Descriptor);
  void eventLoop();
  void interrupt(bool);

private:
  Reactor(const Reactor&);
  Reactor& operator=(const Reactor&);

private:
  typedef std::map<EventSource::Descriptor, EventHandler::Ptr> t_handlers;
  typedef std::pair<EventHandler::Ptr, EventSource::EventTypes> t_toHandle;
  typedef std::vector<t_toHandle> t_toHandles;

  std::mutex m_mutex;
  bool m_run;
  t_handlers m_handlers;
  EventDemultiplexer::Ptr m_eventDemultiplexer;
};
}

#endif
