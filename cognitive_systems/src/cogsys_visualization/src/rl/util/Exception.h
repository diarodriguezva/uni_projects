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

#ifndef _RL_UTIL_EXCEPTION_H_
#define _RL_UTIL_EXCEPTION_H_

#ifdef WIN32
#include <windows.h>
#endif // WIN32

#include <cstring>
#include <sstream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

namespace rl
{
	namespace util
	{
		class Exception : public ::std::runtime_error
		{
		public:
			Exception(const ::std::string& what_arg) :
				::std::runtime_error(what_arg)
			{
			}
			
			Exception(const int& errnum) :
				::std::runtime_error(Exception::strerror(errnum))
			{
			}
			
			virtual ~Exception() throw()
			{
			}
			
			static ::std::string strerror(const int& errnum)
			{
#ifdef WIN32
				::LPTSTR buffer = NULL;
				::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errnum, 0, buffer, 0, NULL);
				::std::string message = NULL != buffer ? buffer : ::boost::lexical_cast< ::std::string >(errnum);
				::LocalFree(buffer);
				return message;
#else // WIN32
				return ::strerror(errnum);
#endif // WIN32
			}
			
		protected:
			
		private:
			
		};
	}
}

#endif // _RL_UTIL_EXCEPTION_H_
