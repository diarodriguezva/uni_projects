/** BEGIN LICENSE ************************************************************/
//    Copyright (C) 2011-2012 by Cognition Factory GmbH (CF)
//    All rights reserved.
//    Contact: info@cognitionfactory.de
//
//    This file is part of the cf framework.
//
//    Commercial Usage:
//      Licensees holding valid commercial licenses may use this file in
//      accordance with the commercial license agreement provided with the
//      software or, alternatively, in accordance with the terms contained in
//      a written agreement with CF.
//
//    GNU General Public License Usage:
//      Alternatively, this file may be used under the terms of the GNU
//      General Public License version 3.0 as published by the Free Software
//      Foundation and appearing in the file LICENSE.GPL3 included in the
//      packaging of this file. Please review the following information to
//      ensure the GNU General Public License version 3.0 requirements will be
//      met: http://www.gnu.org/copyleft/gpl.html.
//      Alternatively you may (at your option) use any later version of the GNU
//      General Public License if such license has been publicly approved by
//      CF (or its successors, if any).
//
//    Please note third party software included with the framework may impose
//    additional restrictions and it is the user's responsibility to ensure
//    that they have met the licensing requiremens of all effective licenses
//    they are using.
//
//    IN NO EVENT SHALL "CF" BE LIABLE TO ANY PARTY FOR DIRECT,
//    INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF
//    THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF "CF"
//    HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//    "CF" SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
//    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//    FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE PROVIDED HEREUNDER IS
//    ON AN "AS IS" BASIS, AND "CF" HAVE NO OBLIGATION TO
//    PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS OR MODIFICATIONS.
/** END LICENSE **************************************************************/

#ifndef CF_LOGGING_MACROS
#define CF_LOGGING_MACROS


/*
 * EXAMPLE TEST CODE:
 *
#include <iostream>
#include "logging.hpp"

std::string createText()
{
        LOG(DBG) << __FUNCTION__ << std::endl;
        return " Oh happy day..";
}

int main(int argc, char** argv)
{
        LOG(NON) << "loggingnone" << createText() << std::endl;
        LOG(DBG) << "loggingdebug" << createText() << std::endl;
        LOG(INF) << "logginginfo" << createText() << std::endl;


        Logging::setLogFile("LOG.TXT");
    Logging::setLogStream(&std::cerr);

        LOG(WARN) << "loggingwarning" << createText() << std::endl;
        LOG(ERR) << "loggingerror" << createText() << std::endl;
        LOG_IF(INF, 2 == 1) << "logginginfo" << createText() << std::endl;
        DLOG(DBG) << "loggingdebug" << createText() << std::endl;

        return 0;
}
*/

#include <iostream>
#include <streambuf>
#include <ostream>
#include <fstream>
#include <assert.h>


#define CFLOG_NON     0
#define CFLOG_DBG     1
#define CFLOG_INF     2
#define CFLOG_WARN    3
#define CFLOG_ERR     4

#ifndef LOG_STRIP_UP_TO_LEVEL
    #define LOG_STRIP_UP_TO_LEVEL CFLOG_NON
#endif

#ifndef LOG_DEFAULT_STREAM
    #define LOG_DEFAULT_STREAM std::cerr
#endif


template <class cT, class traits = std::char_traits<cT> >
class basic_nullbuf: public std::basic_streambuf<cT, traits>
{
    typename traits::int_type overflow(typename traits::int_type c)
    {
        return traits::not_eof(c); // indicate success
    }
};

template <class cT, class traits = std::char_traits<cT> >
class basic_onullstream: public std::basic_ostream<cT, traits>
{
    public:
        basic_onullstream():
            std::basic_ios<cT, traits>(&m_sbuf),
            std::basic_ostream<cT, traits>(&m_sbuf)
        {
            this->init(&m_sbuf);
        }

    private:
        basic_nullbuf<cT, traits> m_sbuf;
};

typedef basic_onullstream<char> onullstream;
typedef basic_onullstream<wchar_t> wonullstream;

static std::ostream* log_internal_stream = &LOG_DEFAULT_STREAM;


