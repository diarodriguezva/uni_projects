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

#ifndef _MESSAGESERVER_HPP
#define _MESSAGESERVER_HPP

#include <cf/common/Thread.hpp>

#include <cf/comm/Context.hpp>
#include <cf/comm/Server.hpp>
#include <cf/comm/macros.hpp>

namespace cf {
namespace comm {

template <class RequestT, class ResponseT>
class CF_COMM_API MessageServer : public ::cf::common::Thread
{
public:
    MessageServer(Context& context);

    virtual ~MessageServer();

    void bind(const ::std::string& endpoint);

    void setTimeout(const int& timeout);

    int timeout() const;

    void setBlocking(const bool& blocking);

    bool blocking() const;

protected:

    virtual void run();

    virtual bool processIncommingMessage(const RequestT& request, ResponseT& response) = 0;

    Server<RequestT, ResponseT> _server;

    int _timeout;

    bool _blocking;

};

}
}

#include <cf/comm/impl/MessageServer.hpp>

#endif
