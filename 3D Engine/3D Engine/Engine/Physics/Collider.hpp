#ifndef PHYSICS_COLLIDER_HPP
#define PHYSICS_COLLIDER_HPP
#include "../Math/Vector.hpp"
#include "../Math/Bounds.hpp"

namespace Physics {

	class Body;

	enum class CollisionShape : unsigned char { None, Sphere };

	class Collider {
	protected:
		friend Body;

		// the body that the collider is attached to
		Body* body;

		/// position and rotation relative to the bodies position
		Math::Vector3 position;
		Math::Vector3 rotation;

		// called from body to update bounds
		virtual Math::Bounds3D GetBounds(const Math::Vector3& bodyPos, const Math::Vector3& bodyRot) = 0;

		// called by the collider to update the bounds in the body
		void UpdateBounds();

	public:

		Collider() : body(nullptr), position(0.0f), rotation(0.0f) { }
		virtual ~Collider() = 0 { }

		/// getters

		Body* GetBody() const { return body; }
		template<typename B>
		B* GetBody() const { return static_cast<B*>(body); }
		Math::Vector3 GetPosition() const { return position; }
		Math::Vector3 GetRotation() const { return rotation; }
		Math::Vector3 GetWorldPosition() const;
		Math::Vector3 GetWorldRotation() const;
		virtual CollisionShape GetCollisionShape() const = 0 { return CollisionShape::None; }

		/// setters

		void SetPosition(const Math::Vector3& position_) { position = position_; }
		void SetRotation(const Math::Vector3& rotation_) { rotation = rotation_; }


	};

}

#endif // !PHYSICS_COLLIDER_HPP