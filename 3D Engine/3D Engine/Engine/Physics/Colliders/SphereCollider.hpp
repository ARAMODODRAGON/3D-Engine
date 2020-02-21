#ifndef PHYSICS_SPHERE_COLLIDER_HPP
#define PHYSICS_SPHERE_COLLIDER_HPP
#include "../Collider.hpp"

namespace Physics {

	class SphereColldier : public Collider {
	protected:

		// the circle radius
		float radius;

		// called from body to update bounds
		virtual Math::Bounds3D GetBounds(const Math::Vector3& bodyPos, const Math::Vector3& bodyRot) override {
			Math::Vector3 r = Math::Vector3(radius);
			return Math::Bounds3D(bodyPos + position - r, bodyPos + position + r);
		}

	public:

		SphereColldier() { }
		~SphereColldier() { }

		/// getters

		float GetRadius() const { return radius; }
		virtual CollisionShape GetCollisionShape() const override { return CollisionShape::Sphere; }

		/// setters

		void SetRadius(const float& radius_) { radius = radius_; UpdateBounds(); }




	};

}

#endif // !PHYSICS_SPHERE_COLLIDER_HPP