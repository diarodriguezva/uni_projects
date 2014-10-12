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

#ifndef _EXCEPTION_HPP
#define _EXCEPTION_HPP

#include <string>
#include <exception>
#include <stdexcept>
#include <cf/common/macros.hpp>

namespace cf {
namespace common {

class CF_COMMON_API Exception: public ::std::exception
{
public:

    Exception(const ::std::string& msg = "unspecified error") throw() :
        _msg(msg)
    {
    }

    ~Exception() throw()
    {
    }

    virtual const char* what() const throw()
    {
        return this->_msg.c_str();
    }

    virtual const ::std::string& whatString() const throw()
    {
        return this->_msg;
    }

protected:
    ::std::string _msg;
};

}
}

#endif
