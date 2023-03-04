#pragma once
#include "Point.h"

#include "App/AppSettings.h"
#include "Point.h"
#include <cmath>

namespace Math {
	inline float DotProduct(const CPoint& a, const CPoint& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline float ToRadians(float degrees) {
		return degrees * PI / 180;
	}

	inline CPoint AbsValue(CPoint p1)
	{
		const CPoint abs_point = CPoint(abs(p1.x), abs(p1.y), abs(p1.z), 1.0f);
		return abs_point;
	}

	inline double AbsValue(double value)
	{
		return abs(value);
	}

	inline float GetLength(const CPoint& a) {
		return a.x * a.x + a.y * a.y;
	}

	inline CPoint Normalize(const CPoint& a) {
		return a * (1 / std::sqrt(GetLength(a)));
	}

}