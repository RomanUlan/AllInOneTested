#include "ConfigParser.hpp"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

ConfigParser::ConfigParser(int p_argc, char** p_argv)
  : m_argc(p_argc), m_argv(p_argv)
{

}

ConfigParser::~ConfigParser()
{
}

Config ConfigParser::get() const
{
  Config c;
  c.eventEngineType = Config::Reactor;
  c.eventEngineSize = 1;
  c.port = 5050;

  int o;
  while((o = getopt(m_argc, m_argv, "e:s:p:")) != EOF) {
    switch (o) {
    case 'e':
      if (strcmp(optarg, "reacor") == 0)
        c.eventEngineType = Config::Reactor;
      else if (strcmp(optarg, "tp") == 0)
        c.eventEngineType = Config::ThreadPool;
      else if (strcmp(optarg, "hsha") == 0)
        c.eventEngineType = Config::HalfSyncHalfAsync;
      else
        throw std::runtime_error("Not supported engine type");
      break;
    case 's':
      c.eventEngineSize = atoi(optarg);
      break;
    case 'p':
      c.port = atoi(optarg);
    }
  }
  return c;
}
