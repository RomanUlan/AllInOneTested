#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include "Config.hpp"

class ConfigParser {
public:
  ConfigParser(int p_argc, char** p_argv);
  ~ConfigParser();
  Config get() const;
private:
  int m_argc;
  char** m_argv;
};

#endif //CONFIG_PARSER_HPP
