#include "GravityWell.hpp"
#include "../Body.hpp"

namespace Physics {

	Math::Vector3 GravityWell::GetWorldPosition() const {
		return position + body->GetPosition();
	}

}