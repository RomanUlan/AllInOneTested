#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include <memory>

class Socket
{
public:
  typedef std::shared_ptr<Socket> Ptr;
  typedef int Descriptor;

public:
  virtual ~Socket();

public:
  virtual Descriptor getDescriptor() const;
  virtual void setNonBlocking() const;
  virtual void read(std::string&) const;
  virtual void write(const std::string&) const;

protected:
  Socket(int, int, int);
  explicit Socket(int);
  Socket(const Socket&);
  Socket& operator=(const Socket&);

protected:
  Descriptor m_fd;
};

#endif
