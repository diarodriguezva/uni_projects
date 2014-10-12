/** BEGIN LICENSE ************************************************************/
//    Copyright 2011-2012 Cognition Factory
//    All rights reserved.
//
//    Any use, distribution or replication without a written permission
//    is prohibited.
//
//    The name "Cognition Factory" must not be used to endorse or promote
//    products derived from the source code without prior written permission.
//
//    You agree to indemnify, hold harmless and defend Cognition Factory from
//    and against any loss, damage, claims or lawsuits, including attorney's
//    fees that arise or result from your use the software.
//
//    THIS SOFTWARE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT ANY
//    TECHNICAL SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
//    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//    FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. ALSO, THERE IS NO
//    WARRANTY OF NON-INFRINGEMENT, TITLE OR QUIET ENJOYMENT. IN NO EVENT
//    SHALL COGNITION FACTORY OR ITS SUPPLIERS BE LIABLE FOR ANY DIRECT,
//    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//    POSSIBILITY OF SUCH DAMAGE.
/** END LICENSE **************************************************************/

#ifndef CF_COMM_MODULE_MACROS
#define CF_COMM_MODULE_MACROS

#include <cf/macros.hpp>
//#include <cf/comm/config.hpp>

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

// CF_COMM_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// CF_LOCAL is used for non-api symbols.

#ifdef CF_DLL // defined if CF is compiled as a DLL
  #ifdef cfcomm_EXPORTS // defined if we are building the CF DLL (instead of using it)
    #define CF_COMM_API CF_HELPER_DLL_EXPORT
  #else
    #define CF_COMM_API CF_HELPER_DLL_IMPORT
  #endif // CF_DLL_EXPORTS
  #define CF_LOCAL CF_HELPER_DLL_LOCAL
#else // CF_DLL is not defined: this means CF is a static lib.
  #define CF_COMM_API
  #define CF_LOCAL
#endif // CF_DLL

#endif // CF_COMM_MODULE_MACROS
