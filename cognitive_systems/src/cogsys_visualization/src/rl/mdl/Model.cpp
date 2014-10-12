//
// Copyright (c) 2009, Markus Rickert
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

#include "Body.h"
#include "Compound.h"
#include "Exception.h"
#include "Joint.h"
#include "Model.h"
#include "World.h"

namespace rl
{
	namespace mdl
	{
		Model::Model() :
			bodies(),
			elements(),
			frames(),
			G(),
			invG(),
			joints(),
			leaves(),
			manufacturer(),
			name(),
			root(0),
			tools(),
			transforms(),
			tree()
		{
		}
		
		Model::~Model()
		{
		}
		
		void
		Model::add(Compound* compound, const Frame* a, const Frame* b)
		{
			compound->inTransform = new Transform();
			this->add(compound->inTransform, a, compound->inFrame);
			
			compound->outTransform = new Transform();
			this->add(compound->outTransform, compound->outFrame, b);
		}
		
		void
		Model::add(Frame* frame)
		{
			Vertex vertex = ::boost::add_vertex(this->tree);
			frame->setVertexDescriptor(vertex);
			this->tree[vertex].reset(frame);
			
			if (dynamic_cast< World* >(frame))
			{
				this->root = vertex;
			}
		}
		
		void
		Model::add(Transform* transform, const Frame* a, const Frame* b)
		{
			Edge edge = ::boost::add_edge(a->getVertexDescriptor(), b->getVertexDescriptor(), this->tree).first;
			transform->setEdgeDescriptor(edge);
			this->tree[edge].reset(transform);
		}
		
		bool
		Model::areColliding(const ::std::size_t& i, const ::std::size_t& j) const
		{
			assert(i < this->bodies.size());
			assert(j < this->bodies.size());
			
			if (this->bodies[i]->selfcollision.count(this->bodies[j]) > 0 || this->bodies[j]->selfcollision.count(this->bodies[i]) > 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		
		Model*
		Model::clone() const
		{
			return new Model(*this);
		}
		
		void
		Model::getAcceleration(::rl::math::Vector& ydd) const
		{
			::rl::math::Vector qdd(this->getJointDof());
			
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				qdd.segment(j, this->joints[i]->getDof()) = this->joints[i]->getAcceleration();
			}
			
			ydd = this->invG * qdd;
		}
		
		void
		Model::getAccelerationUnits(::Eigen::Matrix< ::rl::math::Unit, ::Eigen::Dynamic, 1 >& units) const
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				units.segment(j, this->joints[i]->getDof()) = this->joints[i]->getAccelerationUnits();
			}
		}
		
		::std::size_t
		Model::getBodies() const
		{
			return this->bodies.size();
		}
		
		Body*
		Model::getBody(const ::std::size_t& i) const
		{
			assert(i < this->bodies.size());
			
			return this->bodies[i];
		}
		
		::std::size_t
		Model::getDof() const
		{
			return this->G.cols();
		}
		
		::std::size_t
		Model::getDofPosition() const
		{
			::std::size_t dof = 0;
			
			for (::std::size_t i = 0; i < this->joints.size(); ++i)
			{
				dof += this->joints[i]->getDofPosition();
			}
			
			return dof;
		}
		
		const ::rl::math::Transform&
		Model::getFrame(const ::std::size_t& i) const
		{
			assert(i < this->getBodies());
			
			return this->bodies[i]->t;
		}
		
		const ::rl::math::Matrix&
		Model::getGamma() const
		{
			return this->G;
		}
		
		const ::rl::math::Matrix&
		Model::getGammaInverse() const
		{
			return this->invG;
		}
		
		Joint*
		Model::getJoint(const ::std::size_t& i) const
		{
			assert(i < this->joints.size());
			
			return this->joints[i];
		}
		
		::std::size_t
		Model::getJointDof() const
		{
			::std::size_t dof = 0;
			
			for (::std::size_t i = 0; i < this->joints.size(); ++i)
			{
				dof += this->joints[i]->getDof();
			}
			
			return dof;
		}
		
		::std::size_t
		Model::getJoints() const
		{
			return this->joints.size();
		}
		
		const ::rl::math::MotionVector&
		Model::getOperationalAcceleration(const ::std::size_t& i) const
		{
			assert(i < this->getOperationalDof());
			
			return this->tree[this->leaves[i]]->a;
		}
		
		::std::size_t
		Model::getOperationalDof() const
		{
			return this->leaves.size();
		}
		
		const ::rl::math::ForceVector&
		Model::getOperationalForce(const ::std::size_t& i) const
		{
			assert(i < this->getOperationalDof());
			
			return this->tree[this->leaves[i]]->f;
		}
		
