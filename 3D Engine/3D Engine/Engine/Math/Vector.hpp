#ifndef MATH_FLOAT_VECTOR_HPP
#define MATH_FLOAT_VECTOR_HPP
#include "CommonMath.hpp"

namespace Math {

	struct Vector2 {
		float x, y;

		Vector2(const float& value = 0.0f)
			: x(value), y(value) { }
		Vector2(const float& x_, const float& y_)
			: x(x_), y(y_) { }

		/// member functions
		float Magnitude() const {
			return sqrtf(x * x + y * y);
		}
		float Sqrmagnitude() const {
			return x * x + y * y;
		}

		/// operators
		Vector2 operator+(const Vector2& other) const {
			return Vector2(x + other.x, y + other.y);
		}
		Vector2 operator-(const Vector2& other) const {
			return Vector2(x - other.x, y - other.y);
		}
		Vector2 operator*(const float& scalar) const {
			return Vector2(x * scalar, y * scalar);
		}
		friend Vector2 operator*(const float& scalar, const Vector2& vec) {
			return Vector2(vec.x * scalar, vec.y * scalar);
		}
		Vector2 operator/(const float& divisor) const {
			if (divisor == 0.0f) return Vector2(0.0f);
			return Vector2(x / divisor, y / divisor);
		}
		friend Vector2 operator/(const float& divisor, const Vector2& vec) {
			if (divisor == 0.0f) return Vector2(0.0f);
			return Vector2(vec.x / divisor, vec.y / divisor);
		}
		Vector2& operator+=(const Vector2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}
		Vector2& operator-=(const Vector2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}
		Vector2& operator*=(const float& scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}
		Vector2& operator/=(const float& divisor) {
			if (divisor == 0.0f) {
				x = y = 0.0f;
			} else {
				x /= divisor;
				y /= divisor;
			}
			return *this;
		}
		Vector2 operator-() const {
			return Vector2(-x, -y);
		}
		bool operator==(const Vector2& other) const {
			return x == other.x && y == other.y;
		}
		bool operator!=(const Vector2& other) const {
			return x != other.x || y != other.y;
		}
		const float& operator[](const int& index) const {
			return (&x)[index];
		}
		float& operator[](const int& index) {
			return (&x)[index];
		}

		/// static member functions
		static Vector2 Normalize(const Vector2& vec) {
			float mag = sqrtf(vec.x * vec.x + vec.y * vec.y);
			if (NearlyZero(mag, REALLY_SMALL)) return Vector2(0.0f);
			return Vector2(vec.x / mag, vec.y / mag);
		}
		static float Dot(const Vector2& v0, const Vector2& v1) {
			return v0.x * v1.x + v0.y * v1.y;
		}
		static Vector2 Relfect(const Vector2& direction, Vector2 normal) {
			return direction + normal * Dot(-direction, normal) * 2.0f;
		}

	};

	struct Vector3 {
		float x, y, z;

		Vector3(const float& value = 0.0f)
			: x(value), y(value), z(value) { }
		Vector3(const float& x_, const float& y_, const float& z_)
			: x(x_), y(y_), z(z_) { }

		/// up conversions
		Vector3(const Vector2& vec, const float& z_)
			: x(vec.x), y(vec.y), z(z_) { }
		Vector3(const float& x_, const Vector2& vec)
			: x(x_), y(vec.x), z(vec.y) { }

		/// member functions
		float Magnitude() const {
			return sqrtf(x * x + y * y + z * z);
		}
		float Sqrmagnitude() const {
			return x * x + y * y + z * z;
		}

