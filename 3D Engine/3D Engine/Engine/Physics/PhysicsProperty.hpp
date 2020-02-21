#ifndef PHYSICS_PHYSICS_PROPERTY_HPP
#define PHYSICS_PHYSICS_PROPERTY_HPP
#include "../Math/Vector.hpp"

namespace Physics {
	class Body;

	class PhysicsProperty {
	protected:
		friend Body;

		// the attached body
		Body* body;

	public:

		PhysicsProperty() { }
		virtual ~PhysicsProperty() = 0 { }

		/// getters

		Body* GetBody() const { return body; }
		template<typename B>
		B* GetBody() const { return static_cast<B*>(body); }

	};

}

#endif // !PHYSICS_PHYSICS_PROPERTY_HPP