		const ::rl::math::Transform&
		Model::getOperationalPosition(const ::std::size_t& i) const
		{
			assert(i < this->getOperationalDof());
			
			return this->tree[this->leaves[i]]->t;
		}
		
		const ::rl::math::MotionVector&
		Model::getOperationalVelocity(const ::std::size_t& i) const
		{
			assert(i < this->getOperationalDof());
			
			return this->tree[this->leaves[i]]->v;
		}
		
		const ::std::string&
		Model::getManufacturer() const
		{
			return this->manufacturer;
		}
		
		void
		Model::getMaximum(::rl::math::Vector& max) const
		{
//			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDofPosition(), ++i)
//			{
//				max.segment(j, this->joints[i]->getDofPosition()) = this->joints[i]->getMaximum();
//			}
			max(0) = this->joints[0]->getMaximum()(0);
			max(1) = this->joints[1]->getMaximum()(0);
			max(2) = this->joints[3]->getMaximum()(0);
		}
		
		void
		Model::getMinimum(::rl::math::Vector& min) const
		{
//			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDofPosition(), ++i)
//			{
//				min.segment(j, this->joints[i]->getDofPosition()) = this->joints[i]->getMinimum();
//			}
			min(0) = this->joints[0]->getMinimum()(0);
			min(1) = this->joints[1]->getMinimum()(0);
			min(2) = this->joints[3]->getMinimum()(0);
		}
		
		const ::std::string&
		Model::getName() const
		{
			return this->name;
		}
		
		void
		Model::getPosition(::rl::math::Vector& y) const
		{
			::rl::math::Vector q(this->getJointDof());
			
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDofPosition(), ++i)
			{
				q.segment(j, this->joints[i]->getDofPosition()) = this->joints[i]->getPosition();
			}
			
