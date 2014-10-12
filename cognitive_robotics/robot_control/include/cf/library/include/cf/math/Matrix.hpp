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

#ifndef _CF_MATH_MATRIX_HPP_
#define _CF_MATH_MATRIX_HPP_

#include <cf/math/macros.hpp>
#include <deque>

#include <Eigen/Core>
#include <Eigen/Dense>

namespace cf {
    namespace math {
        /////////////// dynamic matrices
        typedef ::Eigen::Matrix< Real, ::Eigen::Dynamic, ::Eigen::Dynamic > Matrix;

        typedef ::Eigen::Matrix<int, ::Eigen::Dynamic, ::Eigen::Dynamic> MatrixI;

        typedef ::Eigen::Matrix<unsigned char, ::Eigen::Dynamic, ::Eigen::Dynamic,
                ::Eigen::RowMajor> MatrixUC;

        typedef std::deque<Matrix, Eigen::aligned_allocator<Matrix> > Matrices;

        /////////////// statics
        typedef ::Eigen::Matrix< Real, 2, 2 > Matrix22;

        typedef ::Eigen::Matrix< Real, 3, 3 > Matrix33;

        typedef ::Eigen::Matrix< Real, 4, 4 > Matrix44;

        typedef std::deque<Matrix44, Eigen::aligned_allocator<Matrix44> > Matrices44;

        typedef ::Eigen::Matrix< Real, 6, 6 > Matrix66;

        //blocks
        typedef ::Eigen::Block< Matrix > MatrixBlock;

        typedef const ::Eigen::Block< const Matrix > MatrixBlockConst;

        typedef Matrix::ColXpr MatrixColumn;

        typedef Matrix::ConstColXpr MatrixColumnConst;

        typedef Matrix::RowXpr MatrixRow;

        typedef Matrix::ConstRowXpr MatrixRowConst;

        typedef ::Eigen::Block< MatrixUC > MatrixUCBlock;

    }
}

#endif /* _CF_MATH_MATRIX_HPP_ */

