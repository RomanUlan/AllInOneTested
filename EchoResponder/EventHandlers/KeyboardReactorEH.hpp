#ifndef KEYBOARD_EH_HPP
#define KEYBOARD_EH_HPP

#include "KeyboardEH.hpp"

class KeyboardReactorEH : public KeyboardEH
{
public:
  KeyboardReactorEH(const std::string&, KeyboardES::Ptr);
  virtual ~KeyboardReactorEH();

public:
  virtual void finalize();
};

#endif
