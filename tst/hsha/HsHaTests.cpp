#include "HsHaTests.hpp"
#include "EventHandlers/BaseTypes.hpp"
#include "EpollMock.hpp"
#include "TcpSocketMock.hpp"
#include "EventSources/ListenerES.hpp"
#include "EventHandlers/AcceptorSEH.hpp"

using namespace ::testing;

void HsHaTests::SetUp()
{
}

void HsHaTests::TearDown()
{
}

TEST_F(HsHaTests, acceptThrowsRuntimeError)
{
  int listenerFd = 5;
  int port = 5555;

  Epoll::EventTypes ets;
  ets.insert(Epoll::EventType::In);
  Epoll::Event ev(ets, listenerFd);
  Epoll::Events es;
  es.push_back(ev);

  EpollMock::Ptr e(new EpollMock());
  TcpSocketMock::Ptr l(new TcpSocketMock(listenerFd));

  EXPECT_CALL(*l, bind(port)).Times(1);
  EXPECT_CALL(*l, listen()).Times(1);
  EXPECT_CALL(*l, setNonBlocking()).Times(1);
  EXPECT_CALL(*l, getDescriptor()).WillOnce(Return(listenerFd));
  EXPECT_CALL(*l, accept()).WillOnce(Throw(std::runtime_error("error")));

  EXPECT_CALL(*e, add(_, _)).Times(1);
  EXPECT_CALL(*e, wait(_)).WillOnce(SetArgReferee<0>(es));

  EpollED::Ptr eed(new EpollED(e));
  HSHA::Ptr hsha(new HSHA(eed, 1000));
  ListenerES::Ptr les(new ListenerES(l, port));
  SEH::Ptr seh(new AcceptorSEH(les, *hsha));
  AEH::Ptr aeh;
  HSHA::Handlers ah(seh, aeh);

  hsha->add(ah);

  EXPECT_THROW(hsha->eventLoop(), std::runtime_error);
}

TEST_F(HsHaTests, echoSuccess)
{
  int listenerFd = 5;
  int clientFd = 6;
  int port = 5555;
  std::string msg = "msg\n";

  Epoll::EventTypes ets;
  ets.insert(Epoll::EventType::In);
  Epoll::Event sev(ets, listenerFd);
  Epoll::Event cev(ets, clientFd);
  Epoll::Events ses;
  Epoll::Events ces;
  ses.push_back(sev);
  ces.push_back(cev);

  EpollMock::Ptr e(new EpollMock());
  TcpSocketMock::Ptr l(new TcpSocketMock(listenerFd));
  TcpSocketMock::Ptr c(new TcpSocketMock(clientFd));

  EXPECT_CALL(*l, bind(port)).Times(1);
  EXPECT_CALL(*l, listen()).Times(1);
  EXPECT_CALL(*l, setNonBlocking()).Times(1);
  EXPECT_CALL(*l, getDescriptor()).WillOnce(Return(listenerFd));
  EXPECT_CALL(*l, accept()).WillOnce(Return(c));

  EXPECT_CALL(*c, setNonBlocking()).Times(1);
  EXPECT_CALL(*c, getDescriptor()).WillRepeatedly(Return(clientFd));
  EXPECT_CALL(*c, read(_)).WillOnce(SetArgReferee<0>(msg));
  EXPECT_CALL(*c, write(msg)).Times(1);

  EXPECT_CALL(*e, add(_, _)).Times(2);
  EXPECT_CALL(*e, wait(_)).Times(3)
                          .WillOnce(SetArgReferee<0>(ses))
									        .WillOnce(SetArgReferee<0>(ces))
									        .WillOnce(Throw(std::runtime_error("error")));
  EXPECT_CALL(*e, modify(_, _)).Times(2);

  EpollED::Ptr eed(new EpollED(e));
  HSHA::Ptr hsha(new HSHA(eed, 1000));
  ListenerES::Ptr les(new ListenerES(l, port));
  SEH::Ptr seh(new AcceptorSEH(les, *hsha));
  AEH::Ptr aeh;
  HSHA::Handlers ah(seh, aeh);

  hsha->add(ah);

  EXPECT_THROW(hsha->eventLoop(), std::runtime_error);
}
