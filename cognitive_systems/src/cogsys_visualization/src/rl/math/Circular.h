//
// Copyright (c) 2009, Andre Gaschler
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef _RL_MATH_CIRCULAR_H_
#define _RL_MATH_CIRCULAR_H_

#include <cassert>
#include <cmath>
#include <limits>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/LU>

#include "Function.h"
#include "Matrix.h"
#include "Vector.h"

namespace rl
{
	namespace math
	{
		/**
		 * @brief Circular segment function that maps from a time x to a point in 2D or 3D on a circular trajectory.
		 * 
		 */
		class Circular : public Function
		{
		public:
			Circular() :
				Function(),
				angle(0)
			{
			}
			
			virtual ~Circular()
			{
			}
			
			Circular* clone() const
			{
				return new Circular(*this);
			}
			
			/**
			 * @brief Generates a circular segment function in 2D through three given points.
			 * 
			 * The given points most not be (numerically close to) colinear.
			 */
			static Circular ThreePoints(const Vector2& y0, const Vector2& yi, const Vector2& y1, const Real& x1 = 1)
			{
				Circular f;
				
				::Eigen::Matrix< Real, 2, 3 > points2d;
				points2d << y0, yi, y1;
				
				// Solve substituted system similar to http://www.arndt-bruenner.de/mathe/scripts/kreis3p.htm
				Matrix33 A;
				A << Matrix::Ones(3, 1), -points2d.transpose();
				Vector3 b = - (points2d.transpose() * points2d).diagonal();
				Vector3 x = A.fullPivLu().solve(b); 
				Vector2 center2d = x.bottomRows(2) / 2;
				Real radiusSquared = center2d.transpose() * center2d - x(0);
				Real radius = ::std::sqrt(radiusSquared);
				assert((A * x - b).norm() < 1e-8 && "Circular motion: Linear system cannot be solved. (Points must not be colinear.)");
					
				f.center = center2d;
				f.axisX = y0 - f.center;
				f.axisY = Vector2(f.axisX(1), -f.axisX(0));
				Real angleVia = ::std::atan2(f.axisY.transpose() * (yi - f.center), f.axisX.transpose() * (yi - f.center));
				
				if (angleVia < 0)
				{
					f.axisY *= -1.0;
				}
				
				f.angle = ::std::atan2(f.axisY.transpose() * (y1 - f.center), f.axisX.transpose() * (y1 - f.center));
				
				if (f.angle < 0)
				{
					f.angle += 2 * static_cast< Real >(M_PI);
				}
				
				f.x1 = x1;
				
				return f;
			}
			
			/**
			 * @brief Generates a circular segment through three given points in 3D.
			 * 
			 * The given points must not be (numerically close to) colinear.
			 */
			static Circular ThreePoints(const Vector3& y0, const Vector3& yi, const Vector3& y1, const Real& x1 = 1)
			{
				Circular f;
				
				Matrix33 points3d;
				points3d << y0, yi, y1;
				Vector3 planeNormal = (yi - y0).cross(y1 - y0);
				assert(planeNormal.norm() > 1e-8 && "Circular motion is ambiguous. Given three points must not be colinear!");
				planeNormal.normalize();
				Real planeD = planeNormal.transpose() * y0;
				
				// Numerically stable orthonormals
				Vector3 planeDirection1, planeDirection2;
				Vector3 someUnit(1, 0, 0);
				Vector3 someOtherUnit(0, 1, 0);
				
				if ((planeNormal.transpose() * someUnit).norm() < (planeNormal.transpose() * someOtherUnit).norm())
				{
					planeDirection1 = planeNormal.cross(someUnit);
				}
				else
				{
					planeDirection1 = planeNormal.cross(someOtherUnit);
				}
				
				planeDirection1.normalize();
				planeDirection2 = planeNormal.cross(planeDirection1);
				planeDirection2.normalize();
				
				// Project all points to a plane that contains the circular motion
				::Eigen::Matrix< Real, 2, 3 > projectionTo2d;
				projectionTo2d << planeDirection1.transpose(), planeDirection2.transpose();
				Vector2 y02d = projectionTo2d * y0;
				Vector2 yi2d = projectionTo2d * yi;
				Vector2 y12d = projectionTo2d * y1;
				
				Circular circ2d = Circular::ThreePoints(y02d, yi2d, y12d);
				f.center = projectionTo2d.transpose() * circ2d.getCenter() + planeNormal * planeD;
				f.axisX = y0 - f.center;
				f.axisY = planeNormal.cross(Vector3(f.axisX));
				f.angle = ::std::atan2(f.axisY.transpose() * (y1 - f.center), f.axisX.transpose() * (y1 - f.center));
				
				if (f.angle < 0)
				{
					f.angle += 2 * static_cast< Real >(M_PI);
				}
				
				f.x1 = x1;
				
				return f;
			}
			
			static Circular ThreePointsAngle(const Vector3& y0, const Vector3& yi, const Vector3& y1, const Real& angle, const Real& x1 = 1)
			{
				Circular c = ThreePoints(y0, yi, y1, x1);
				c.angle = angle;
				return c;
			}
			
			Real getAngle() const
			{
				return this->angle;
			}
			
			Vector getAxisX() const
			{
				return this->axisX;
			}
			
			Vector getAxisY() const
			{
				return this->axisY;
			}
			
			Vector getCenter() const
			{
				return this->center;
			}
			
			/**
			 * @brief Evaluates the circular segment function for a given x.
			 * 
			 * Note that only the first two derivatives are implemented, all higher orders will return NaN.
			 */
			ArrayX operator()(const Real& x, const ::std::size_t& derivative = 0) const
			{
				//assert(x >= this->lower());
				//assert(x <= this->upper());
				Real c = this->angle / this->x1;

				if (derivative == 0)
				{
					return this->center + ::std::cos(c * x) * this->axisX + ::std::sin(c * x) * this->axisY;
				}
				else if (derivative == 1)
				{
					return -c * ::std::sin(c * x) * this->axisX + c * ::std::cos(c * x) * this->axisY;
				}
				else if (derivative == 2)
				{
					return -::std::pow(c, 2) * ::std::cos(c * x) * this->axisX - ::std::pow(c, 2) * ::std::sin(c * x) * this->axisY;
				}
				else
				{
					return this->axisX * ::std::numeric_limits< Real >::signaling_NaN();
				}
			}
			
		protected:
			/** @brief Angle of circular motion. Any real value is allowed. */
			Real angle;
			
			/** @brief First axis of the circular motion. Note that at time 0, the function value is (center + axisX) */
			Vector axisX;
			
			/** @brief Second axis of the circular motion. After a motion of 90 degrees, the function value is (center + axisY) */
			Vector axisY;
			
			/** @brief Center of the circle. */
			Vector center;
			
		private:
			
		};
	}
}

#endif // _RL_MATH_CIRCULAR_H_
