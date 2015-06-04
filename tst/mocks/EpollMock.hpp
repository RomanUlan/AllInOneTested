#ifndef EPOLL_MOCK_HPP
#define EPOLL_MOCK_HPP

#include "Epoll.hpp"
#include "gmock/gmock.h"

class EpollMock: public Epoll {
public:
	typedef std::shared_ptr<EpollMock> Ptr;
	EpollMock();
	virtual ~EpollMock ();

	MOCK_CONST_METHOD2(add, void(Socket::Ptr, const EventTypes&));
	MOCK_CONST_METHOD2(modify, void(Socket::Ptr, const EventTypes&));
	MOCK_CONST_METHOD1(remove, void(Socket::Descriptor));
	MOCK_CONST_METHOD1(wait, void(Events&));
	MOCK_CONST_METHOD0(interrupt, void(void));
};

#endif //EPOLL_MOCK_HPP

