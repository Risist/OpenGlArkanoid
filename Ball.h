#pragma once
#include "Rendering.h"
#include "Physics.h"
#include "GameObject.h"

class Ball : public Game::Renderable
{
public:
	void Init() override;
	void FixedStep() override;

	inline bool Loose()
	{
		return transform.position.y < -1.f;
	}
private:
	Physics::Rigidbody rigidbody;
	Physics::AABBCollider collider;
	void InitPhysics();
	void InitModel();

};

