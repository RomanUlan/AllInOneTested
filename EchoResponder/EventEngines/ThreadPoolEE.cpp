#include "ThreadPoolEE.hpp"

ThreadPoolEE::ThreadPoolEE(EventEngines::ThreadPool::Ptr p_threadPool)
  : m_threadPool(p_threadPool)
{
}

ThreadPoolEE::~ThreadPoolEE()
{
}

void ThreadPoolEE::start()
{
  m_threadPool->eventLoop();
}

void ThreadPoolEE::stop(bool p_immediately)
{
  m_threadPool->interrupt(p_immediately);
}
