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

#include <cf/comm/MessageSubscriber.hpp>

namespace cf {
namespace comm {

template <class Message>
MessageSubscriber<Message>::MessageSubscriber(Context& context) :
    _subscriber(context),
    _timeout(0),
    _blocking(true)
{
}

template <class Message>
MessageSubscriber<Message>::~MessageSubscriber()
{
}

template <class Message>
void MessageSubscriber<Message>::connect(const ::std::string& endpoint)
{
    this->_subscriber.connect(endpoint);
}

template <class Message>
void MessageSubscriber<Message>::setFilter(const ::std::string& filter)
{
    this->_subscriber.setFilter(filter);
}

template <class Message>
void MessageSubscriber<Message>::setTimeout(const int& timeout)
{
    this->_timeout = timeout;
}

template <class Message>
int MessageSubscriber<Message>::timeout() const
{
    return this->_timeout;
}

template <class Message>
void MessageSubscriber<Message>::setBlocking(const bool& blocking)
{
    this->_blocking = blocking;
}

template <class Message>
bool MessageSubscriber<Message>::blocking() const
{
    return this->_blocking;
}

template <class Message>
void MessageSubscriber<Message>::run()
{
    while(!boost::this_thread::interruption_requested())
    {
        Message message;
        if (this->_subscriber.receive(message, this->_timeout, this->_blocking))
        {
            this->processIncommingMessage(message);
        }

        boost::this_thread::yield();
    }
}

}
}
