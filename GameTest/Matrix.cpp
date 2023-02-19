#include "stdafx.h"
#include "Matrix.h"


Matrix4::Matrix4(float fov, float aspectRatio, float zNear, float zFar) 
{
	matrix[0][0] = aspectRatio * (1 / tan(fov / 2)); // For X calculation.
	matrix[1][1] = (1 / tan(fov / 2)); // For Y calculation.
	matrix[2][2] = zFar / (zFar - zNear); // For Z calculation (distance from zFar).
	matrix[2][3] = -(zFar / (zFar - zNear)); // For Z calculation (offset of zNear).
	matrix[3][2] = 1; // For W calulation (shearing, persective divide, etc.).
}


Matrix4::Matrix4() 
{
	matrix = { { 0 } };
}