			y = this->invG * q;
		}
		
		void
		Model::getPositionUnits(::Eigen::Matrix< ::rl::math::Unit, ::Eigen::Dynamic, 1 >& units) const
		{
//			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDofPosition(), ++i)
//			{
//				units.segment(j, this->joints[i]->getDofPosition()) = this->joints[i]->getPositionUnits();
//			}
			for (::std::ptrdiff_t i = 0, j = 0; i < units.size(); ++i)
			{
				units(i) = ::rl::math::UNIT_RADIAN;
			}
		}
		
		void
		Model::getTorque(::rl::math::Vector& tau) const
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				tau.segment(j, this->joints[i]->getDof()) = this->joints[i]->getTorque();
			}
		}
		
		void
		Model::getTorqueUnits(::Eigen::Matrix< ::rl::math::Unit, ::Eigen::Dynamic, 1 >& units) const
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				units.segment(j, this->joints[i]->getDof()) = this->joints[i]->getTorqueUnits();
			}
		}
		
		void
		Model::getSpeed(::rl::math::Vector& speed) const
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				speed.segment(j, this->joints[i]->getDof()) = this->joints[i]->getSpeed();
			}
		}
		
		void
		Model::getSpeedUnits(::Eigen::Matrix< ::rl::math::Unit, ::Eigen::Dynamic, 1 >& units) const
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				units.segment(j, this->joints[i]->getDof()) = this->joints[i]->getSpeedUnits();
			}
		}
		
		void
		Model::getVelocity(::rl::math::Vector& yd) const
		{
			::rl::math::Vector qd(this->getJointDof());
			
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				qd.segment(j, this->joints[i]->getDof()) = this->joints[i]->getVelocity();
			}
			
			yd = this->invG * qd;
		}
		
		void
		Model::getVelocityUnits(::Eigen::Matrix< ::rl::math::Unit, ::Eigen::Dynamic, 1 >& units) const
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				units.segment(j, this->joints[i]->getDof()) = this->joints[i]->getVelocityUnits();
			}
		}
		
		bool
		Model::isColliding(const ::std::size_t& i) const
		{
			assert(i < this->bodies.size());
			
			return this->bodies[i]->collision;
		}
		
		void
		Model::replace(Compound* compound, Transform* transform)
		{
			this->add(transform, compound->inFrame, compound->outFrame);
			this->remove(compound);
		}
		
		void
		Model::replace(Transform* transform, Compound* compound)
		{
			this->add(compound, transform->in, transform->out);
			this->remove(transform);
		}
		
		void
		Model::remove(Compound* compound)
		{
			this->remove(compound->inTransform);
			this->remove(compound->outTransform);
		}
		
		void
		Model::remove(Frame* frame)
		{
			::boost::clear_vertex(frame->getVertexDescriptor(), this->tree);
			
			if (dynamic_cast< World* >(frame))
			{
				this->root = 0;
			}
			
			::boost::remove_vertex(frame->getVertexDescriptor(), this->tree);
		}
		
		void
		Model::remove(Transform* transform)
		{
			::boost::remove_edge(transform->getEdgeDescriptor(), this->tree);
		}
		
		void
		Model::setAcceleration(const ::rl::math::Vector& ydd)
		{
			::rl::math::Vector qdd = this->G * ydd;
			
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				this->joints[i]->setAcceleration(qdd.segment(j, this->joints[i]->getDof()));
			}
		}
		
		void
		Model::setGamma(const ::rl::math::Matrix& G)
		{
			this->G = G;
			::Eigen::JacobiSVD< ::rl::math::Matrix > svd(this->G, ::Eigen::ComputeThinU | ::Eigen::ComputeThinV);
			::rl::math::Vector singularValues(svd.singularValues().size());
			
			for (::std::ptrdiff_t i = 0; i < svd.singularValues().size(); ++i)
			{
				singularValues[i] = svd.singularValues()[i] > std::numeric_limits< ::rl::math::Real >::epsilon() ? 1 / svd.singularValues()[i] : 0;
			}
			
			this->invG = svd.matrixV() * singularValues.asDiagonal() * svd.matrixU().transpose();
		}
		
		void
		Model::setManufacturer(const ::std::string& manufacturer)
		{
			this->manufacturer = manufacturer;
		}
		
		void
		Model::setName(const ::std::string& name)
		{
			this->name = name;
		}
		
		void
		Model::setOperationalVelocity(const ::std::size_t& i, const ::rl::math::MotionVector& v) const
		{
			this->tree[this->leaves[i]]->v = v;
		}
		
		void
		Model::setPosition(const ::rl::math::Vector& y)
		{
			::rl::math::Vector q = this->G * y;
			
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDofPosition(), ++i)
			{
				this->joints[i]->setPosition(q.segment(j, this->joints[i]->getDofPosition()));
			}
		}
		
		void
		Model::setTorque(const ::rl::math::Vector& tau)
		{
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				this->joints[i]->setTorque(tau.segment(j, this->joints[i]->getDof()));
			}
		}
		
		void
		Model::setVelocity(const ::rl::math::Vector& yd)
		{
			::rl::math::Vector qd = this->G * yd;
			
			for (::std::size_t i = 0, j = 0; i < this->joints.size(); j += this->joints[i]->getDof(), ++i)
			{
				this->joints[i]->setVelocity(qd.segment(j, this->joints[i]->getDof()));
			}
		}
		
		::rl::math::Transform&
		Model::tool(const ::std::size_t& i)
		{
			assert(i < this->tools.size());
			
			return this->tree[this->tools[i]]->t;
		}
		
		const ::rl::math::Transform&
		Model::tool(const ::std::size_t& i) const
		{
			assert(i < this->tools.size());
			
			return this->tree[this->tools[i]]->t;
		}
		
		void
		Model::update()
		{
			this->bodies.clear();
			this->elements.clear();
			this->joints.clear();
			this->leaves.clear();
			this->tools.clear();
			this->transforms.clear();
			
			this->update(this->root);
		}
		
		void
		Model::update(const Vertex& u)
		{
			Frame* frame = this->tree[u].get();
			this->elements.push_back(frame);
			this->frames.push_back(frame);
			
			if (Body* body = dynamic_cast< Body* >(frame))
			{
				this->bodies.push_back(body);
			}
			
			if (::boost::out_degree(u, this->tree) > 0)
			{
				for (OutEdgeIteratorPair i = ::boost::out_edges(u, this->tree); i.first != i.second; ++i.first)
				{
					Edge e = *i.first;
					Vertex v = ::boost::target(e, this->tree);
					
					Transform* transform = this->tree[e].get();
					this->elements.push_back(transform);
					this->transforms.push_back(transform);
					transform->in = this->tree[u].get();
					transform->out = this->tree[v].get();
					
					if (Joint* joint = dynamic_cast< Joint* >(transform))
					{
						this->joints.push_back(joint);
					}
					
					this->update(v);
				}
			}
			else
			{
				this->leaves.push_back(u);
				
				for (InEdgeIteratorPair i = ::boost::in_edges(u, this->tree); i.first != i.second; ++i.first)
				{
					this->tools.push_back(*i.first);
				}
			}
			
			this->G.resize(this->getJointDof(), this->getJointDof());
			this->G.setIdentity();
			this->invG.resize(this->getJointDof(), this->getJointDof());
			this->invG.setIdentity();
		}
		
		::rl::math::Transform&
		Model::world()
		{
			return this->tree[this->root]->t;
		}
		
		const ::rl::math::Transform&
		Model::world() const
		{
			return this->tree[this->root]->t;
		}
	}
}
