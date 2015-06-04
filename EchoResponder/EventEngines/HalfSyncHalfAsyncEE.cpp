#include "HalfSyncHalfAsyncEE.hpp"
#include "iostream"

HalfSyncHalfAsyncEE::HalfSyncHalfAsyncEE(HSHA::Ptr p_hsha)
  : m_hsha(p_hsha)
{
}

HalfSyncHalfAsyncEE::~HalfSyncHalfAsyncEE()
{
}

void HalfSyncHalfAsyncEE::start()
{
  m_hsha->eventLoop();
}

void HalfSyncHalfAsyncEE::stop(bool p_immediately)
{
  m_hsha->interrupt(p_immediately);
}
