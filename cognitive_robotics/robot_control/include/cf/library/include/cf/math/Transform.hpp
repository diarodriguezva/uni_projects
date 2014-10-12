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

#ifndef _CF_MATH_TRANSFORM_HPP_
#define _CF_MATH_TRANSFORM_HPP_

#include <cmath>
#include <limits>
#include <deque>

#include <cf/math/macros.hpp>
#include <cf/math/Real.hpp>

#include <Eigen/Geometry>
#include <Eigen/StdDeque>


namespace cf
{
    namespace math
    {
        typedef ::Eigen::Transform<Real, 3, ::Eigen::Affine> Transform;

        typedef ::Eigen::Transform<int, 3, ::Eigen::Affine> Transformi;

        typedef std::deque<Transform, Eigen::aligned_allocator<Transform> > Transforms;

        // methods for transforming
        namespace transform
        {
            template<typename Matrix1, typename Real, typename Matrix2>
            inline
            void fromDelta(const Matrix1& t1, const Real& x, const Real& y,
                    const Real& z, const Real& a, const Real& b, const Real& c,
                    Matrix2& t2)
            {
                t2(0, 0) = t1(0, 0) - c * t1(1, 0) + b * t1(2, 0);
                t2(0, 1) = t1(0, 1) - c * t1(1, 1) + b * t1(2, 1);
                t2(0, 2) = t1(0, 2) - c * t1(1, 2) + b * t1(2, 2);
                t2(0, 3) = t1(0, 3) + x;
                t2(1, 0) = t1(1, 0) + c * t1(0, 0) - a * t1(2, 0);
                t2(1, 1) = t1(1, 1) + c * t1(0, 1) - a * t1(2, 1);
                t2(1, 2) = t1(1, 2) + c * t1(0, 2) - a * t1(2, 2);
                t2(1, 3) = t1(1, 3) + y;
                t2(2, 0) = t1(2, 0) - b * t1(0, 0) + a * t1(1, 0);
                t2(2, 1) = t1(2, 1) - b * t1(0, 1) + a * t1(1, 1);
                t2(2, 2) = t1(2, 2) - b * t1(0, 2) + a * t1(1, 2);
                t2(2, 3) = t1(2, 3) + z;
                t2(3, 0) = 0.0f;
                t2(3, 1) = 0.0f;
                t2(3, 2) = 0.0f;
                t2(3, 3) = 1.0f;
            }

            template<typename Matrix1, typename Vector, typename Matrix2>
            inline
            void fromDelta(const Matrix1& t1, const Vector& xyzabc, Matrix2& t2)
            {
                assert(xyzabc.size() > 5);

                fromDelta(t1, xyzabc(0), xyzabc(1), xyzabc(2), xyzabc(3),
                        xyzabc(4), xyzabc(5), t2);
            }

            template<typename Matrix, typename Real>
            inline
            void getDelta(const Matrix& t, Real& x, Real& y, Real& z, Real& a,
                    Real& b, Real& c)
            {
                x = t(0, 3);
                y = t(1, 3);
                z = t(2, 3);
                a = (t(2, 1) - t(1, 2)) / 2.0f;
                b = (t(0, 2) - t(2, 0)) / 2.0f;
                c = (t(1, 0) - t(0, 1)) / 2.0f;
            }

            template<typename Matrix, typename Vector>
            inline
            void getDelta(const Matrix& t, Vector& xyzabc)
            {
                assert(xyzabc.size() > 5);

                getDelta(t, xyzabc(0), xyzabc(1), xyzabc(2), xyzabc(3), xyzabc(
                        4), xyzabc(5));
            }

            template<typename Matrix, typename Real>
            inline
            void getDenavitHartenberg(const Matrix& t, Real& d, Real& theta,
                    Real& a, Real& alpha)
            {
                assert(::std::abs(t(2, 0)) <= ::std::numeric_limits<Real>::epsilon());

                d = t(2, 3);

                theta = ::std::atan2(t(1, 0), t(0, 0));

                if (::std::abs(t(0, 0))
                        <= ::std::numeric_limits<Real>::epsilon())
                {
                    a = t(1, 3) / t(1, 0);
                }
                else
                {
                    a = t(0, 3) / t(0, 0);
                }

                alpha = ::std::atan2(t(2, 1), t(2, 2));
            }

