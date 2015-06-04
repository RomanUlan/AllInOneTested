#include "ReactorEE.hpp"

ReactorEE::ReactorEE(EventEngines::Reactor::Ptr p_reactor)
  : m_reactor(p_reactor)
{
}

ReactorEE::~ReactorEE()
{
}

void ReactorEE::start()
{
  m_reactor->eventLoop();
}

void ReactorEE::stop(bool p_immediately)
{
  m_reactor->interrupt(p_immediately);
}
