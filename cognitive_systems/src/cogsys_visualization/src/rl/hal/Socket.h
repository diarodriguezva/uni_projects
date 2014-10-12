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

#ifndef _RL_HAL_SOCKET_H_
#define _RL_HAL_SOCKET_H_

#ifdef WIN32
#include <winsock2.h>
#endif // WIN32

#include <string>
#include <rl/math/Real.h>

#include "Com.h"

namespace rl
{
	namespace hal
	{
		class Socket : public Com
		{
		public:
			static Socket Tcp4(const ::std::string& address, const unsigned short int& port);
			
			static Socket Tcp6(const ::std::string& address, const unsigned short int& port);
			
			static Socket Udp4(const ::std::string& address, const unsigned short int& port);
			
			static Socket Udp6(const ::std::string& address, const unsigned short int& port);
			
			virtual ~Socket();
			
			Socket accept();
			
			void bind();
			
			void close();
			
			void connect();
			
			const ::std::string& getAddress() const;
			
			const int& getDomain() const;
			
			const unsigned short int& getPort() const;
			
			const int& getProtocol() const;
			
			const int& getType() const;
			
			static ::std::string hostnameToAddress(const ::std::string& hostname);
			
			static ::std::string hostnameToAddress4(const ::std::string& hostname);
			
			static ::std::string hostnameToAddress6(const ::std::string& hostname);
			
			void listen();
			
			void listen(const int& backlog);
			
			void open();
			
			::std::size_t read(void* buf, const ::std::size_t& count);
			
			::std::size_t select(const bool& read, const bool& write, const ::rl::math::Real& timeout);
			
			void setAddress(const ::std::string& address);
			
			void setPort(const unsigned short int& port);
			
			void shutdown(const bool& read = true, const bool& write = true);
			
			::std::size_t write(const void* buf, const ::std::size_t& count);
			
		protected:
			Socket(const int& domain, const int& type, const int& protocol, const ::std::string& address, const unsigned short int& port);
			
#ifdef WIN32
			Socket(const int& domain, const int& type, const int& protocol, const SOCKET& fd, const unsigned short int& port);
#else // WIN32
			Socket(const int& domain, const int& type, const int& protocol, const int& fd, const unsigned short int& port);
#endif // WIN32
			
#ifdef WIN32
			static void cleanup();
#endif // WIN32
			
			static ::std::string hostnameToAddress(const ::std::string& hostname, const int& type);
			
#ifdef WIN32
			static void startup();
#endif // WIN32
			
#ifdef WIN32
			SOCKET fd;
#else // WIN32
			int fd;
#endif // WIN32
			
		private:
			::std::string address;
			
			int domain;
			
			unsigned short int port;
			
			int protocol;
			
			int type;
		};
	}
}

#endif // _RL_HAL_SOCKET_H_
