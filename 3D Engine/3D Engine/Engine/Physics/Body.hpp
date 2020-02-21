#ifndef PHYSICS_BODY_HPP
#define PHYSICS_BODY_HPP
#include "../Math/Vector.hpp"
#include "../Math/Bounds.hpp"
#include "../Containers/SList.hpp"
#include "Collider.hpp"
#include "PhysicsProperty.hpp"

namespace Physics {

	class Body {
	protected:

		// is this body actve
		bool simulated;

		// the attached collider
		Collider* collider;

		// the list of physics properties
		SList<PhysicsProperty*> properties;

		Math::Bounds3D bounds;
		Math::Vector3 position;
		Math::Vector3 rotation;

		float friction;
		float bounce;
		float mass;
		float density;

	public:

		Body() : simulated(true), collider(nullptr), bounds(0.0f, 0.0f), position(0.0f), friction(0.0f), bounce(0.0f), mass(1.0f), density(1.0f) { }
		virtual ~Body() = 0 {
			// delete the collider
			if (collider) delete collider;
			collider = nullptr;

			// delete the properties
			for (PhysicsProperty* pp : properties)
				delete pp;
			properties.clear();
		}

		/// setting/adding/removing components

		// sets the collider to type C
		template<typename C> 
		C* SetCollider() {
			// delete old collider
			if (collider) delete collider;

			// create a collider of type C and attach it
			C* coll = new C();
			collider = coll;
			collider->body = this;

			// update bounds
			UpdateBounds();

			// return the collider as type C
			return coll;
		}

		// deletes the currently attached collider
		void DestroyCollider() {
			// delete old collider
			if (collider) delete collider;
		}

		// creates a PhysicsProperty of type P
		template<typename P>
		P* CreateProperty() {
			// create property of type P and attach
			P* prop = new P();
			PhysicsProperty* pp = prop;
			pp->body = this;
			properties.push_back(pp);

			// return the property as type P
			return prop;
		}

		// finds a property of type P
		template<typename P>
		P* GetProperty() {
			for (PhysicsProperty* prop : properties)
				if (P* p = dynamic_cast<P*>(prop))
					return p;

			// if it could not find the property then return nullptr
			return nullptr;
		}

		// delete the property
		bool DeleteProperty(PhysicsProperty* prop) {
			SList<PhysicsProperty*>::Iterator iter = properties.begin();
			while (iter != properties.end()) {
				if (*iter == prop) {
					// delete and remove the property
					delete prop;
					properties.erase(iter);

					// return true as it deleted the property
					return true;
				}
			}

			// return false if it couldnt find the property
			return false;
		}


		/// getters

		bool GetSimulated() const { return simulated; }
		Collider* GetCollider() const { return collider; }
		template<typename C> 
		C* GetCollider() const { return static_cast<C*>(collider); }
		Math::Bounds3D GetBounds() const { return bounds; }
		Math::Vector3 GetPosition() const { return position; }
		Math::Vector3 GetRotation() const { return rotation; }
		float GetFriction() const { return friction; }
		float GetBounce() const { return bounce; }
		float GetMass() const { return mass; }
		float GetDensity() const { return density; }

		/// setters

		void SetSimulated(const bool& simulated_) { simulated = simulated_; }
		void SetPosition(const Math::Vector3& position_) {
			position = position_; UpdateBounds();
		}
		void SetRotation(const Math::Vector3& rotation_) {
			rotation = rotation_; UpdateBounds();
		}
		void SetFriction(const float& friction_) {
			friction = friction_;
			if (friction <= 0.0f) friction = 0.0f;
		}
		void SetBounce(const float& bounce_) {
			bounce = bounce_;
			if (bounce <= 0.0f) bounce = 0.0f;
		}
		void SetMass(const float& mass_) {
			mass = mass_;
			if (mass <= 0.00001f) mass = 0.00001f;
		}
		void SetDensity(const float& density_) {
			density = density_;
			if (density <= 0.00001f) density = 0.00001f;
		}

		/// member functions

		void UpdateBounds() {
			bounds = collider->GetBounds(position, rotation);
		}



	};

}

#endif // !PHYSICS_BODY_HPP