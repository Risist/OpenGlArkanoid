#pragma once

#include "Angle.h"

#include <glm/vec3.hpp>
#include <glm/vector_relational.hpp>
#include <glm/trigonometric.hpp>
#include <glm/mat3x3.hpp>

namespace Math
{
	inline float randRange(float min, float max)
	{
		return (float)rand() / RAND_MAX * (max - min) + min;
	}

	inline double triangleArea(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
	{
		double a = glm::length(v1 - v2);
		double b = glm::length(v2 - v3);
		double c = glm::length(v1 - v3);
		double x = (a + b + c) * 0.5f;

		return sqrt(x * (x - a) * (x - b) * (x - c));
	}
	inline bool insideTriangle(glm::vec2 d, glm::vec2 a, glm::vec2 b, glm::vec2 c)
	{
		double A = triangleArea(a, b, c);
		double A1 = triangleArea(a, b, d);
		double A2 = triangleArea(a, c, d);
		double A3 = triangleArea(b, c, d);

		return abs(A - (A1 + A2 + A3)) < ((double)numeric_limits<float>::epsilon()) * 2;
	}

	inline bool lineIntersection(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2)
	{
		float x1 = a1.x;
		float x2 = a2.x;
		float x3 = b1.x;
		float x4 = b2.x;

		float y1 = a1.y;
		float y2 = a2.y;
		float y3 = b1.y;
		float y4 = b2.y;

		float denominator = ((x2 - x1) * (y4 - y3)) - ((y2 - y1) * (x4 - x3));
		float numerator1 = ((y1 - y3) * (x4 - x3)) - ((x1 - x3) * (y4 - y3));
		float numerator2 = ((y1 - y3) * (x2 - x1)) - ((x1 - x3) * (y2 - y1));

		if (denominator == 0) return numerator1 == 0 && numerator2 == 0;

		float r = numerator1 / denominator;
		float s = numerator2 / denominator;

		return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
	}
}