#ifndef MATH_MATRIX_HPP
#define MATH_MATRIX_HPP
#include "Vector.hpp"
#include "CommonMath.hpp"

namespace Math {

	/// 3 x 3 and 4 x 4 matricies
	/// row centric


	struct Matrix3 {
		// the data
		float m[9];

		Matrix3()
			: m {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f} { }
		Matrix3(
			const float& m00, const float& m01, const float& m02,
			const float& m10, const float& m11, const float& m12,
			const float& m20, const float& m21, const float& m22
		) : m {m00, m01, m02, m10, m11, m12, m20, m21, m22} { }

		/// copy & move constructors/operators

		Matrix3(const Matrix3& mat)
			: m {mat.m[0], mat.m[1], mat.m[2], mat.m[3], mat.m[4], mat.m[5], mat.m[6], mat.m[7], mat.m[8]} { }
		Matrix3& operator=(const Matrix3& mat) {
			m[0] = mat.m[0]; m[3] = mat.m[3]; m[6] = mat.m[6];
			m[1] = mat.m[1]; m[4] = mat.m[4]; m[7] = mat.m[7];
			m[2] = mat.m[2]; m[5] = mat.m[5]; m[8] = mat.m[8];
			return *this;
		}
		Matrix3(Matrix3&& mat)
			: m {mat.m[0], mat.m[1], mat.m[2], mat.m[3], mat.m[4], mat.m[5], mat.m[6], mat.m[7], mat.m[8]} { }
		Matrix3& operator=(Matrix3&& mat) {
			m[0] = mat.m[0]; m[3] = mat.m[3]; m[6] = mat.m[6];
			m[1] = mat.m[1]; m[4] = mat.m[4]; m[7] = mat.m[7];
			m[2] = mat.m[2]; m[5] = mat.m[5]; m[8] = mat.m[8];
			return *this;
		}

