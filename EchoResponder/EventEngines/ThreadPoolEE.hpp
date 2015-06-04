#ifndef THREAD_POOL_EE_HPP
#define THREAD_POOL_EE_HPP

#include "EventEngine.hpp"
#include "EventEngines/ThreadPool.hpp"

class ThreadPoolEE: public EventEngine {
public:
  ThreadPoolEE(EventEngines::ThreadPool::Ptr);
  virtual ~ThreadPoolEE();
  virtual void start();
  virtual void stop(bool);
private:
  EventEngines::ThreadPool::Ptr m_threadPool;
};

#endif //THREAD_POOL_EE_HPP
