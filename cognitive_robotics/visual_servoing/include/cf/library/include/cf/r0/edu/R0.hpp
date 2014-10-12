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

#ifndef _R0_HPP
#define _R0_HPP

#include <string>
#include <map>

namespace cf {

    namespace r0 {

        namespace edu {

            class RobotClient;

            struct Point
            {
                double x;
                double y;
                double z;

                Point() :
                    x(0.0f), y(0.0f), z(0.0f)
                {}

                Point(const double& x_, const double& y_, const double& z_) :
                    x(x_), y(y_), z(z_)
                {}
            };

            enum Mode
            {
                ConfigurationSpace,
                OperationalSpace
            };

            typedef ::std::map< ::std::string, Point> EffectorMap;

            class R0
            {
            public:
                R0();

                virtual ~R0();

                void connect(const ::std::string& host, const ::std::size_t& port);

                void disconnect();

                bool getEffectorPosition(const ::std::string& effector, Point& point);

                bool setEffectors(const EffectorMap& effectors);

                bool moveToPosition(const Point& p, const ::std::string& effector, const Mode& mode = ConfigurationSpace,
                                    const float& speed = 1.0f, const float& acceleration = 1.0f);

                bool moveJoints(const double& q0, const double& q1, const double& q2, const float& speed = 1.0f, const float& acceleration = 1.0f);

            private:

                ::cf::r0::edu::RobotClient* _client;
            };

        }
    }
}

#endif /* end of include guard */

