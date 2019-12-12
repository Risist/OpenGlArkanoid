#include "Walls.h"

void Walls::Init()
{
	wallTransforms[0].position = { 0,1 };
	wallTransforms[0].rotation = Math::Degree(180);
	
	wallTransforms[1].position = { 0,-1 };
	wallTransforms[1].rotation = Math::Degree(0);
	
	wallTransforms[2].position = glm::normalize(glm::vec2{ -1,0.25 });
	wallTransforms[2].rotation = Math::Degree(90);
	
	wallTransforms[3].position = glm::normalize(glm::vec2{  1,0.25 });
	wallTransforms[3].rotation = Math::Degree(-90);
	
	collider.halfExtends = { 1, 0.05f };
	collider2.halfExtends = { 0.05f, 1};

	world->solver.AddSurface({ &wallTransforms[0], &collider, {0,1} });
	//world->solver.AddSurface({ &wallTransforms[1], &collider, {0,1} });
	world->solver.AddSurface({ &wallTransforms[2], &collider2, {0,1} });
	world->solver.AddSurface({ &wallTransforms[3], &collider2, {0,1} });



	float l = 1.0f;
	float r = 3.0f;
	const float sqrt3 = 1.73205080757;

	glm::vec2 v1 = { 0.0f,    -sqrt3 * 0.5f * l };
	glm::vec2 v2 = { 0.5f * r,   0 };
	glm::vec2 v3 = { -0.5f * r,   0 };
	glm::vec2 middle = (v1 + v2 + v3) / 3.0f;

	v1 -= middle;
	v2 -= middle;
	v3 -= middle;

	Rendering::Vertex v[] = {
		{ v1,  { 0.25f, 0.5f, 0.15f} },
		{ v2,  { 0.35f, 0.5f, 0.1f} },
		{ v3,  { 0.25f, 0.3f, 0.5f} },
	};
	InitModel(v, 1);
}

void Walls::FixedStep()
{
	for (int i = 0; i < 4; ++i)
		if(i != 1)
	{
		Math::Transform tr = wallTransforms[i];
		tr.scale *= 0.9f;
		tr.position *= 1.25f;
		tr.position.y += -0.05f;
		renderer.material.SetUniformMat3fv("mvp", tr.GetMatrix());
		renderer.Display();
	}
}

void Walls::OnPause()
{
	FixedStep();
}
