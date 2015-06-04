#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <cstddef>

struct Config {
  enum EventEngineType {
    Reactor = 0,
    ThreadPool = 1,
    HalfSyncHalfAsync = 2
  };

  EventEngineType eventEngineType;
  size_t eventEngineSize;
  int port;
};

#endif //CONFIG_HPP
