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

#ifndef _CF_MATH_SQUAREMATRIX_HPP_
#define _CF_MATH_SQUAREMATRIX_HPP_

#include <cf/math/macros.hpp>
#include <cf/math/Matrix.hpp>
#include <cf/logging.hpp>

#include <Eigen/Core>
#include <Eigen/StdDeque>

namespace cf {
namespace math {

//////dynamic
class SquareMatrix: public Matrix
{
    public:
        SquareMatrix(std::size_t dim = 1) :
            Matrix(dim, dim)
        {
        }

        virtual void resize(const int& dim)
        {
            Matrix::resize(dim, dim);
        }

        void resize(const int& dim1, const int& dim2)
        {
            LOG_IF(WARN, dim1 != dim2)
                    << "You try to resize a square matrix to a non square one... Taking largest value instead"
                    << std::endl;
            this->resize(std::max(dim1, dim2));
        }

        bool invert(SquareMatrix& result)
        {
            if(this->determinant() == 0)
            {
                return false;
            }
            else
            {
                result.base() = this->inverse();
                return true;
            }
        }

        // You need to define this for your object to work
        typedef Matrix Base;
        template<typename OtherDerived>
        SquareMatrix& operator=(
                const Eigen::MatrixBase<OtherDerived>& other)
        {
            this->Base::operator=(other);
            return *this;
        }
};

template<std::size_t n>
class SquareMatrixT: public SquareMatrix
{
public:
    SquareMatrixT<n> () :
        SquareMatrix(n)
    {
    }

    SquareMatrixT<n> (const SquareMatrixT<n>& t) :
        SquareMatrix(t)
    {
    }

    SquareMatrixT<n> (const SquareMatrix& t) :
        SquareMatrix(t)
    {
        assert(t.rows() == n);
    }

    void resize(const int& dim)
    {
        assert(0 && "Error: resizing fixed size Matrix");
    }

};

typedef SquareMatrixT<2> SquareMatrix2;
typedef SquareMatrixT<3> SquareMatrix3;


typedef std::deque<SquareMatrix, Eigen::aligned_allocator<SquareMatrix> >
        SquareMatrices;

}
}

#endif /* _CF_MATH_SQUAREMATRIX_HPP_ */

