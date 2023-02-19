#pragma once
#include "Matrix.h"
#include "Point.h"

#include "App/AppSettings.h"

namespace Math {
	/*inline float DotProduct(const Point& a, const Point& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}*/

	inline float ToRadians(float degrees) {
		return degrees * PI / 180;
	}
}