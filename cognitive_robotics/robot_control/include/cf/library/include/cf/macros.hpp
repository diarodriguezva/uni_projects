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

#ifndef CF_GENERAL_MACROS
#define CF_GENERAL_MACROS

//this makes logging available EVERYWHERE!
#include <cf/common/logging.hpp>

// define a pretty name for the foreach macro
#include <boost/foreach.hpp>

// ###### BEGIN FIX (see https://svn.boost.org/trac/boost/ticket/6131)
#include <boost/version.hpp>
namespace boost {
#if BOOST_VERSION != 104900
    namespace BOOST_FOREACH = foreach;
#endif
} // namespace boost
// ###### END FIX

#ifndef foreach
    #define foreach         BOOST_FOREACH
#endif
#ifndef reverse_foreach
    #define reverse_foreach BOOST_REVERSE_FOREACH
#endif

// special delete substitution that sets the pointer to 0
#ifndef CFDELETE
    #define CFDELETE(obj) { delete obj; obj = NULL; }
#endif
#ifndef CFDELETEARRAY
    #define CFDELETEARRAY(obj) { delete[] obj; obj = NULL; }
#endif

#endif
