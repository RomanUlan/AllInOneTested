#ifndef ECHO_RESPONDER_EH_HPP
#define ECHO_RESPONDER_EH_HPP

#include "EventEngines/ThreadPool.hpp"
#include "MessageES.hpp"
#include "IO/Epoll.hpp"
#include <boost/algorithm/string.hpp>

template <class EventEngine>
class EchoResponderEH : public EventHandler
{
public:
  EchoResponderEH(MessageES::Ptr, EventEngine&);
  virtual ~EchoResponderEH();

public:
  virtual void handle(const EventSource::EventTypes&);

private:
  EventEngine& m_ee;
};

template<class EE>
EchoResponderEH<EE>::EchoResponderEH(MessageES::Ptr p_messageES, EE& p_ee)
  : EventHandler(p_messageES), m_ee(p_ee)
{
}

template<class EE>
EchoResponderEH<EE>::~EchoResponderEH()
{
}

template<class EE>
void EchoResponderEH<EE>::handle(const EventSource::EventTypes& p_eventTypes)
{
  EventSource::EventTypes::const_iterator iIn = p_eventTypes.find(Epoll::EventType::In);
  if ( (iIn != p_eventTypes.end()) && (p_eventTypes.size() == 1) )
  {
    MessageES::Ptr mES = std::dynamic_pointer_cast<MessageES>(m_eventSource);
    std::string data;
    while (!boost::ends_with(data, "\n"))
    {
      std::string part;
      mES->read(part);
      data.append(part);
    }
    mES->getSocket()->write(data);
    m_ee.modify(m_eventSource);
  }
  else
  {
    m_ee.remove(m_eventSource->getDescriptor());
  }
}

#endif
