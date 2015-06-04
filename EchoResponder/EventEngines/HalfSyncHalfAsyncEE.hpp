#ifndef HALF_SYNC_HALF_ASYNC_EE_HPP
#define HALF_SYNC_HALF_ASYNC_EE_HPP

#include "EventEngine.hpp"
#include "BaseTypes.hpp"

class HalfSyncHalfAsyncEE: public EventEngine {
public:
  HalfSyncHalfAsyncEE(HSHA::Ptr);
  virtual ~HalfSyncHalfAsyncEE();
  virtual void start();
  virtual void stop(bool);
private:
  HSHA::Ptr m_hsha;
};

#endif //HALF_SYNC_HALF_ASYNC_EE_HPP
