#include "TcpSocketMock.hpp"

TcpSocketMock::TcpSocketMock(int p_fd)
  : TcpSocket(p_fd, sockaddr(), sizeof(struct sockaddr))
{
}

TcpSocketMock::~TcpSocketMock()
{
}
