//
// Copyright (c) 2009, Markus Rickert
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifdef WIN32
#include <windows.h>
#include <ws2tcpip.h>
#else // WIN32
#include <cerrno>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#ifdef __QNX__
#include <sys/select.h>
#endif // __QNX__
#include <sys/socket.h>
#include <sys/types.h>
#endif // WIN32

#include <cstring>
#include <sstream>
#include <boost/lexical_cast.hpp>

#include "ComException.h"
#include "Socket.h"
#include "TimeoutException.h"

namespace rl
{
	namespace hal
	{
		Socket::Socket(const int& domain, const int& type, const int& protocol, const ::std::string& address, const unsigned short int& port) :
			Com(),
#ifdef WIN32
			fd(INVALID_SOCKET),
#else // WIN32
			fd(-1),
#endif // WIN32
			address(address),
			domain(domain),
			port(port),
			protocol(protocol),
			type(type)
		{
#ifdef WIN32
			Socket::startup();
#endif // WIN32
		}
		
#ifdef WIN32
		Socket::Socket(const int& domain, const int& type, const int& protocol, const SOCKET& fd, const unsigned short int& port) :
#else // WIN32
		Socket::Socket(const int& domain, const int& type, const int& protocol, const int& fd, const unsigned short int& port) :
#endif // WIN32
			Com(),
			fd(fd),
			address(),
			domain(domain),
			port(port),
			protocol(protocol),
			type(type)
		{
#ifdef WIN32
			Socket::startup();
#endif // WIN32
			
			this->setConnected(true);
		}
		
		Socket::~Socket()
		{
			if (this->isConnected())
			{
				this->shutdown();
				this->close();
			}
			
#ifdef WIN32
			Socket::cleanup();
#endif // WIN32
		}
		
		Socket
		Socket::Tcp4(const ::std::string& address, const unsigned short int& port)
		{
			return Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, address, port);
		}
		
		Socket
		Socket::Tcp6(const ::std::string& address, const unsigned short int& port)
		{
			return Socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, address, port);
		}
		
		Socket
		Socket::Udp4(const ::std::string& address, const unsigned short int& port)
		{
			return Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, address, port);
		}
		
		Socket
		Socket::Udp6(const ::std::string& address, const unsigned short int& port)
		{
			return Socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, address, port);
		}
		
		Socket
		Socket::accept()
		{
#ifdef WIN32
			SOCKET fd = ::accept(this->fd, NULL, NULL);
#else // WIN32
			int fd = ::accept(this->fd, NULL, NULL);
#endif // WIN32
			
#ifdef WIN32
			if (INVALID_SOCKET == fd)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == fd)
			{
				throw ComException(errno);
			}
#endif // WIN32
			
			return Socket(this->domain, this->type, this->protocol, fd, this->port);
		}
		
		void
		Socket::bind()
		{
			::addrinfo hints;
			::memset(&hints, 0, sizeof(hints));
			hints.ai_family = this->domain;
			hints.ai_flags = AI_PASSIVE;
			hints.ai_socktype = this->type;
			::addrinfo* res;
			
			int err = ::getaddrinfo(this->address.empty() ? NULL : this->address.c_str(), ::boost::lexical_cast< ::std::string >(this->port).c_str(), &hints, &res);
			
			if (0 != err)
			{
				throw ComException(::gai_strerror(err));
			}
			
			err = ::bind(this->fd, res->ai_addr, res->ai_addrlen);
			::freeaddrinfo(res);
			
#ifdef WIN32
			if (SOCKET_ERROR == err)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == err)
			{
				throw ComException(errno);
			}
#endif // WIN32
		}
		
#ifdef WIN32
		void
		Socket::cleanup()
		{
			if (0 != ::WSACleanup())
			{
				throw ComException(::WSAGetLastError());
			}
		}
