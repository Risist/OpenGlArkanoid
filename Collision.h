#pragma once
#include "Colliders.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <functional>

namespace Physics
{
	
	template<typename ColliderTy>
	struct CollisionReference
	{
		Math::Transform* transform;
		ColliderTy* collider;
		std::function<void()> collisionCallback = [](){};
		ColliderTy GetTransformedCollider() const
		{
			return collider->GetTransformed(*transform);
		}
	};

	class Rigidbody;
	struct CollisionEntity : public CollisionReference<AABBCollider>
	{
		CollisionEntity() = default;
		CollisionEntity(Math::Transform* transform, AABBCollider* collider, Rigidbody* rigidbody)
			: rigidbody(rigidbody)
		{
			this->transform = transform;
			this->collider = collider;
		}
		Rigidbody* rigidbody;
	};

	struct CollisionSurface : public CollisionReference<AABBCollider>
	{
		CollisionSurface() = default;
		CollisionSurface(Math::Transform* transform, AABBCollider* collider, glm::vec2 normal)
			: normal(normal)
		{
			this->transform = transform;
			this->collider = collider;
		}
		glm::vec2 normal;
		glm::vec2 GetReflectionVector(glm::vec2 incidence, float random = 0.0f) const;
		bool ResolveCollision(const CollisionEntity& entity, float stepLength, float randomAngle = 0.0f) const;
	};

	class CollisionSurfaceSolver
	{
	public:

		void AddSurface(const CollisionSurface& s)
		{
			surfaces.push_back(s);
		}
		void AddTrigger(const CollisionReference<AABBCollider>& s)
		{
			triggers.push_back(s);
		}
		void ResolveCollisions(const CollisionEntity& entity, float stepLength, float randomAngle = 0.0f)
		{
			for (auto& it : triggers)
				if (it.GetTransformedCollider().IsOnCollision(entity.GetTransformedCollider()))
					it.collisionCallback();

			for (auto& it : surfaces)
				if (it.ResolveCollision(entity, stepLength, randomAngle))
					return;
		}

		std::vector<CollisionReference<AABBCollider>> triggers;
		std::vector<CollisionSurface> surfaces;
	};
}