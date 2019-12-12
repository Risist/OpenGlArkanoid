#pragma once
#include "Rendering.h"
#include "Physics.h"
#include "GameObjectTriangle.h"

class Paddle : public GameObjectTriangle
{
public:
	virtual void Init() override;
	virtual void FixedStep() override;

private:
	Physics::AABBCollider collider;
};

