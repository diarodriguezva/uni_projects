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

#include <cf/r0/RobotClient.hpp>

namespace cf {
namespace r0 {

template <class RequestT, class ResponseT>
RobotClient<RequestT, ResponseT>::RobotClient() :
    _context(1),
    _client(_context),
    _connected(false),
    _sequence_number(0)
{
}

template <class RequestT, class ResponseT>
RobotClient<RequestT, ResponseT>::~RobotClient()
{
    if (this->_connected)
        this->disconnect();
}

template <class RequestT, class ResponseT>
void RobotClient<RequestT, ResponseT>::connect(const ::std::string& endpoint)
{
    this->_client.connect(endpoint);
    this->_connected = true;
}

template <class RequestT, class ResponseT>
void RobotClient<RequestT, ResponseT>::disconnect()
{
    this->_client.close();
    this->_connected = false;
}

template <class RequestT, class ResponseT>
bool RobotClient<RequestT, ResponseT>::getEffectorPose(const ::std::string& effector, ::cf::math::Pose& pose)
{
    RequestT request;
    ResponseT response;
    request.set_type(RequestT::GETPOSITION);
    request.set_sequence_number(++this->_sequence_number);
    request.mutable_position_task()->set_effector(effector);

    if (!this->_client.request(request, response))
        return false;

    if (response.position_task().status() == proto::GetPositionTaskResponse::EFFECTORNOTCONFIGURED)
    {
        std::cerr << "Effector " << effector << " is not configured!" << std::endl;
        return false;
    }

    pose.position.x() = response.position_task().pose().position().x();
    pose.position.y() = response.position_task().pose().position().y();
    pose.position.z() = response.position_task().pose().position().z();
    pose.rotation.w() = response.position_task().pose().rotation().w();
    pose.rotation.x() = response.position_task().pose().rotation().x();
    pose.rotation.y() = response.position_task().pose().rotation().y();
    pose.rotation.z() = response.position_task().pose().rotation().z();

    return true;
}

template <class RequestT, class ResponseT>
bool RobotClient<RequestT, ResponseT>::setEffectors(EffectorMap& effectors)
{
    RequestT request;
    ResponseT response;
    request.set_type(RequestT::SETCONFIGURATION);
    request.set_sequence_number(++this->_sequence_number);
    proto::SetConfigurationTaskRequest* task = request.mutable_set_config_task();

    for (EffectorMap::const_iterator it = effectors.begin(); it != effectors.end(); ++it)
    {
        proto::ToolConfiguration* config = task->add_tools();
        config->set_name(it->first);
        config->mutable_pose()->mutable_position()->set_x(it->second.position.x());
        config->mutable_pose()->mutable_position()->set_y(it->second.position.y());
        config->mutable_pose()->mutable_position()->set_z(it->second.position.z());
        config->mutable_pose()->mutable_rotation()->set_w(it->second.rotation.w());
        config->mutable_pose()->mutable_rotation()->set_x(it->second.rotation.x());
        config->mutable_pose()->mutable_rotation()->set_y(it->second.rotation.y());
        config->mutable_pose()->mutable_rotation()->set_z(it->second.rotation.z());
    }

    return this->_client.request(request, response);
}

template <class RequestT, class ResponseT>
bool RobotClient<RequestT, ResponseT>::moveToPose(const ::cf::math::Pose& pose, const ::std::string& effector, const Mode& mode, const float& speed, const float& acceleration)
{
    RequestT request;
    ResponseT response;
    request.set_type(RequestT::MOVE);
    request.set_sequence_number(++this->_sequence_number);
    proto::MoveTaskRequest* task = request.mutable_move_task();

    task->set_effector(effector);
    task->set_speed(speed);
    task->set_acceleration(acceleration);
    task->set_mode(mode);
    task->mutable_pose()->mutable_position()->set_x(pose.position.x());
    task->mutable_pose()->mutable_position()->set_y(pose.position.y());
    task->mutable_pose()->mutable_position()->set_z(pose.position.z());
    task->mutable_pose()->mutable_rotation()->set_w(pose.rotation.w());
    task->mutable_pose()->mutable_rotation()->set_x(pose.rotation.x());
    task->mutable_pose()->mutable_rotation()->set_y(pose.rotation.y());
    task->mutable_pose()->mutable_rotation()->set_z(pose.rotation.z());

    if (!this->_client.request(request, response))
        return false;

    switch (response.move_task().status())
    {
        case proto::MoveTaskResponse::EFFECTORNOTCONFIGURED:
            std::cerr << "Effector " << effector << " is not configured!" << std::endl;
            break;
        case proto::MoveTaskResponse::INVERSEPOSITIONFAILED:
            std::cerr << "Inverse position failed - position is not reachable" << std::endl;
            break;
        case proto::MoveTaskResponse::ERROR:
            std::cerr << "Error" << std::endl;
            break;
        case proto::MoveTaskResponse::GOALREACHED:
            return true;
    }
    return false;
}

template <class RequestT, class ResponseT>
bool RobotClient<RequestT, ResponseT>::moveJoints(const ::cf::math::Vector& q, const float& speed, const float& acceleration)
{
    RequestT request;
    ResponseT response;
    request.set_type(RequestT::SETJOINTS);
    request.set_sequence_number(++this->_sequence_number);
    proto::SetJointsTaskRequest* task = request.mutable_set_joints_task();

    task->set_speed(speed);
    task->set_acceleration(acceleration);

    for (::std::size_t i = 0; i < q.size(); ++i)
        task->mutable_configuration()->add_q(q(i));

    if (!this->_client.request(request, response))
        return false;

    return (response.set_joints_task().status() == proto::SetJointsTaskResponse::GOALREACHED);
}

}
}