            template<typename Matrix, typename Real>
            inline
            void getScale(const Matrix& t, Real& x, Real& y, Real& z)
            {
                x = t(0, 0);
                y = t(1, 1);
                z = t(2, 2);
            }

            template<typename Matrix, typename Vector>
            inline
            void getScale(const Matrix& t, Vector& xyz)
            {
                assert(xyz.size() > 2);

                getScale(t, xyz(0), xyz(1), xyz(2));
            }

            template<typename Matrix, typename Real>
            inline
            void getTranslation(const Matrix& t, Real& x, Real& y, Real& z)
            {
                x = t(0, 3);
                y = t(1, 3);
                z = t(2, 3);
            }

            template<typename Matrix, typename Vector>
            inline
            void getTranslation(const Matrix& t, Vector& xyz)
            {
                assert(xyz.size() > 2);

                getTranslation(t, xyz(0), xyz(1), xyz(2));
            }

            template<typename Real, typename Matrix>
            inline
            void setDelta(const Real& x, const Real& y, const Real& z,
                    const Real& a, const Real& b, const Real& c, Matrix& t)
            {
                t(0, 0) = 0;
                t(0, 1) = -c;
                t(0, 2) = b;
                t(0, 3) = x;
                t(1, 0) = c;
                t(1, 1) = 0;
                t(1, 2) = -a;
                t(1, 3) = y;
                t(2, 0) = -b;
                t(2, 1) = a;
                t(2, 2) = 0;
                t(2, 3) = z;
                t(3, 0) = 0;
                t(3, 1) = 0;
                t(3, 2) = 0;
                t(3, 3) = 1;
            }

            template<typename Vector, typename Matrix>
            inline
            void setDelta(const Vector& xyzabc, Matrix& t)
            {
                assert(xyzabc.size() > 5);

                setDelta(xyzabc(0), xyzabc(1), xyzabc(2), xyzabc(3), xyzabc(4),
                        xyzabc(5), t);
            }

            template<typename Real, typename Matrix>
            inline
            void setDenavitHartenberg(const Real& d, const Real& theta,
                    const Real& a, const Real& alpha, Matrix& t)
            {
                Real cosAlpha = ::std::cos(alpha);
                Real cosTheta = ::std::cos(theta);
                Real sinAlpha = ::std::sin(alpha);
                Real sinTheta = ::std::sin(theta);

                t(0, 0) = cosTheta;
                t(1, 0) = sinTheta;
                t(2, 0) = 0.0f;
                t(3, 0) = 0.0f;
                t(0, 1) = -cosAlpha * sinTheta;
                t(1, 1) = cosAlpha * cosTheta;
                t(2, 1) = sinAlpha;
                t(3, 1) = 0.0f;
                t(0, 2) = sinAlpha * sinTheta;
                t(1, 2) = -sinAlpha * cosTheta;
                t(2, 2) = cosAlpha;
                t(3, 2) = 0.0f;
                t(0, 3) = a * cosTheta;
                t(1, 3) = a * sinTheta;
                t(2, 3) = d;
                t(3, 3) = 1.0f;
            }

            template<typename Real, typename Matrix>
            inline
            void setScale(const Real& x, const Real& y, const Real& z,
                    Matrix& t)
            {
                t(0, 0) = x;
                t(1, 1) = y;
                t(2, 2) = z;
            }

            template<typename Vector, typename Matrix>
            inline
            void setScale(const Vector& xyz, Matrix& t)
            {
                assert(xyz.size() > 2);

                setScale(xyz(0), xyz(1), xyz(2), t);
            }

            template<typename Real, typename Matrix>
            inline
            void setTranslation(const Real& x, const Real& y, const Real& z,
                    Matrix& t)
            {
                t(0, 3) = x;
                t(1, 3) = y;
                t(2, 3) = z;
            }

            template<typename Vector, typename Matrix>
            inline
            void setTranslation(const Vector& xyz, Matrix& t)
            {
                assert(xyz.size() > 2);

                setTranslation(xyz(0), xyz(1), xyz(2), t);
            }