template<unsigned int V>
struct logging_
{
    static inline std::ostream& log(const char* file, const int line)
    {
        assert(0);
        std::cerr << "UNKN " << file << ":" << line << ": LOGGING LEVEL " << V << " IGNORED. >" << LOG_STRIP_UP_TO_LEVEL << std::endl;
        static onullstream o;
        return o;
    }
};

#if CFLOG_DBG>LOG_STRIP_UP_TO_LEVEL
template<>
struct logging_<CFLOG_DBG>
{
    static inline std::ostream& log(const char* file, const int line)
    {
        *log_internal_stream << "DEBUG " ;
#ifdef LOG_WITH_FILENAMES
        *log_internal_stream << file << ":" << line << ": ";
#endif
        return *log_internal_stream;
    }
};
#endif

#if CFLOG_INF>LOG_STRIP_UP_TO_LEVEL
template<>
struct logging_<CFLOG_INF>
{
    static inline std::ostream& log(const char* file, const int line)
    {
        *log_internal_stream << "INFO " ;
#ifdef LOG_WITH_FILENAMES
        *log_internal_stream << file << ":" << line << ": ";
#endif
        return *log_internal_stream;
    }
};
#endif

#if CFLOG_WARN > LOG_STRIP_UP_TO_LEVEL
template<>
struct logging_<CFLOG_WARN>
{
    static inline std::ostream& log(const char* file, const int line)
    {
        *log_internal_stream << "WARNING ";
#ifdef LOG_WITH_FILENAMES
        *log_internal_stream << file << ":" << line << ": ";
#endif
        return *log_internal_stream;
    }
};
#endif

#if CFLOG_ERR > LOG_STRIP_UP_TO_LEVEL
template<>
struct logging_<CFLOG_ERR>
{
    static inline std::ostream& log(const char* file, const int line)
    {
        *log_internal_stream << "ERROR " ;
#ifdef LOG_WITH_FILENAMES
        *log_internal_stream << file << ":" << line << ": ";
#endif
        return *log_internal_stream;
    }
};
#endif

class Logging
{
    public:
        template<unsigned int V>
        static inline std::ostream& log(const char* file, const int line)
        {
            return logging_<V>::log(file, line);
        }

            inline void operator&(std::ostream&) { }

        inline void setLogStream(std::ostream* s)
        {
            if (s != NULL)
            {
                log_internal_stream = s;
            }
        }

        static inline bool setLogFile(const char* filename)
        {
            static std::ofstream fileStream;
            if (fileStream.is_open())
            {
                fileStream.close();
            }

            fileStream.open(filename);

            if (!fileStream.fail())
            {
                log_internal_stream = &fileStream;
                return true;
            }

            return false;
        }

        static inline void flush()
        {
            log_internal_stream->flush();
        }
};



// INTERNAL MACROS
#define LOG_INTERNAL_NORMAL(level) \
        Logging::log<CFLOG_##level>(__FILE__, __LINE__)

#define LOG_INTERNAL_CONDITIONAL(level, condition) \
        !(condition) ? (void) 0 : Logging() & LOG_INTERNAL_NORMAL(level)

#define LOG_INTERNAL_DISCARD(level) \
        LOG_INTERNAL_CONDITIONAL(level, false)



// PUBLIC MACROS
#define LOG(level) \
        LOG_INTERNAL_CONDITIONAL(level, CFLOG_##level > LOG_STRIP_UP_TO_LEVEL)

#define LOG_IF(level, condition) \
        LOG_INTERNAL_CONDITIONAL(level, (CFLOG_##level > LOG_STRIP_UP_TO_LEVEL) && (condition))

#ifdef DEBUG
    #define DLOG(level) \
        LOG_INTERNAL_CONDITIONAL(level, CFLOG_##level > LOG_STRIP_UP_TO_LEVEL)

    #define DLOG_IF(level, condition) \
        LOG_INTERNAL_CONDITIONAL(level, (CFLOG_##level > LOG_STRIP_UP_TO_LEVEL) && (condition))
#else
    #define DLOG(level) \
        LOG_INTERNAL_DISCARD(level)

    #define DLOG_IF(level, condition) \
        LOG_INTERAL_DISCARD(level)
#endif


#endif

