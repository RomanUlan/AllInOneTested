#include "EventEngineFactory.hpp"

#include "HalfSyncHalfAsyncEE.hpp"
#include "AcceptorSEH.hpp"
#include "KeyboardSEH.hpp"

#include "ThreadPoolEE.hpp"
#include "AcceptorEH.hpp"
#include "KeyboardTPEH.hpp"

#include "ReactorEE.hpp"
#include "KeyboardReactorEH.hpp"

EventEngine::Ptr EventEngineFactory::create(const Config& p_config)
{
  EventEngine::Ptr result;
  switch (p_config.eventEngineType) {
  case Config::ThreadPool:
    result = createTP(p_config);
    break;
  case Config::HalfSyncHalfAsync:
    result = createHSHA(p_config);
    break;
  default:
    result = createReactor(p_config);
  }

  return result;
}

EventEngine::Ptr EventEngineFactory::createReactor(const Config& p_config)
{
  Epoll::Ptr epoll(new Epoll());
  EpollED::Ptr epollED(new EpollED(epoll));
  EventEngines::Reactor::Ptr r(new EventEngines::Reactor(epollED));

  KeyboardSocket::Ptr keybSocket(new KeyboardSocket());
  KeyboardES::Ptr keybES(new KeyboardES(keybSocket));
  EventHandler::Ptr keybEH(new KeyboardReactorEH("log.txt", keybES));

  TcpSocket::Ptr listenerSokcet(new TcpSocket());
  ListenerES::Ptr listenerES(new ListenerES(listenerSokcet, p_config.port));
  EventHandler::Ptr acceptorEH(new AcceptorEH<EventEngines::Reactor>(listenerES, *r));

  r->add(keybEH);
  r->add(acceptorEH);

  return EventEngine::Ptr(new ReactorEE(r));
}

EventEngine::Ptr EventEngineFactory::createTP(const Config& p_config)
{
  Epoll::Ptr epoll(new Epoll());
  EpollED::Ptr epollED(new EpollED(epoll));
  EventEngines::ThreadPool::Ptr tp(new EventEngines::ThreadPool(epollED, p_config.eventEngineSize));

  KeyboardSocket::Ptr keybSocket(new KeyboardSocket());
  KeyboardES::Ptr keybES(new KeyboardES(keybSocket));
  EventHandler::Ptr keybEH(new KeyboardTPEH("log.txt", keybES, *tp));

  TcpSocket::Ptr listenerSokcet(new TcpSocket());
  ListenerES::Ptr listenerES(new ListenerES(listenerSokcet, p_config.port));
  EventHandler::Ptr acceptorEH(new AcceptorEH<EventEngines::ThreadPool>(listenerES, *tp));

  tp->add(keybEH);
  tp->add(acceptorEH);

  return EventEngine::Ptr(new ThreadPoolEE(tp));
}

EventEngine::Ptr EventEngineFactory::createHSHA(const Config& p_config)
{
  Epoll::Ptr epoll(new Epoll());
  EpollED::Ptr epollED(new EpollED(epoll));
  HSHA::Ptr hsha(new HSHA(epollED, p_config.eventEngineSize));

  KeyboardSocket::Ptr keybSocket(new KeyboardSocket());
  KeyboardES::Ptr keybES(new KeyboardES(keybSocket));
  SEH::Ptr keybSEH(new KeyboardSEH("log.txt", keybES));
  AEH::Ptr keybAEH;
  HSHA::Handlers keybHandlers(keybSEH, keybAEH);

  TcpSocket::Ptr listenerSokcet(new TcpSocket());
  ListenerES::Ptr listenerES(new ListenerES(listenerSokcet, p_config.port));
  SEH::Ptr acceptorSEH(new AcceptorSEH(listenerES, *hsha));
  AEH::Ptr acceptorAEH;
  HSHA::Handlers acceptorHandlers(acceptorSEH, acceptorAEH);

  hsha->add(keybHandlers);
  hsha->add(acceptorHandlers);

  return EventEngine::Ptr(new HalfSyncHalfAsyncEE(hsha));
}
