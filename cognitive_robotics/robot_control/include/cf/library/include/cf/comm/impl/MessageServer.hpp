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

#include <cf/comm/MessageServer.hpp>

namespace cf {
namespace comm {

template <class RequestT, class ResponseT>
MessageServer<RequestT, ResponseT>::MessageServer(Context& context) :
    _server(context),
    _timeout(0),
    _blocking(true)
{
}

template <class RequestT, class ResponseT>
MessageServer<RequestT, ResponseT>::~MessageServer()
{
}

template <class RequestT, class ResponseT>
void MessageServer<RequestT, ResponseT>::bind(const ::std::string& endpoint)
{
    this->_server.bind(endpoint);
}

template <class RequestT, class ResponseT>
void MessageServer<RequestT, ResponseT>::setTimeout(const int& timeout)
{
    this->_timeout = timeout;
}

template <class RequestT, class ResponseT>
int MessageServer<RequestT, ResponseT>::timeout() const
{
    return this->_timeout;
}

template <class RequestT, class ResponseT>
void MessageServer<RequestT, ResponseT>::setBlocking(const bool& blocking)
{
    this->_blocking = blocking;
}

template <class RequestT, class ResponseT>
bool MessageServer<RequestT, ResponseT>::blocking() const
{
    return this->_blocking;
}

template <class RequestT, class ResponseT>
void MessageServer<RequestT, ResponseT>::run()
{
    while(!boost::this_thread::interruption_requested())
    {
        RequestT req;
        if (this->_server.receive(req, this->_timeout, this->_blocking))
        {
            ResponseT resp;
            if (this->processIncommingMessage(req, resp))
            {
                this->_server.send(resp);
            }
        }
        boost::this_thread::yield();
    }
}

}
}