            template<typename Matrix1, typename Matrix2, typename Real>
            inline
            void toDelta(const Matrix1& t1, const Matrix2& t2, Real& x,
                    Real& y, Real& z, Real& a, Real& b, Real& c)
            {
                x = t2(0, 3) - t1(0, 3);
                y = t2(1, 3) - t1(1, 3);
                z = t2(2, 3) - t1(2, 3);
                a = (t1(1, 0) * t2(2, 0) - t1(2, 0) * t2(1, 0) + t1(1, 1) * t2(
                        2, 1) - t1(2, 1) * t2(1, 1) + t1(1, 2) * t2(2, 2) - t1(
                        2, 2) * t2(1, 2)) / 2.0f;
                b = (t1(2, 0) * t2(0, 0) - t1(0, 0) * t2(2, 0) + t1(2, 1) * t2(
                        0, 1) - t1(0, 1) * t2(2, 1) + t1(2, 2) * t2(0, 2) - t1(
                        0, 2) * t2(2, 2)) / 2.0f;
                c = (t1(0, 0) * t2(1, 0) - t1(1, 0) * t2(0, 0) + t1(0, 1) * t2(
                        1, 1) - t1(1, 1) * t2(0, 1) + t1(0, 2) * t2(1, 2) - t1(
                        1, 2) * t2(0, 2)) / 2.0f;
            }

            template<typename Matrix1, typename Matrix2, typename Vector>
            inline
            void toDelta(const Matrix1& t1, const Matrix2& t2, Vector& xyzabc)
            {
                assert(xyzabc.size() > 5);

                toDelta(t1, t2, xyzabc(0), xyzabc(1), xyzabc(2), xyzabc(3),
                        xyzabc(4), xyzabc(5));
            }
        }

        namespace rotation
        {
            ///for rotation
            template<typename Real, typename Matrix>
            inline
            void fromAxisAngle(const Real& x, const Real& y, const Real& z,
                    const Real& angle, Matrix& r)
            {
                Real norm = ::std::sqrt(::std::pow(x, 2) + ::std::pow(y, 2)
                        + ::std::pow(z, 2));

                Real u;
                Real v;
                Real w;

                if (::std::abs(norm) > ::std::numeric_limits<Real>::epsilon())
                {
                    u = x / norm;
                    v = y / norm;
                    w = z / norm;
                }
                else
                {
                    u = x;
                    v = y;
                    w = z;
                }

                Real uv = u * v;
                Real uw = u * w;
                Real vw = v * w;

                Real cosAngle = ::std::cos(angle);
                Real sinAngle = ::std::sin(angle);
                Real versineAngle = (1.0f - cosAngle);

                r(0, 0) = cosAngle + u * u * versineAngle;
                r(1, 0) = w * sinAngle + uv * versineAngle;
                r(2, 0) = -v * sinAngle + uw * versineAngle;
                r(0, 1) = -w * sinAngle + uv * versineAngle;
                r(1, 1) = cosAngle + v * v * versineAngle;
                r(2, 1) = u * sinAngle + vw * versineAngle;
                r(0, 2) = v * sinAngle + uw * versineAngle;
                r(1, 2) = -u * sinAngle + vw * versineAngle;
                r(2, 2) = cosAngle + w * w * versineAngle;
            }

            template<typename Vector, typename Real, typename Matrix>
            inline
            void fromAxisAngle(const Vector& axis, const Real& angle, Matrix& r)
            {
                fromAxisAngle(axis(0), axis(1), axis(2), angle, r);
            }

            template<typename Real, typename Matrix>
            inline
            void fromEulerXyz(const Real& x, const Real& y1, const Real& z2,
                    Matrix& r)
            {
                Real cosPhi = ::std::cos(x);
                Real cosTheta = ::std::cos(y1);
                Real cosPsi = ::std::cos(z2);
                Real sinPhi = ::std::sin(x);
                Real sinTheta = ::std::sin(y1);
                Real sinPsi = ::std::sin(z2);

                Real cosPsiSinTheta = cosPsi * sinTheta;
                Real sinPsiSinTheta = sinPsi * sinTheta;

                r(0, 0) = cosPsi * cosTheta;
                r(1, 0) = cosPsiSinTheta * sinPhi + sinPsi * cosPhi;
                r(2, 0) = -cosPsiSinTheta * cosPhi + sinPsi * sinPhi;
                r(0, 1) = -sinPsi * cosTheta;
                r(1, 1) = -sinPsiSinTheta * sinPhi + cosPsi * cosPhi;
                r(2, 1) = sinPsiSinTheta * cosPhi + cosPsi * sinPhi;
                r(0, 2) = sinTheta;
                r(1, 2) = -cosTheta * sinPhi;
                r(2, 2) = cosTheta * cosPhi;
            }

