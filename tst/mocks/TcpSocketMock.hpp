#ifndef TCP_SOCKET_MOCK_HPP
#define TCP_SOCKET_MOCK_HPP

#include "TcpSocket.hpp"
#include "gmock/gmock.h"

class TcpSocketMock: public TcpSocket {
public:
  typedef std::shared_ptr<TcpSocketMock> Ptr;
  TcpSocketMock(int);
  virtual ~TcpSocketMock();
  MOCK_CONST_METHOD0(getDescriptor, Descriptor(void));
  MOCK_CONST_METHOD0(setNonBlocking, void(void));
  MOCK_CONST_METHOD1(read, void(std::string&));
  MOCK_CONST_METHOD1(write, void(const std::string&));
  MOCK_METHOD1(bind, void(int));
  MOCK_CONST_METHOD0(listen, void(void));
  MOCK_CONST_METHOD0(accept, TcpSocket::Ptr(void));
};

#endif //TCP_SOCKET_MOCK_HPP
