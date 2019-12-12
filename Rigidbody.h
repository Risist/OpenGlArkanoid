#pragma once
#include "Math.h"
#include <glm/vec2.hpp>

namespace Physics
{
	class Rigidbody
	{
	public:
		void Step()
		{
			position += velocity;
			velocity *= dragFactor;
		}

		void AddImpulse(glm::vec2 impulse)
		{
			velocity = velocity + impulse * inverseMass;
		}

		float dragFactor = 0.1f;
		float inverseMass = 1.0f;
		glm::vec2 position = {0,0};
		glm::vec2 velocity = {0,0};
	};
}