            template<typename Vector, typename Matrix>
            inline
            void fromEulerXyz(const Vector& xy1z2, Matrix& r)
            {
                fromEulerXyz(xy1z2(0), xy1z2(1), xy1z2(2), r);
            }

            template<typename Real, typename Matrix>
            inline
            void fromEulerZxz(const Real& z, const Real& x1, const Real& z2,
                    Matrix& r)
            {
                Real cosPhi = ::std::cos(z);
                Real cosTheta = ::std::cos(x1);
                Real cosPsi = ::std::cos(z2);
                Real sinPhi = ::std::sin(z);
                Real sinTheta = ::std::sin(x1);
                Real sinPsi = ::std::sin(z2);

                Real cosThetaCosPhi = cosTheta * cosPhi;
                Real cosThetaSinPhi = cosTheta * sinPhi;

                r(0, 0) = cosPsi * cosPhi - cosThetaSinPhi * sinPsi;
                r(1, 0) = cosPsi * sinPhi + cosThetaCosPhi * sinPsi;
                r(2, 0) = sinTheta * sinPsi;
                r(0, 1) = -sinPsi * cosPhi - cosThetaSinPhi * cosPsi;
                r(1, 1) = -sinPsi * sinPhi + cosThetaCosPhi * cosPsi;
                r(2, 1) = sinTheta * cosPsi;
                r(0, 2) = sinPhi * sinTheta;
                r(1, 2) = -cosPhi * sinTheta;
                r(2, 2) = cosTheta;
            }

            template<typename Vector, typename Matrix>
            inline
            void fromEulerZxz(const Vector& zx1z2, Matrix& r)
            {
                fromEulerZxz(zx1z2(0), zx1z2(1), zx1z2(2), r);
            }

            template<typename Real, typename Matrix>
            inline
            void fromRodrigues(const Real& x, const Real& y, const Real& z,
                    Matrix& r)
            {
                Real theta = ::std::sqrt(x * x + y * y + z * z);

                if (theta <= ::std::numeric_limits<Real>::epsilon())
                {
                    r.setIdentity();
                }
                else
                {
                    Real c = ::std::cos(theta);
                    Real s = ::std::sin(theta);

                    Real theta2 = theta ? 1.0f / theta : 0.0f;

                    Real x2 = x * theta2;
                    Real y2 = y * theta2;
                    Real z2 = z * theta2;

                    r(0, 0) = c + (1.0f - c) * x2 * x2;
                    r(0, 1) = (1.0f - c) * x2 * y2 - s * z2;
                    r(0, 2) = (1.0f - c) * x2 * z2 + s * y2;
                    r(1, 0) = (1.0f - c) * x2 * y2 + s * z2;
                    r(1, 1) = c + (1.0f - c) * y2 * y2;
                    r(1, 2) = (1.0f - c) * y2 * z2 - s * x2;
                    r(2, 0) = (1.0f - c) * x2 * z2 - s * y2;
                    r(2, 1) = (1.0f - c) * y2 * z2 + s * x2;
                    r(2, 2) = c + (1.0f - c) * z2 * z2;
                }
            }

            template<typename Vector, typename Matrix>
            inline
            void fromRodrigues(const Vector& xyz, Matrix& r)
            {
                fromRodrigues(xyz(0), xyz(1), xyz(2), r);
            }

            template<typename Real, typename Matrix>
            inline
            void fromSkewSymmetric(const Real& a, const Real& b, const Real& c,
                    Matrix& r)
            {
                r(0, 0) = 0;
                r(0, 1) = -c;
                r(0, 2) = b;
                r(1, 0) = c;
                r(1, 1) = 0;
                r(1, 2) = -a;
                r(2, 0) = -b;
                r(2, 1) = a;
                r(2, 2) = 0;
            }

