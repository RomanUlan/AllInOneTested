#include "KeyboardTPEH.hpp"


KeyboardTPEH::KeyboardTPEH(const std::string& p_fileName, KeyboardES::Ptr p_kES, EventEngines::ThreadPool& p_tp)
  : KeyboardEH(p_fileName, p_kES)
  , m_threadPool(p_tp)
{
}

KeyboardTPEH::~KeyboardTPEH()
{
}

void KeyboardTPEH::finalize()
{
  m_threadPool.interrupt(true);
}