		/// operators
		Vector3 operator+(const Vector3& other) const {
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		Vector3 operator-(const Vector3& other) const {
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		Vector3 operator*(const float& scalar) const {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}
		friend Vector3 operator*(const float& scalar, const Vector3 vec) {
			return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
		}
		Vector3 operator/(const float& divisor) const {
			if (divisor == 0.0f) return Vector3(0.0f);
			return Vector3(x / divisor, y / divisor, z / divisor);
		}
		friend Vector3 operator/(const float& divisor, const Vector3 vec) {
			if (divisor == 0.0f) return Vector3(0.0f);
			return Vector3(vec.x / divisor, vec.y / divisor, vec.z / divisor);
		}

		Vector3& operator+=(const Vector3& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		Vector3& operator-=(const Vector3& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		Vector3& operator*=(const float& scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}
		Vector3& operator/=(const float& divisor) {
			if (divisor == 0.0f) {
				x = y = z = 0.0f;
			} else {
				x /= divisor;
				y /= divisor;
				z /= divisor;
			}
			return *this;
		}
		Vector3 operator-() const {
			return Vector3(-x, -y, -z);
		}
		bool operator==(const Vector3& other) const {
			return x == other.x && y == other.y && z == other.z;
		}
		bool operator!=(const Vector3& other) const {
			return x != other.x || y != other.y || z != other.z;
		}
		const float& operator[](const int& index) const {
			return (&x)[index];
		}
		float& operator[](const int& index) {
			return (&x)[index];
		}

		/// static member functions
		static Vector3 Normalize(const Vector3& vec) {
			float mag = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
			if (NearlyZero(mag, REALLY_SMALL)) return Vector3(0.0f);
			return Vector3(vec.x / mag, vec.y / mag, vec.z / mag);
		}
		static float Dot(const Vector3& v0, const Vector3& v1) {
			return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
		}
		static Vector3 Relfect(const Vector3& direction, Vector3 normal) {
			return direction + normal * Dot(-direction, normal) * 2.0f;
		}
		static Vector3 Cross(const Vector3& v0, const Vector3& v1) {
			return Vector3(v0.y * v1.z + v0.z * v1.y, v0.x * v1.z - v0.z * v1.x, v0.x * v1.y + v0.y * v1.x);
		}

	};

	struct Vector4 {
		float x, y, z, w;

		Vector4(const float& value = 0.0f)
			: x(value), y(value), z(value), w(value) { }
		Vector4(const float& x_, const float& y_, const float& z_, const float& w_)
			: x(x_), y(y_), z(z_), w(w_) { }

		/// up conversions
		Vector4(const Vector2& vec, const float& z_, const float& w_)
			: x(vec.x), y(vec.y), z(z_), w(w_) { }
		Vector4(const float& x_, const Vector2& vec, const float& w_)
			: x(x_), y(vec.x), z(vec.y), w(w_) { }
		Vector4(const float& x_, const float& y_, const Vector2& vec)
			: x(x_), y(y_), z(vec.x), w(vec.y) { }
		Vector4(const Vector3& vec, const float& w_)
			: x(vec.x), y(vec.y), z(vec.z), w(w_) { }
		Vector4(const float& x_, const Vector3& vec)
			: x(x_), y(vec.x), z(vec.y), w(vec.z) { }

		/// member functions
		float Magnitude() const {
			return sqrtf(x * x + y * y + z * z + w * w);
		}
		float Sqrmagnitude() const {
			return x * x + y * y + z * z + w * w;
		}

		/// operators
		Vector4 operator+(const Vector4& other) const {
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		Vector4 operator-(const Vector4& other) const {
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}
		Vector4 operator*(const float& scalar) const {
			return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
		}
		friend Vector4 operator*(const float& scalar, const Vector4& vec) {
			return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
		}
		Vector4 operator/(const float& divisor) const {
			if (divisor == 0.0f) return Vector4(0.0f);
			return Vector4(x / divisor, y / divisor, z / divisor, w / divisor);
		}
		friend Vector4 operator/(const float& divisor, const Vector4& vec) {
			if (divisor == 0.0f) return Vector4(0.0f);
			return Vector4(vec.x / divisor, vec.y / divisor, vec.z / divisor, vec.w / divisor);
		}
		Vector4& operator+=(const Vector4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		Vector4& operator-=(const Vector4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}
		Vector4& operator*=(const float& scalar) {
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}
		Vector4& operator/=(const float& divisor) {
			if (divisor == 0.0f) {
				x = y = z = w = 0.0f;
			} else {
				x /= divisor;
				y /= divisor;
				z /= divisor;
				w /= divisor;
			}
			return *this;
		}
		Vector4 operator-() const {
			return Vector4(-x, -y, -z, -w);
		}
		bool operator==(const Vector4& other) const {
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}
		bool operator!=(const Vector4& other) const {
			return x != other.x || y != other.y || z != other.z || w != other.w;
		}
		const float& operator[](const int& index) const {
			return (&x)[index];
		}
		float& operator[](const int& index) {
			return (&x)[index];
		}

		/// static member functions
		static Vector4 Normalize(const Vector4& vec) {
			float mag = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
			if (NearlyZero(mag, REALLY_SMALL)) return Vector4(0.0f);
			return Vector4(vec.x / mag, vec.y / mag, vec.z / mag, vec.w / mag);
		}
		static float Dot(const Vector4& v0, const Vector4& v1) {
			return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
		}
		static Vector4 Relfect(const Vector4& direction, Vector4 normal) {
			return direction + normal * Dot(-direction, normal) * 2.0f;
		}

	};

}

#endif // !MATH_FLOAT_VECTOR_HPP