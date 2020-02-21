#ifndef PHYSICS_RIGIDBODY_HPP
#define PHYSICS_RIGIDBODY_HPP
#include "Body.hpp"

namespace Physics {

	class Rigidbody : public Body {
	protected:

		/// motion
		Math::Vector3 velocity;
		Math::Vector3 acceleration;
		Math::Vector3 angularVelocity;
		Math::Vector3 angularAcceleration;

	public:

		Rigidbody();
		~Rigidbody();

		/// getters

		Math::Vector3 GetVelocity() const { return velocity; }
		Math::Vector3 GetAcceleration() const { return acceleration; }
		Math::Vector3 GetAngularVelocity() const { return angularVelocity; }
		Math::Vector3 GetAngularAcceleration() const { return angularAcceleration; }

		/// setters

		void SetVelocity(const float& velocity_) { velocity = velocity_; }
		void SetAcceleration(const float& acceleration_) { acceleration = acceleration_; }
		void SetAngularVelocity(const float& angularVelocity_) { angularVelocity = angularVelocity_; }
		void SetAngularAcceleration(const float& angularAcceleration_) { angularAcceleration = angularAcceleration_; }



	};

}

#endif // !PHYSICS_RIGIDBODY_HPP