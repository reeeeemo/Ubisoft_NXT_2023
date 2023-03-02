#pragma once
#include "Point.h"

#include "App/AppSettings.h"
#include "Point.h"

namespace Math {
	inline float DotProduct(const CPoint& a, const CPoint& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline float ToRadians(float degrees) {
		return degrees * PI / 180;
	}
}