            template<typename Vector, typename Matrix>
            inline
            void fromSkewSymmetric(const Vector& abc, Matrix& r)
            {
                assert(abc.size() > 2);
                assert(r.rows() > 2);
                assert(r.cols() > 2);

                fromSkewSymmetric(abc(0), abc(1), abc(2), r);
            }

            template<typename Real, typename Matrix>
            inline
            void fromXyz(const Real& x, const Real& y, const Real& z, Matrix& r)
            {
                Real cosPhi = ::std::cos(x);
                Real cosTheta = ::std::cos(y);
                Real cosPsi = ::std::cos(z);
                Real sinPhi = ::std::sin(x);
                Real sinTheta = ::std::sin(y);
                Real sinPsi = ::std::sin(z);

                Real cosPsiSinTheta = cosPsi * sinTheta;
                Real sinPsiSinTheta = sinPsi * sinTheta;

                r(0, 0) = cosPsi * cosTheta;
                r(1, 0) = sinPsi * cosTheta;
                r(2, 0) = -sinTheta;
                r(0, 1) = -sinPsi * cosPhi + cosPsiSinTheta * sinPhi;
                r(1, 1) = cosPsi * cosPhi + sinPsiSinTheta * sinPhi;
                r(2, 1) = cosTheta * sinPhi;
                r(0, 2) = sinPsi * sinPhi + cosPsiSinTheta * cosPhi;
                r(1, 2) = -cosPsi * sinPhi + sinPsiSinTheta * cosPhi;
                r(2, 2) = cosTheta * cosPhi;
            }

            template<typename Vector, typename Matrix>
            inline
            void fromXyz(const Vector& xyz, Matrix& r)
            {
                fromXyz(xyz(0), xyz(1), xyz(2), r);
            }

            template<typename Matrix, typename Real>
            inline
            void toEulerXyz(const Matrix& r, Real& x, Real& y1, Real& z2)
            {
                if (r(0, 2) > (1.0f - ::std::numeric_limits<Real>::epsilon()))
                { // gimbal lock: sin(M_PI_2) = 1
                    x = ::std::atan2(r(1, 0), r(1, 1));
                    y1 = static_cast<Real> (M_PI_2);
                    z2 = 0.0f;
                }
                else if (r(0, 2) < (-1.0f
                        + ::std::numeric_limits<Real>::epsilon()))
                { // gimbal lock: sin(-M_PI_2) = -1
                    x = -::std::atan2(r(1, 0), r(1, 1));
                    y1 = static_cast<Real> (-M_PI_2);
                    z2 = 0.0f;
                }
                else
                {
                    x = ::std::atan2(-r(1, 2), r(2, 2));
                    y1 = ::std::atan2(r(0, 2), ::std::sqrt(::std::pow(r(1, 2),
                            2) + ::std::pow(r(2, 2), 2)));
                    z2 = ::std::atan2(-r(0, 1), r(0, 0));
                }
            }

            template<typename Matrix, typename Vector>
            inline
            void toEulerXyz(const Matrix& r, Vector& xy1z2)
            {
                toEulerXyz(r, xy1z2(0), xy1z2(1), xy1z2(2));
            }

            template<typename Matrix, typename Real>
            inline
            void toEulerZxz(const Matrix& r, Real& z, Real& x1, Real& z2)
            {
                if (r(2, 2) > (1.0f - ::std::numeric_limits<Real>::epsilon()))
                { // gimbal lock: cos(0) = 1
                    z = ::std::atan2(-r(0, 1), r(0, 0));
                    x1 = 0.0f;
                    z2 = 0.0f;
                }
                else if (r(2, 2) < (-1.0f
                        + ::std::numeric_limits<Real>::epsilon()))
                { // gimbal lock: cos(M_PI) = -1
                    z = -::std::atan2(-r(0, 1), r(0, 0));
                    x1 = static_cast<Real> (M_PI);
                    z2 = 0.0f;
                }
                else
                {
                    z = ::std::atan2(r(0, 2), -r(1, 2));
                    x1 = ::std::atan2(::std::sqrt(::std::pow(r(2, 0), 2)
                            + ::std::pow(r(2, 1), 2)), r(2, 2));
                    z2 = ::std::atan2(r(2, 0), r(2, 1));
                }
            }

