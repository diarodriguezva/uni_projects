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

#ifndef CF_COMMON_MODULE_MACROS
#define CF_COMMON_MODULE_MACROS

#include <cf/macros.hpp>
//#include <cf/common/config.hpp>

#if defined _WIN32 || defined __CYGWIN__
  #define CF_HELPER_DLL_IMPORT __declspec(dllimport)
  #define CF_HELPER_DLL_EXPORT __declspec(dllexport)
  #define CF_HELPER_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define CF_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
    #define CF_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
    #define CF_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define CF_HELPER_DLL_IMPORT
    #define CF_HELPER_DLL_EXPORT
    #define CF_HELPER_DLL_LOCAL
  #endif
#endif

// CF_COMMON_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// CF_LOCAL is used for non-api symbols.

#ifdef CF_DLL // defined if CF is compiled as a DLL
  #ifdef cfcommon_EXPORTS // defined if we are building the CF DLL (instead of using it)
    #define CF_COMMON_API CF_HELPER_DLL_EXPORT
  #else
    #define CF_COMMON_API CF_HELPER_DLL_IMPORT
  #endif // CF_DLL_EXPORTS
  #define CF_LOCAL CF_HELPER_DLL_LOCAL
#else // CF_DLL is not defined: this means CF is a static lib.
  #define CF_COMMON_API
  #define CF_LOCAL
#endif // CF_DLL

#endif // CF_COMMON_MODULE_MACROS
