#pragma once
#include "CoreInclude.h"
#include "Rigidbody.h"
#include "Transform.h"

namespace Physics
{
	/// Base Collision Shapes
	/// connisions are required to implement:
	///		ColliderTy GetTransformed(const Math::Transform& transform) const
	///				Transforms collider relative to given transform
	///
	///		bool IsOnCollision(const ColliderTy& other) const
	///				Checks for collision with other collider of the smame type
	///				@positionOffset allows to move collider a little bit to check collisions in different place
	///
	///		glm::vec2 GetResolveCollision(const ColliderTy& other, glm::vec2 stepLength)
	///				returns offsetToPosition that allows to leave collision

	class CircleCollider
	{
	public:

		bool IsOnCollision(const CircleCollider& other, glm::vec2 positionOffset = {0,0}) const
		{
			glm::vec2 diff = (other.center - center - positionOffset);
			return diff.length() <= radius + other.radius;
		}

		CircleCollider GetTransformed(const Math::Transform& transform) const
		{
			return { transform.TransformPosition(center), radius * transform.scale };
		}

		glm::vec2 GetResolveCollision(const CircleCollider& other, glm::vec2 stepLength)
		{
			static const unsigned int nStep = 50;
			unsigned int i = 0;
			for (; i < nStep; ++i)
			{
				if (!IsOnCollision(other, stepLength * (float)i))
					break;
			}
			return stepLength * (float)i;
		}

		glm::vec2 center;
		float radius;
	};
	class AABBCollider
	{
	public:

		bool IsOnCollision(const AABBCollider& other, glm::vec2 positionOffset = {0,0}) const
		{
			auto min = GetMin() + positionOffset;
			auto max = GetMax() + positionOffset;
			auto otherMin = other.GetMin();
			auto otherMax = other.GetMax();

			return
				min.x <= otherMax.x && max.x >= otherMin.x &&
				min.y <= otherMax.y && max.y >= otherMin.y;
		}

		AABBCollider GetTransformed(const Math::Transform& transform)const
		{
			return { transform.TransformPosition(center), halfExtends * transform.scale };
		}
		glm::vec2 GetResolveCollision(const AABBCollider& other, glm::vec2 stepLength)
		{
			static const unsigned int nStep = 500;
			unsigned int i = 0;
			for (; i < nStep; ++i)
			{
				if (!IsOnCollision(other, stepLength * (float)i))
					break;
			}
			return stepLength * (float)i;
		}


		glm::vec2 GetMin() const
		{
			return center - halfExtends;
		}
		glm::vec2 GetMax() const
		{
			return center + halfExtends;
		}
		glm::vec2 center;
		glm::vec2 halfExtends;
	};
}