#endif // WIN32
		
		void
		Socket::close()
		{
#ifdef WIN32
			if (SOCKET_ERROR == ::closesocket(this->fd))
			{
				throw ComException(::WSAGetLastError());
			}
			
			this->fd = INVALID_SOCKET;
#else // WIN32
			if (-1 == ::close(this->fd))
			{
				throw ComException(errno);
			}
			
			this->fd = -1;
#endif // WIN32
			
			this->setConnected(false);
		}
		
		void
		Socket::connect()
		{
			::addrinfo hints;
			::memset(&hints, 0, sizeof(hints));
			hints.ai_family = this->domain;
			hints.ai_flags = AI_PASSIVE;
			hints.ai_socktype = this->type;
			::addrinfo* res;
			
			int err = ::getaddrinfo(this->address.c_str(), ::boost::lexical_cast< ::std::string >(this->port).c_str(), &hints, &res);
			
			if (0 != err)
			{
				throw ComException(::gai_strerror(err));
			}
			
			err = ::connect(this->fd, res->ai_addr, res->ai_addrlen);
			::freeaddrinfo(res);
			
#ifdef WIN32
			if (SOCKET_ERROR == err)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == err)
			{
				throw ComException(errno);
			}
#endif // WIN32
		}
		
		const ::std::string&
		Socket::getAddress() const
		{
			return this->address;
		}
		
		const int&
		Socket::getDomain() const
		{
			return this->domain;
		}
		
		const unsigned short int&
		Socket::getPort() const
		{
			return this->port;
		}
		
		const int&
		Socket::getProtocol() const
		{
			return this->protocol;
		}
		
		const int&
		Socket::getType() const
		{
			return this->type;
		}
		
		::std::string
		Socket::hostnameToAddress(const ::std::string& hostname)
		{
			return Socket::hostnameToAddress(hostname, AF_UNSPEC);
		}
		
		::std::string
		Socket::hostnameToAddress(const ::std::string& hostname, const int& type)
		{
#ifdef WIN32
			Socket::startup();
#endif // WIN32
			
			::addrinfo* res;
			int err = ::getaddrinfo(hostname.c_str(), NULL, NULL, &res);
			
			if (0 != err)
			{
#ifdef WIN32
				Socket::cleanup();
#endif // WIN32
				
				throw ComException(::gai_strerror(err));
			}
			
			char host[INET6_ADDRSTRLEN];
			
			switch (AF_UNSPEC == type ? res->ai_family : type)
			{
			case AF_INET:
				::sockaddr_in in;
				memset(&in, 0, sizeof(in));
				in.sin_family = AF_INET;
				memcpy(&in.sin_addr, &reinterpret_cast< ::sockaddr_in* >(res->ai_addr)->sin_addr, sizeof(in.sin_addr));
				err = ::getnameinfo(reinterpret_cast< ::sockaddr* >(&in), sizeof(in), host, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
				break;
			case AF_INET6:
				::sockaddr_in6 in6;
				memset(&in6, 0, sizeof(in6));
				in6.sin6_family = AF_INET6;
				memcpy(&in6.sin6_addr, &reinterpret_cast< ::sockaddr_in6* >(res->ai_addr)->sin6_addr, sizeof(in6.sin6_addr));
				err = ::getnameinfo(reinterpret_cast< ::sockaddr* >(&in6), sizeof(in6), host, INET6_ADDRSTRLEN, NULL, 0, NI_NUMERICHOST);
				break;
			default:
				host[0] = '\0';
				break;
			}
			
			::freeaddrinfo(res);
			
#ifdef WIN32
			Socket::cleanup();
#endif // WIN32
			
			if (0 != err)
			{
				throw ComException(::gai_strerror(err));
			}
			
			return host;
		}
		
		::std::string
		Socket::hostnameToAddress4(const ::std::string& hostname)
		{
			return Socket::hostnameToAddress(hostname, AF_INET);
		}
		
		::std::string
		Socket::hostnameToAddress6(const ::std::string& hostname)
		{
			return Socket::hostnameToAddress(hostname, AF_INET6);
		}
		
		void
		Socket::listen()
		{
			this->listen(SOMAXCONN);
		}
		
		void
		Socket::listen(const int& backlog)
		{
			int err = ::listen(this->fd, backlog);
			
#ifdef WIN32
			if (SOCKET_ERROR == err)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == err)
			{
				throw ComException(errno);
			}
#endif // WIN32
		}
		
		void
		Socket::open()
		{
			this->fd = ::socket(this->domain, this->type, this->protocol);
			
#ifdef WIN32
			if (INVALID_SOCKET == this->fd)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == this->fd)
			{
				throw ComException(errno);
			}
