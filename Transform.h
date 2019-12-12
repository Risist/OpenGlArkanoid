#pragma once
#include "Math.h"

namespace Math
{
	class Transform
	{
	public:
		Transform(glm::vec2 position = {0,0}, Math::Angle rotation = Math::Angle(), float scale = 1.0f)
			:position(position), rotation(rotation), scale(scale)
		{
		}

		glm::mat3 GetMatrix() const
		{
			glm::mat3 matrix{
				scale,		0.0f,		0.0f,
				0.0f,		scale,		0.0f,
				0.0f,       0.0f,       1.0f,
			};
			glm::mat3 matrixR {
				rotation.cos(), -rotation.sin(),	0.0f,
				rotation.sin(),  rotation.cos(),	0.0f,
				0.0f,            0.0f,              1.0f,
			};

			
			matrix = matrix * matrixR;

			matrix[2][0] += position.x;
			matrix[2][1] += position.y;

			if (parent != nullptr) 
				return parent->GetMatrix() * matrix;
			else
				return matrix;
		}

		glm::vec2 TransformDirection(glm::vec2 v) const
		{
			return GetMatrix() * glm::vec3({v.x, v.y, 0.0f});
		}
		glm::vec2 TransformPosition(glm::vec2 v) const
		{
			return GetMatrix() * glm::vec3({ v.x, v.y, 1.0f });
		}

	public:
		glm::vec2 position;
		float scale = 1.0f;
		Math::Angle rotation;
		Transform* parent = nullptr;
	};
}