            template<typename Matrix, typename Vector>
            inline
            void toEulerZxz(const Matrix& r, Vector& zx1z2)
            {
                toEulerZxz(r, zx1z2(0), zx1z2(1), zx1z2(2));
            }

            template<typename Matrix, typename Real>
            inline
            void toRodrigues(const Matrix& r, Real& x, Real& y, Real& z)
            {
                x = r(2, 1) - r(1, 2);
                y = r(0, 2) - r(2, 0);
                z = r(1, 0) - r(0, 1);

                Real s = ::std::sqrt((x * x + y * y + z * z) * 0.25f);
                Real c = (r(0, 0) + r(1, 1) + r(2, 2) - 1.0f) * 0.5f;
                c = c > 1.0f ? 1.0f : c < -1.0f ? -1.0f : c;
                Real theta = ::std::acos(c);

                if (s < 1e-5)
                {
                    Real t;

                    if (c > 0.0f)
                    {
                        x = 0.0f;
                        y = 0.0f;
                        z = 0.0f;
                    }
                    else
                    {
                        t = (r(0, 0) + 1.0f) * 0.5f;
                        x = theta * ::std::sqrt(::std::max(t,
                                static_cast<Real> (0.0f)));
                        t = (r(1, 1) + 1.0f) * 0.5f;
                        y = theta * ::std::sqrt(::std::max(t,
                                static_cast<Real> (0.0f)))
                                * (r(0, 1) < 0.0f ? -1.0f : 1.0f);
                        t = (r(2, 2) + 1.0f) * 0.5f;
                        z = theta * ::std::sqrt(::std::max(t,
                                static_cast<Real> (0.0f)))
                                * (r(0, 2) < 0.0f ? -1.0f : 1.0f);
                    }
                }
                else
                {
                    Real vth = (1.0f / (2.0f * s)) * theta;
                    x *= vth;
                    y *= vth;
                    z *= vth;
                }
            }

            template<typename Matrix, typename Vector>
            inline
            void toRodrigues(const Matrix& r, Vector& xyz)
            {
                toRodrigues(r, xyz(0), xyz(1), xyz(2));
            }

            template<typename Matrix, typename Real>
            inline
            void toSkewSymmetric(const Matrix& r, Real& a, Real& b, Real& c)
            {
                a = (r(2, 1) - r(1, 2)) / 2.0f;
                b = (r(0, 2) - r(2, 0)) / 2.0f;
                c = (r(1, 0) - r(0, 1)) / 2.0f;
            }

            template<typename Matrix, typename Vector>
            inline
            void toSkewSymmetric(const Matrix& r, Vector& abc)
            {
                assert(abc.size() > 2);

                toSkewSymmetric(r, abc(0), abc(1), abc(2));
            }

            template<typename Matrix, typename Real>
            inline
            void toXyz(const Matrix& r, Real& x, Real& y, Real& z)
            {
                if (r(2, 0) > (1.0f - ::std::numeric_limits<Real>::epsilon()))
                { // gimbal lock: -sin(-M_PI_2) = 1
                    x = ::std::atan2(-r(0, 1), r(1, 1));
                    y = static_cast<Real> (-M_PI_2);
                    z = 0.0f;
                }
                else if (r(2, 0) < (-1.0f
                        + ::std::numeric_limits<Real>::epsilon()))
                { // gimbal lock: -sin(M_PI_2) = -1
                    x = -::std::atan2(-r(0, 1), r(1, 1));
                    y = static_cast<Real> (M_PI_2);
                    z = 0.0f;
                }
                else
                {
                    x = ::std::atan2(r(2, 1), r(2, 2));
                    y = ::std::atan2(-r(2, 0), ::std::sqrt(::std::pow(r(2, 1),
                            2) + ::std::pow(r(2, 2), 2)));
                    z = ::std::atan2(r(1, 0), r(0, 0));
                }
            }

            template<typename Matrix, typename Vector>
            inline
            void toXyz(const Matrix& r, Vector& xyz)
            {
                toXyz(r, xyz(0), xyz(1), xyz(2));
            }
        }
    }
}

#endif /* _CF_MATH_TRANSFORM_HPP_ */

