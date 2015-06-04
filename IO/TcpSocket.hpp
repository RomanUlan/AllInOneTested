#ifndef TCP_SOCKET_ES_HPP
#define TCP_SOCKET_ES_HPP

#include "Socket.hpp"
#include <sys/socket.h>

class TcpSocket: public Socket
{
public:
  typedef std::shared_ptr<TcpSocket> Ptr;

public:
  TcpSocket();
  virtual ~TcpSocket();

public:
  virtual void bind(int);
  virtual void listen() const;
  virtual TcpSocket::Ptr accept() const;


protected:
  TcpSocket(int, const struct sockaddr&, socklen_t);

private:
  struct sockaddr m_address;
  socklen_t m_addressLength;
};

#endif
