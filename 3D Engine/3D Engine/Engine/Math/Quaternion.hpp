#ifndef MATH_QUATERNION_HPP
#define MATH_QUATERNION_HPP
#include "CommonMath.hpp"

namespace Math {

	struct Quaternion {

		float w, x, y, z;

		Quaternion() : w(0.0f), x(0.0f), y(0.0f), z(0.0f) { }
		Quaternion(float w_, float x_, float y_, float z_)
			: w(w_), x(x_), y(y_), z(z_) { }

		/// operators
		Quaternion operator*(Quaternion other) {
			Vector3 ot(other.x, other.y, other.z);
			Vector3 ts(x, y, z);
			Vector3 ve = w * ot + other.w * ts + Vector3::Cross(ts, ot);
			return Quaternion(ve.x, ve.y, ve.z, w * other.w - Vector3::Dot(ts, ot));
		}
		Vector3 operator*(const Vector3& vec) {
			Quaternion res = *this * Quaternion(vec.x, vec.y, vec.z, 0.0f) * Conjugate(*this);
			return Vector3(res.x, res.y, res.z);
		}

		/// member functions
		float Magnitude() const {
			return sqrtf(w * w + x * x + y * y + z * z);
		}
		Vector3 ToEulerAngles() const {
			Vector3 euler;
			euler.z = atanf((2 * (w * x + y * z)) / (1 - 2 * (x * x + y * y)));
			euler.y = asinf(2 * (w * y - z * x));
			euler.x = atanf((2 * (w * z + x * y)) / (1 - 2 * (x * x + y * y)));
			return euler;
		}

		/// static member functions
		static Quaternion Normalize(const Quaternion& q) {
			Quaternion res = q;
			float mag = res.Magnitude();
			res.x /= mag;
			res.y /= mag;
			res.z /= mag;
			res.w /= mag;
			return res;
		}
		static Quaternion Conjugate(const Quaternion& q) {
			Quaternion res = q;
			res.x = -res.x;
			res.y = -res.y;
			res.z = -res.z;
			return res;
		}
		static Quaternion Inverse(const Quaternion& q) {
			Quaternion res = Conjugate(q);
			float mags = q.Magnitude(); mags *= mags;
			res.x = res.x / mags;
			res.y = res.y / mags;
			res.z = res.z / mags;
			res.w = res.w / mags;
		}
		static Quaternion Eular(const float& x, const float& y, const float& z) {
			float cy = cosf(DEG_TO_RAD(z) * 0.5f);
			float sy = sinf(DEG_TO_RAD(z) * 0.5f);
			float cp = cosf(DEG_TO_RAD(y) * 0.5f);
			float sp = sinf(DEG_TO_RAD(y) * 0.5f);
			float cr = cosf(DEG_TO_RAD(x) * 0.5f);
			float sr = sinf(DEG_TO_RAD(x) * 0.5f);

			Quaternion q;
			q.w = cy * cp * cr + sy * sp * sr;
			q.x = cy * cp * sr - sy * sp * cr;
			q.y = sy * cp * sr + cy * sp * cr;
			q.z = sy * cp * cr - cy * sp * sr;

			return q;
		}
		static Quaternion Eular(const Vector3& euler) {
			float cy = cosf(DEG_TO_RAD(euler.z) * 0.5f);
			float sy = sinf(DEG_TO_RAD(euler.z) * 0.5f);
			float cp = cosf(DEG_TO_RAD(euler.y) * 0.5f);
			float sp = sinf(DEG_TO_RAD(euler.y) * 0.5f);
			float cr = cosf(DEG_TO_RAD(euler.x) * 0.5f);
			float sr = sinf(DEG_TO_RAD(euler.x) * 0.5f);

			Quaternion q;
			q.w = cy * cp * cr + sy * sp * sr;
			q.x = cy * cp * sr - sy * sp * cr;
			q.y = sy * cp * sr + cy * sp * cr;
			q.z = sy * cp * cr - cy * sp * sr;

			return q;
		}
		static Quaternion FromToVectorsNormalized(const Vector3& from, const Vector3& to) {
			Quaternion res;

			Vector3 a = Vector3::Cross(from, to);
			res.x = a.x;
			res.y = a.y;
			res.z = a.z;

			float mag0 = from.Magnitude();
			float mag1 = to.Magnitude();

			res.w = mag0 * mag1 + Vector3::Dot(from, to);

			return Quaternion::Normalize(res);
		}
		static Quaternion FromToVectors(const Vector3& from, const Vector3& to) {
			Quaternion res;

			Vector3 a = Vector3::Cross(from, to);
			res.x = a.x;
			res.y = a.y;
			res.z = a.z;

			float mag0 = from.Magnitude();
			float mag1 = to.Magnitude();

			res.w = mag0 * mag1 + Vector3::Dot(from, to);

			return res;
		}
		static Quaternion AxisAngle(const Vector3& axis, const float& angle) {
			Quaternion res;

			float rad = DEG_TO_RAD(angle);
			float t = sinf(rad / 2.0f);

			res.w = cosf(rad / 2.0f);
			res.x = axis.x * t;
			res.y = axis.y * t;
			res.z = axis.z * t;

			return res;
		}

	};

}

#endif // !MATH_QUATERNION_HPP