		/// operators
		Matrix3 operator*(const Matrix3& other) const {
			Matrix3 temp;

			// multiply the first row by the matrix
			temp.m[0] = m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6];
			temp.m[1] = m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7];
			temp.m[2] = m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8];

			// multiply the second row by the matrix
			temp.m[3] = m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6];
			temp.m[4] = m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7];
			temp.m[5] = m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8];

			// multiply the third row by the matrix
			temp.m[6] = m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6];
			temp.m[7] = m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7];
			temp.m[8] = m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8];

			//return the new matrix
			return temp;
		}
		Matrix3 operator+(const Matrix3& other) const {
			return Matrix3(
				m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2],
				m[3] + other.m[3], m[4] + other.m[4], m[5] + other.m[5],
				m[6] + other.m[6], m[7] + other.m[7], m[8] + other.m[8]
			);
		}
		Matrix3 operator-(const Matrix3& other) const {
			return Matrix3(
				m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2],
				m[3] - other.m[3], m[4] - other.m[4], m[5] - other.m[5],
				m[6] - other.m[6], m[7] - other.m[7], m[8] - other.m[8]
			);
		}
		Vector3 operator*(const Vector3& vec) const {
			Vector3 temp;

			temp.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z;
			temp.y = m[3] * vec.x + m[4] * vec.y + m[5] * vec.z;
			temp.z = m[6] * vec.x + m[7] * vec.y + m[8] * vec.z;

			return temp;
		}
		friend Vector3 operator*(const Vector3& vec, const Matrix3& mat) {
			Vector3 temp;

			temp.x = mat.m[0] * vec.x + mat.m[1] * vec.y + mat.m[2] * vec.z;
			temp.y = mat.m[3] * vec.x + mat.m[4] * vec.y + mat.m[5] * vec.z;
			temp.z = mat.m[6] * vec.x + mat.m[7] * vec.y + mat.m[8] * vec.z;

			return temp;
		}

		const float& operator[](const unsigned int& index) const {
			return m[index];
		}
		float& operator[](const unsigned int& index) {
			return m[index];
		}

		/// member functions
		Matrix3 Transpose() const {
			return Matrix3(m[0], m[3], m[6], m[1], m[4], m[7], m[2], m[5], m[8]);
		}
		float Determinant() const {
			// calculates and returns the determinant
			return m[0] * (m[4] * m[8] - m[5] * m[7]) - m[1] * (m[3] * m[8] - m[5] * m[6]) + m[2] * (m[3] * m[7] - m[4] * m[6]);
		}
		Matrix3 Inverse() const {
			float det = Determinant();
			Matrix3 temp0, temp1;

			// transpose
			temp1 = Transpose();

			// calculate minors
			temp0.m[0] = temp1.m[4] * temp1.m[8] - temp1.m[7] * temp1.m[5];
			temp0.m[1] = temp1.m[3] * temp1.m[8] - temp1.m[6] * temp1.m[5];
			temp0.m[2] = temp1.m[3] * temp1.m[7] - temp1.m[6] * temp1.m[4];

			temp0.m[3] = temp1.m[1] * temp1.m[8] - temp1.m[7] * temp1.m[2];
			temp0.m[4] = temp1.m[0] * temp1.m[8] - temp1.m[6] * temp1.m[2];
			temp0.m[5] = temp1.m[0] * temp1.m[7] - temp1.m[6] * temp1.m[1];

			temp0.m[6] = temp1.m[1] * temp1.m[5] - temp1.m[4] * temp1.m[2];
			temp0.m[7] = temp1.m[0] * temp1.m[5] - temp1.m[3] * temp1.m[2];
			temp0.m[8] = temp1.m[0] * temp1.m[4] - temp1.m[3] * temp1.m[1];
			// not gonna explain what happened there

			// calculate adjugates
			temp0.m[1] *= -1;
			temp0.m[3] *= -1;
			temp0.m[5] *= -1;
			temp0.m[7] *= -1;

			// calculate cofactors and load values back into the matrix
			temp0.m[0] = temp0.m[0] / det;
			temp0.m[1] = temp0.m[1] / det;
			temp0.m[2] = temp0.m[2] / det;
			temp0.m[3] = temp0.m[3] / det;
			temp0.m[4] = temp0.m[4] / det;
			temp0.m[5] = temp0.m[5] / det;
			temp0.m[6] = temp0.m[6] / det;
			temp0.m[7] = temp0.m[7] / det;
			temp0.m[8] = temp0.m[8] / det;

			return temp0;
		}

		/// static member functions
		static Matrix3 Identity() {
			return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		static Matrix3 Scale(const float& x, const float& y, const float& z) {
			return Matrix3(x, 0.0f, 0.0f, 0.0f, y, 0.0f, 0.0f, 0.0f, z);
		}
		static Matrix3 Scale(const Vector3& vec) {
			return Matrix3(vec.x, 0.0f, 0.0f, 0.0f, vec.y, 0.0f, 0.0f, 0.0f, vec.z);
		}
		static Matrix3 RotateX(const float& angle) {
			return Matrix3(
				1.0f, 0.0f, 0.0f, 
				0.0f, Cos(angle), -Sin(angle),
				0.0f, Sin(angle), Cos(angle)

			);
		}
		static Matrix3 RotateY(const float& angle) {
			return Matrix3(
				Cos(angle), 0.0f, Sin(angle),
				0.0f, 1.0f, 0.0f,
				-Sin(angle), 0.0f, Cos(angle)
			);
		}
		static Matrix3 RotateZ(const float& angle) {
			return Matrix3(
				Cos(angle), -Sin(angle), 0.0f,
				Sin(angle), Cos(angle), 0.0f,
				0.0f, 0.0f, 1.0f
			);
		}

	};


	struct Matrix4 {
		// the data
		float m[16];

		Matrix4()
			: m {1.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 1.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 1.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f} { }
		Matrix4(
			const float& m00, const float& m01, const float& m02, const float& m03,
			const float& m10, const float& m11, const float& m12, const float& m13,
			const float& m20, const float& m21, const float& m22, const float& m23,
			const float& m30, const float& m31, const float& m32, const float& m33
		) : m {m00, m01, m02, m03,
			   m10, m11, m12, m13,
			   m20, m21, m22, m23,
			   m30, m31, m32, m33} { }

		/// copy/move constructors and operators

		Matrix4(const Matrix4& mat)
			: m {mat.m[0], mat.m[1], mat.m[2], mat.m[3], mat.m[4], mat.m[5], mat.m[6], mat.m[7],
			mat.m[8], mat.m[9], mat.m[10], mat.m[11], mat.m[12], mat.m[13], mat.m[14], mat.m[15]} { }
		Matrix4& operator=(const Matrix4& mat) {
			m[0] = mat.m[0]; m[4] = mat.m[4]; m[8] = mat.m[8];	 m[12] = mat.m[12];
			m[1] = mat.m[1]; m[5] = mat.m[5]; m[9] = mat.m[9];	 m[13] = mat.m[13];
			m[2] = mat.m[2]; m[6] = mat.m[6]; m[10] = mat.m[10]; m[14] = mat.m[14];
			m[3] = mat.m[3]; m[7] = mat.m[7]; m[11] = mat.m[11]; m[15] = mat.m[15];
			return *this;
		}
		Matrix4(Matrix4&& mat)
			: m {mat.m[0], mat.m[1], mat.m[2], mat.m[3], mat.m[4], mat.m[5], mat.m[6], mat.m[7],
			mat.m[8], mat.m[9], mat.m[10], mat.m[11], mat.m[12], mat.m[13], mat.m[14], mat.m[15]} { }
		Matrix4& operator=(Matrix4&& mat) {
			m[0] = mat.m[0]; m[4] = mat.m[4]; m[8] = mat.m[8];	 m[12] = mat.m[12];
			m[1] = mat.m[1]; m[5] = mat.m[5]; m[9] = mat.m[9];	 m[13] = mat.m[13];
			m[2] = mat.m[2]; m[6] = mat.m[6]; m[10] = mat.m[10]; m[14] = mat.m[14];
			m[3] = mat.m[3]; m[7] = mat.m[7]; m[11] = mat.m[11]; m[15] = mat.m[15];
			return *this;
		}

		/// operators

		Matrix4 operator*(const Matrix4& other) const {
			Matrix4 temp;

			// 00 01 02 03
			// 04 05 06 07
			// 08 09 10 11
			// 12 13 14 15

			// multiply the first row by the matrix
			temp.m[0] = m[0] * other.m[0] + m[1] * other.m[4] + m[2] * other.m[8] + m[3] * other.m[12];
			temp.m[1] = m[0] * other.m[1] + m[1] * other.m[5] + m[2] * other.m[9] + m[3] * other.m[13];
			temp.m[2] = m[0] * other.m[2] + m[1] * other.m[6] + m[2] * other.m[10] + m[3] * other.m[14];
			temp.m[3] = m[0] * other.m[3] + m[1] * other.m[7] + m[2] * other.m[11] + m[3] * other.m[15];

			// multiply the second row by the matrix
			temp.m[4] = m[4] * other.m[0] + m[5] * other.m[4] + m[6] * other.m[8] + m[7] * other.m[12];
			temp.m[5] = m[4] * other.m[1] + m[5] * other.m[5] + m[6] * other.m[9] + m[7] * other.m[13];
			temp.m[6] = m[4] * other.m[2] + m[5] * other.m[6] + m[6] * other.m[10] + m[7] * other.m[14];
			temp.m[7] = m[4] * other.m[3] + m[5] * other.m[7] + m[6] * other.m[11] + m[7] * other.m[15];

			// multiply the third row by the matrix
			temp.m[8] = m[8] * other.m[0] + m[9] * other.m[4] + m[10] * other.m[8] + m[11] * other.m[12];
			temp.m[9] = m[8] * other.m[1] + m[9] * other.m[5] + m[10] * other.m[9] + m[11] * other.m[13];
			temp.m[10] = m[8] * other.m[2] + m[9] * other.m[6] + m[10] * other.m[10] + m[11] * other.m[14];
			temp.m[11] = m[8] * other.m[3] + m[9] * other.m[7] + m[10] * other.m[11] + m[11] * other.m[15];

			// multiply the fourth row by the matrix
			temp.m[12] = m[12] * other.m[0] + m[13] * other.m[4] + m[14] * other.m[8] + m[15] * other.m[12];
			temp.m[13] = m[12] * other.m[1] + m[13] * other.m[5] + m[14] * other.m[9] + m[15] * other.m[13];
			temp.m[14] = m[12] * other.m[2] + m[13] * other.m[6] + m[14] * other.m[10] + m[15] * other.m[14];
			temp.m[15] = m[12] * other.m[3] + m[13] * other.m[7] + m[14] * other.m[11] + m[15] * other.m[15];

			//return the new matrix
			return temp;
		}
		Matrix4 operator+(const Matrix4& other) const {
			return Matrix4(
				m[0] + other.m[0], m[1] + other.m[1], m[2] + other.m[2], m[3] + other.m[3],
				m[4] + other.m[4], m[5] + other.m[5], m[6] + other.m[6], m[7] + other.m[7],
				m[8] + other.m[8], m[9] + other.m[9], m[10] + other.m[10], m[11] + other.m[11],
				m[12] + other.m[12], m[13] + other.m[13], m[14] + other.m[14], m[15] + other.m[15]
			);
		}
		Matrix4 operator-(const Matrix4& other) const {
			return Matrix4(
				m[0] - other.m[0], m[1] - other.m[1], m[2] - other.m[2], m[3] - other.m[3],
				m[4] - other.m[4], m[5] - other.m[5], m[6] - other.m[6], m[7] - other.m[7],
				m[8] - other.m[8], m[9] - other.m[9], m[10] - other.m[10], m[11] - other.m[11],
				m[12] - other.m[12], m[13] - other.m[13], m[14] - other.m[14], m[15] - other.m[15]
			);
		}
		Vector3 operator*(const Vector3& vec) const {
			Vector3 res;

			res.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3];
			res.y = m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7];
			res.z = m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11];
			//w = m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15];

			return res;
		}
		friend Vector3 operator*(const Vector3& vec, const Matrix4& mat) {
			Vector3 res;

			res.x = mat.m[0] * vec.x + mat.m[1] * vec.y + mat.m[2] * vec.z + mat.m[3];
			res.y = mat.m[4] * vec.x + mat.m[5] * vec.y + mat.m[6] * vec.z + mat.m[7];
			res.z = mat.m[8] * vec.x + mat.m[9] * vec.y + mat.m[10] * vec.z + mat.m[11];
			//w = mat.m[12] * vec.x + mat.m[13] * vec.y + mat.m[14] * vec.z + mat.m[15];

			return res;
		}
		Vector4 operator*(const Vector4& vec) const {
			Vector4 v;

			v.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3];
			v.y = m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7];
			v.z = m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11];
			v.w = m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15];

			return v;
		}
		friend Vector4 operator*(const Vector4& vec, const Matrix4& mat) {
			Vector4 v;

			v.x = mat.m[0] * vec.x + mat.m[1] * vec.y + mat.m[2] * vec.z + mat.m[3];
			v.y = mat.m[4] * vec.x + mat.m[5] * vec.y + mat.m[6] * vec.z + mat.m[7];
			v.z = mat.m[8] * vec.x + mat.m[9] * vec.y + mat.m[10] * vec.z + mat.m[11];
			v.w = mat.m[12] * vec.x + mat.m[13] * vec.y + mat.m[14] * vec.z + mat.m[15];

			return v;
		}

		const float& operator[](const unsigned int& index) const {
			return m[index];
		}
		float& operator[](const unsigned int& index) {
			return m[index];
		}

		/// member functions
		Matrix4 Transpose() const {
			return Matrix4(
				m[0], m[4], m[8], m[12],
				m[1], m[5], m[9], m[13],
				m[2], m[6], m[10], m[14],
				m[3], m[7], m[11], m[15]
			);
		}
		float Determinant() const {
			// calculates and returns the determinant
			return m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13]))
				- m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12]))
				+ m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9] * m[12]))
				- m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9] * m[12]));
		}
		Matrix4 Inverse() const {
			Matrix4 m0;

			// calculate adjugate

			m0.m[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15]
				+ m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
			m0.m[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15]
				- m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
			m0.m[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15]
				+ m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
			m0.m[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11]
				- m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
			m0.m[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15]
				- m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
			m0.m[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15]
				+ m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
			m0.m[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15]
				- m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
			m0.m[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11]
				+ m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
			m0.m[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15]
				+ m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
			m0.m[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15]
				- m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
			m0.m[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11]
				- m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
			m0.m[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15]
				+ m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
			m0.m[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14]
				- m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
			m0.m[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14]
				+ m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
			m0.m[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14]
				- m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
			m0.m[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10]
				+ m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

			// not gonna explain what happened there

			// calculate determinant
			float det = m[0] * m0.m[0] + m[1] * m0.m[4] + m[2] * m0.m[8] + m[3] * m0.m[12];

			#if _DEBUG
			if (det == 0.0f) throw "determinant was 0";
			#endif

			// calculate cofactors and load values back into the matrix
			det = 1 / det;
			m0.m[0] *= det;
			m0.m[1] *= det;
			m0.m[2] *= det;
			m0.m[3] *= det;
			m0.m[4] *= det;
			m0.m[5] *= det;
			m0.m[6] *= det;
			m0.m[7] *= det;
			m0.m[8] *= det;
			m0.m[9] *= det;
			m0.m[10] *= det;
			m0.m[11] *= det;
			m0.m[12] *= det;
			m0.m[13] *= det;
			m0.m[14] *= det;
			m0.m[15] *= det;

			return m0;
		}

		/// static member functions
		static Matrix4 Identity() {
			return Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static Matrix4 Scale(const float& x, const float& y, const float& z) {
			return Matrix4(
				x, 0.0f, 0.0f, 0.0f,
				0.0f, y, 0.0f, 0.0f,
				0.0f, 0.0f, z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static Matrix4 RotateX(const float& angle) {
			return Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, Cos(angle), -Sin(angle), 0.0f,
				0.0f, Sin(angle), Cos(angle), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static Matrix4 RotateY(const float& angle) {
			return Matrix4(
				Cos(angle), 0.0f, Sin(angle), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-Sin(angle), 0.0f, Cos(angle), 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static Matrix4 RotateZ(const float& angle) {
			return Matrix4(
				Cos(angle), -Sin(angle), 0.0f, 0.0f,
				Sin(angle), Cos(angle), 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static Matrix4 Translate(const float& x, const float& y, const float& z) {
			return Matrix4(
				1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}
		static Matrix4 Translate(const Vector3& vec) {
			return Matrix4(
				1.0f, 0.0f, 0.0f, vec.x,
				0.0f, 1.0f, 0.0f, vec.y,
				0.0f, 0.0f, 1.0f, vec.z,
				0.0f, 0.0f, 0.0f, 1.0f
			);
		}

	};
}

#endif // !MATH_MATRIX_HPP