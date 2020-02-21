#include "Collider.hpp"
#include "Body.hpp"

namespace Physics {

	void Collider::UpdateBounds() { 
		// call update bounds on the body
		body->UpdateBounds();
	}

	Math::Vector3 Collider::GetWorldPosition() const {
		return position + body->GetPosition();
	}

	Math::Vector3 Collider::GetWorldRotation() const {
		return rotation + body->GetRotation();
	}

}