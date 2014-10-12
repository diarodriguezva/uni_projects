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

#ifndef CF_MATH_UNITS_HPP_
#define CF_MATH_UNITS_HPP_

#include <cf/math/Real.hpp>
#include <cf/math/macros.hpp>

namespace cf {
namespace math {
namespace units {

/**
 * convert a radiant value to a degree value
 * @param rad radiant value
 * @return degree value
 **/
inline cf::math::Real toDeg(const cf::math::Real& rad)
{
    return (rad * 57.295779513082320876798154814105f /* = 180.0 / M_PI*/);
}


/**
 * convert a degree value to a radiant value
 * @param deg degree value
 * @return radiant value
 **/
inline cf::math::Real toRad(const cf::math::Real& deg)
{
    return (deg * 0.017453292519943295769236907684886f /* = M_PI / 180.0*/);
}

inline cf::math::Real pi()
{
    return M_PI;
}

}
}
}

#endif /*CF_MATH_UNITS_HPP_"*/

