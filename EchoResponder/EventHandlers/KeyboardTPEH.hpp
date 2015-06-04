#ifndef KEYBOARDTP_EH_HPP
#define KEYBOARDTP_EH_HPP

#include "KeyboardEH.hpp"
#include "EventEngines/ThreadPool.hpp"

class KeyboardTPEH : public KeyboardEH
{
public:
  KeyboardTPEH(const std::string&, KeyboardES::Ptr, EventEngines::ThreadPool&);
  virtual ~KeyboardTPEH();

public:
  virtual void finalize();

private:
  EventEngines::ThreadPool& m_threadPool;
};

#endif
