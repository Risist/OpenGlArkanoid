#pragma once
#include "GameObjectTriangle.h"

class Walls : public GameObjectTriangle
{
public:
	void Init() override;
	void FixedStep() override;
	void OnPause() override;

private:
	Math::Transform wallTransforms[4];
	Physics::AABBCollider collider;
	Physics::AABBCollider collider2;
};

