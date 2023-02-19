#pragma once
#include <array>

struct Matrix4
{
	Matrix4(float fov, float aspectRatio, float zNear, float zFar); // For Projection Matrix
	Matrix4(); // Default constructor


	union {
		struct { std::array<std::array<float, 4>, 4> matrix; }; // 4 arrays of an array that has 4 floats in it.
	};
};
