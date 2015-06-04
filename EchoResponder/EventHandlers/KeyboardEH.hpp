#ifndef KEYBOARD_EE_HPP
#define KEYBOARD_EE_HPP

#include "EventEngines/EventHandler.hpp"
#include "KeyboardES.hpp"
#include <fstream>

class KeyboardEH : public EventHandler
{
public:
  KeyboardEH(const std::string&, KeyboardES::Ptr);
  virtual ~KeyboardEH();

public:
  virtual void handle(const EventSource::EventTypes&);
  virtual void finalize() = 0;

private:
  std::ofstream m_file;
};

#endif //KEYBOARD_EE_HPP
