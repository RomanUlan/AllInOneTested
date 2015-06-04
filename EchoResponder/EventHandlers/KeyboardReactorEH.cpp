#include "KeyboardReactorEH.hpp"

#include <stdexcept>

KeyboardReactorEH::KeyboardReactorEH(const std::string& p_fileName, KeyboardES::Ptr p_kES)
  : KeyboardEH(p_fileName, p_kES)
{
}

KeyboardReactorEH::~KeyboardReactorEH()
{
}

void KeyboardReactorEH::finalize()
{
  throw std::runtime_error("exit");
}
