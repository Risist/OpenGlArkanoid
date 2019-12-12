#include "Collision.h"

namespace Physics
{
	glm::vec2 CollisionSurface::GetReflectionVector(glm::vec2 incidence, float random) const
	{
		float r = Math::randRange(-random, random);
		Math::Angle angle = Math::Degree(r) - transform->rotation;
		glm::vec2 n = {
			normal.x * angle.cos() - normal.y * angle.sin(),
			normal.x * angle.sin() + normal.y * angle.cos()
		};

		return incidence - (2 * glm::dot(n, incidence)) * n;
	}
	bool CollisionSurface::ResolveCollision(const CollisionEntity& entity, float stepLength, float randomAngle) const
	{
		auto entityColl = entity.GetTransformedCollider();
		auto surfaceColl = GetTransformedCollider();

		glm::vec2 velocityNormalised = entity.rigidbody->velocity;
		if (velocityNormalised == glm::vec2{ 0, 0 })
			return false;
		velocityNormalised = glm::normalize(velocityNormalised);

		auto offset = entityColl.GetResolveCollision(surfaceColl, -velocityNormalised * stepLength);
		if (offset == glm::vec2{ 0, 0 })
			return false;

		glm::vec2 velocity = entity.rigidbody->velocity;
		float velocityLength = glm::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		entity.rigidbody->position += offset;
		entity.rigidbody->velocity = GetReflectionVector(velocityNormalised, randomAngle) * velocityLength;

		collisionCallback();
		return true;
	}


}