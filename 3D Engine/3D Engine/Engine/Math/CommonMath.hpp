#ifndef MATH_COMMON_MATH_HPP
#define MATH_COMMON_MATH_HPP
// never use these ones since I defined floating point defines below
#undef _USE_MATH_DEFINES
#include <math.h>

#define REALLY_SMALL 0.0000000000000001f
#define M_E 2.71828182845904523536f			// e
#define M_LOG2E 1.44269504088896340736f		// log2(e)
#define M_LOG10E 0.434294481903251827651f	// log10(e)
#define M_LN2 0.693147180559945309417f		// ln(2)
#define M_LN10 2.30258509299404568402f		// ln(10)
#define M_PI 3.14159265358979323846f		// pi
#define M_PI_2 1.57079632679489661923f		// pi/2
#define M_PI_4 0.785398163397448309616f		// pi/4
#define M_1_PI 0.318309886183790671538f		// 1/pi
#define M_2_PI 0.636619772367581343076f		// 2/pi
#define M_2_SQRTPI 1.12837916709551257390f  // 2/sqrt(pi)
#define M_SQRT2 1.41421356237309504880f		// sqrt(2)
#define M_SQRT1_2 0.707106781186547524401f  // 1/sqrt(2)
#define DEG_TO_RAD(val) (val * M_PI / 180.0f)
#define RAD_TO_DEG(val) (val * 180.0f / M_PI);

namespace Math {

	static float Sin(const float& deg) {
		return sinf(DEG_TO_RAD(deg));
	}
	static float Cos(const float& deg) {
		return cosf(DEG_TO_RAD(deg));
	}
	static float Tan(const float& deg) {
		return tanf(DEG_TO_RAD(deg));
	}
	static float Sec(const float& deg) {
		return 1.0f / cosf(DEG_TO_RAD(deg));
	}
	static float Csc(const float& deg) {
		return 1.0f / sinf(DEG_TO_RAD(deg));
	}
	static float Cot(const float& deg) {
		return 1.0f / tanf(DEG_TO_RAD(deg));
	}


	static float Clamp(float f, const float& min, const float& max) {
		return (max > min ? (f < max ? (f > min ? f : min) : max) : f);
	}
	static float Lerp(const float& a, const float& b, const float& t) {
		return (b - a) * t + a;
	}
	static bool NearlyZero(const float& value, const float& percision) {
		return fabs(value) < percision;
	}
	static bool NearlyEqual(const float& a, const float& b, const float& percision) {
		return fabs(b - a) < percision;
	}

}

#endif // !MATH_COMMON_MATH_HPP