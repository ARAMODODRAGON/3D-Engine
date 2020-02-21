#ifndef PHYSICS_GRAVITY_WELL_HPP
#define PHYSICS_GRAVITY_WELL_HPP
#include "../PhysicsProperty.hpp"

namespace Physics {

	class GravityWell : public PhysicsProperty {
	protected:

		// the wells position
		Math::Vector3 position;

		// the strength of gravity
		float gravity;
		// the range of the gravity well
		float range;

	public:

		GravityWell() { }
		~GravityWell() { }

		/// getters

		Math::Vector3 GetPosition() const { return position; }
		Math::Vector3 GetWorldPosition() const;

	};

}

#endif // !PHYSICS_GRAVITY_WELL_HPP