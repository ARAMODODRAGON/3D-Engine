#ifndef MATH_BOUNDS_HPP
#define MATH_BOUNDS_HPP
#include "Vector.hpp"

namespace Math {

	struct Bounds2D {

		Vector2 min, max;

		Bounds2D() : min(0.0f), max(0.0f) { }
		Bounds2D(const Vector2& min_, const Vector2& max_) 
			: min(min_), max(max_) { }

		static bool Intersects(const Bounds2D& b0, const Bounds2D& b1) {
			// checks if max < min and min > max
			if (b0.max.x < b1.min.x || b0.min.x > b1.max.x) return false;
			if (b0.max.y < b1.min.y || b0.min.y > b1.max.y) return false;

			// if none of the prev returned then return true
			return true;
		}

		static bool Contains(const Bounds2D& b, const Vector2& p) {
			// checks if p < min and p > max
			if (p.x < b.min.x || p.x > b.max.x) return false;
			if (p.y < b.min.y || p.y > b.max.y) return false;

			// if none of the prev returned then return true
			return true;
		}
	};


	struct Bounds3D {

		Vector3 min, max;

		Bounds3D() : min(0.0f), max(0.0f) { }
		Bounds3D(const Vector3& min_, const Vector3& max_) 
			: min(min_), max(max_) { }

		static bool Intersects(const Bounds3D& b0, const Bounds3D& b1) {
			// checks if max < min and min > max
			if (b0.max.x < b1.min.x || b0.min.x > b1.max.x) return false;
			if (b0.max.y < b1.min.y || b0.min.y > b1.max.y) return false;
			if (b0.max.z < b1.min.z || b0.min.z > b1.max.z) return false;

			// if none of the prev returned then return true
			return true;
		}
		
		static bool Intersects(const Bounds3D& b, const Vector3& p) {
			// checks if p < min and p > max
			if (p.x < b.min.x || p.x > b.max.x) return false;
			if (p.y < b.min.y || p.y > b.max.y) return false;
			if (p.z < b.min.z || p.z > b.max.z) return false;

			// if none of the prev returned then return true
			return true;
		}

	};

}

#endif // !MATH_BOUNDS_HPP