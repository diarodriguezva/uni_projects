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

#ifndef _ROBOTCLIENT_HPP
#define _ROBOTCLIENT_HPP

#include <map>

#include <cf/comm/Client.hpp>
#include <cf/comm/Context.hpp>
#include <cf/math/Pose.hpp>
#include <cf/math/Vector.hpp>

#include <cf/r0/proto/MoveTask.pb.h>
#include <cf/r0/proto/GetPositionTask.pb.h>
#include <cf/r0/proto/GetConfigurationTask.pb.h>
#include <cf/r0/proto/SetConfigurationTask.pb.h>
#include <cf/r0/proto/SetJointsTask.pb.h>

namespace cf {
namespace r0 {

typedef ::cf::r0::proto::MoveTaskRequest_Mode Mode;
typedef ::std::map< ::std::string, ::cf::math::Pose> EffectorMap;

template <class RequestT, class ResponseT>
class RobotClient
{
public:

    RobotClient();

    virtual ~RobotClient();

    void connect(const ::std::string& endpoint);

    void disconnect();

    bool getEffectorPose(const ::std::string& effector, ::cf::math::Pose& pose);

    bool setEffectors(EffectorMap& effectors);

    bool moveToPose(const ::cf::math::Pose& pose, const ::std::string& effector,
                    const Mode& mode = proto::MoveTaskRequest::CONFIGURATIONSPACE, const float& speed = 1.0f, const float& acceleration = 1.0f);

    bool moveJoints(const ::cf::math::Vector& q, const float& speed = 1.0f, const float& acceleration = 1.0f);

protected:

    ::cf::comm::Context _context;

    ::cf::comm::Client< RequestT, ResponseT > _client;

    bool _connected;

    int _sequence_number;

};

}
}

#include <cf/r0/impl/RobotClient.hpp>

#endif /* end of include guard */

