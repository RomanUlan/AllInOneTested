#ifndef ACCEPTOR_EH_HPP
#define ACCEPTOR_EH_HPP

#include "EventEngines/ThreadPool.hpp"
#include "ListenerES.hpp"
#include "EchoResponderEH.hpp"

template <typename EventEngine>
class AcceptorEH : public EventHandler
{
public:
  AcceptorEH(ListenerES::Ptr, EventEngine&);
  virtual ~AcceptorEH();

public:
  virtual void handle(const EventSource::EventTypes&);

private:
  EventEngine& m_ee;
};

template <typename EE>
AcceptorEH<EE>::AcceptorEH(ListenerES::Ptr p_listenerES, EE& p_ee)
  : EventHandler(p_listenerES)
  , m_ee(p_ee)
{
}

template <typename EE>
AcceptorEH<EE>::~AcceptorEH()
{
}

template <typename EE>
void AcceptorEH<EE>::handle(const EventSource::EventTypes& p_eventTypes)
{
  EventSource::EventTypes::const_iterator iIn = p_eventTypes.find(Epoll::EventType::In);
  if ( (iIn != p_eventTypes.end()) && (p_eventTypes.size() == 1) )
  {
    ListenerES::Ptr listenerES = std::dynamic_pointer_cast<ListenerES>(m_eventSource);
    MessageES::Ptr msgES = listenerES->accept();
    typename EchoResponderEH<EE>::Ptr erEH(new EchoResponderEH<EE>(msgES, m_ee));
    m_ee.add(erEH);
    m_ee.modify(m_eventSource);
  }
  else
  {
    throw std::runtime_error("Bad event for for acceptor");
  }
}

#endif
