#pragma once
#include "GameObjectTriangle.h"

class Bricks : public GameObjectTriangle
{
public:
	void Init() override;
	void FixedStep() override;
	void OnPause() override;
	
	static bool Won();
	static int GetPoints() {
		return points;
	}
private:
	vector<Math::Transform> transforms;
	vector<bool> active;
	Physics::AABBCollider collider;

	void AddBrick(glm::vec2 position);

	static int points;
};

