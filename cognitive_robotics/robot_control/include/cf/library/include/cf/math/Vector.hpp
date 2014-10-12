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

#ifndef _CF_MATH_VECTOR_HPP_
#define _CF_MATH_VECTOR_HPP_

#include <cf/math/macros.hpp>
#include <cf/math/Real.hpp>
#include <cf/math/Vector.hpp>
#include <boost/algorithm/string.hpp>

#include <Eigen/Core>
#include <Eigen/StdDeque>

namespace cf {
namespace math {

//////dynamic
typedef ::Eigen::Matrix<Real, ::Eigen::Dynamic, 1> Vector;

typedef ::Eigen::Matrix<int, ::Eigen::Dynamic, 1> VectorI;

typedef std::deque<Vector, Eigen::aligned_allocator<Vector> > Vectors;

///////// statics
typedef ::Eigen::Matrix< Real, 2, 1 > Vector2;

typedef ::Eigen::Matrix< Real, 3, 1 > Vector3;

typedef ::Eigen::Matrix< Real, 4, 1 > Vector4;

typedef ::Eigen::Matrix< Real, 6, 1 > Vector6;

//blocks
typedef ::Eigen::VectorBlock< Vector, ::Eigen::Dynamic > VectorBlock;

typedef ::Eigen::VectorBlock< const Vector, ::Eigen::Dynamic > VectorBlockConst;

namespace vector
{
    /**
        * converts a Vector into a string
        * @param in vector
        * @return string
        */
    static inline std::string convert(const cf::math::Vector& in)
    {
        std::stringstream ss;
        ss << "[";
        for (int r = 0; r < in.rows(); ++r)
        {
            ss << in(r) << ",";
        }
        ss << "]";
        std::string s(ss.str());
        boost::algorithm::erase_last(s, ",");
        return s;
    }

    /**
        * converts a string back into a cf::math::Vector
        * @param in string
        * @return vector
        */
    static inline cf::math::Vector convert(std::string in)
    {
        std::vector<std::string> tmp;
        boost::algorithm::erase_first(in, "[");
        boost::algorithm::erase_first(in, "]");
        boost::algorithm::split(tmp, in, boost::algorithm::is_any_of(","), boost::algorithm::token_compress_on);

        cf::math::Vector out(tmp.size());
        std::stringstream ss;
        for (size_t o = 0; o < tmp.size(); ++o)
        {
            ss.clear();
            ss.str(tmp[o]);
            ss >> out(o);
        }
        return out;
    }
}
}
}

#endif /* _CF_MATH_VECTOR_HPP_ */
