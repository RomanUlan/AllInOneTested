#ifndef EVENT_ENGINE_FACTORY_HPP
#define EVENT_ENGINE_FACTORY_HPP

#include "EventEngine.hpp"
#include "Config.hpp"

class EventEngineFactory {
public:
  static EventEngine::Ptr create(const Config&);
private:
  static EventEngine::Ptr createReactor(const Config&);
  static EventEngine::Ptr createTP(const Config&);
  static EventEngine::Ptr createHSHA(const Config&);
};

#endif //EVENT_ENGINE_FACTORY_HPP