#endif // WIN32
			
			this->setConnected(true);
		}
		
		::std::size_t
		Socket::read(void* buf, const ::std::size_t& count)
		{
			::memset(buf, 0, count);
			
#ifdef WIN32
			int numbytes = ::recv(this->fd, static_cast< char* >(buf), count, 0);
#else // WIN32
			::ssize_t numbytes = ::recv(this->fd, buf, count, 0);
#endif // WIN32
			
#ifdef WIN32
			if (SOCKET_ERROR == numbytes)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == numbytes)
			{
				throw ComException(errno);
			}
#endif // WIN32
			
			return numbytes;
		}
		
		::std::size_t
		Socket::select(const bool& read, const bool& write, const ::rl::math::Real& timeout)
		{
			::timeval tv;
			tv.tv_sec = static_cast< long int >(timeout);
			tv.tv_usec = static_cast< long int >((timeout - tv.tv_sec) * 1000000.0f);
			
			::fd_set readfds;
			FD_ZERO(&readfds);
			FD_SET(this->fd, &readfds);
			
			::fd_set writefds;
			FD_ZERO(&writefds);
			FD_SET(this->fd, &writefds);
			
#ifdef WIN32
			int nfds = -1;
			int numdescriptors;
#else // WIN32
			int nfds = this->fd + 1;
			::ssize_t numdescriptors;
#endif // WIN32
			
			if (read && write)
			{
				numdescriptors = ::select(nfds, &readfds, &writefds, NULL, &tv);
			}
			else if (read)
			{
				numdescriptors = ::select(nfds, &readfds, NULL, NULL, &tv);
			}
			else if (write)
			{
				numdescriptors = ::select(nfds, NULL, &writefds, NULL, &tv);
			}
			else
			{
				numdescriptors = ::select(nfds, NULL, NULL, NULL, &tv);
			}
			
			if (0 == numdescriptors)
			{
				throw TimeoutException();
			}
#ifdef WIN32
			else if (SOCKET_ERROR == numdescriptors)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			else if (-1 == numdescriptors)
			{
				throw ComException(errno);
			}
#endif // WIN32
			
			return numdescriptors;
		}
		
		void
		Socket::setAddress(const ::std::string& address)
		{
			this->address = address;
		}
		
		void
		Socket::setPort(const unsigned short int& port)
		{
			this->port = port;
		}
		
		void
		Socket::shutdown(const bool& read, const bool& write)
		{
			int how;
			
			if (read && write)
			{
#ifdef WIN32
				how = SD_BOTH;
#else // WIN32
				how = SHUT_RDWR;
#endif // WIN32
			}
			else if (read)
			{
#ifdef WIN32
				how = SD_RECEIVE;
#else // WIN32
				how = SHUT_RD;
#endif // WIN32
			}
			else if (write)
			{
#ifdef WIN32
				how = SD_SEND;
#else // WIN32
				how = SHUT_WR;
#endif // WIN32
			}
			else
			{
				return;
			}
			
#ifdef WIN32
			if (SOCKET_ERROR == ::shutdown(this->fd, how))
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == ::shutdown(this->fd, how))
			{
				throw ComException(errno);
			}
#endif // WIN32
		}
		
#ifdef WIN32
		void
		Socket::startup()
		{
			::WSADATA wsaData;
			
			int err = ::WSAStartup(MAKEWORD(1, 1), &wsaData);
			
			if (0 != err)
			{
				throw ComException(err);
			}
			
			if ((1 != LOBYTE(wsaData.wVersion)) || (1 != HIBYTE(wsaData.wVersion)))
			{
				if (0 != ::WSACleanup())
				{
					throw ComException(::WSAGetLastError());
				}
				
				throw ComException("Requested Windows sockets version not supported");
			}
		}
#endif // WIN32
		
		::std::size_t
		Socket::write(const void* buf, const ::std::size_t& count)
		{
#ifdef WIN32
			int numbytes = ::send(this->fd, static_cast< const char* >(buf), count, 0);
#else // WIN32
			::ssize_t numbytes = ::send(this->fd, buf, count, 0);
#endif // WIN32
			
#ifdef WIN32
			if (SOCKET_ERROR == numbytes)
			{
				throw ComException(::WSAGetLastError());
			}
#else // WIN32
			if (-1 == numbytes)
			{
				throw ComException(errno);
			}
#endif // WIN32
			
			return numbytes;
		}
	}
}
