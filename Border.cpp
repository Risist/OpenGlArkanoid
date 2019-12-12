#include "Border.h"
#include "Bricks.h"

void Border::Init()
{
	float l = 1.0f;
	float r = 2.f;
	const float sqrt2 = 1.41421356;
	const float sqrt3 = 1.73205080757;

	glm::vec2 v1 = { 0.0f,    -sqrt3 * 0.5f * l };
	glm::vec2 v2 = { 0.5f * r,   0 };
	glm::vec2 v3 = { -0.5f * r,   0 };
	glm::vec2 middle = (v1 + v2 + v3) / 3.0f;

	v1 -= middle;
	v2 -= middle;
	v3 -= middle;

	Rendering::Vertex v[] = {
		{ -v1,  glm::vec3{ 0.15f, 0.9f, 0.0f }*0.5f  },
		{ -v2,  glm::vec3{ 0.15f, 0.9f, 0.0f }*0.0f },
		{ -v3,  glm::vec3{ 0.2f,  0.95f,0.15f}*0.0f },
	};
	InitModel(v, 1);
	transform.scale = 0.35f;
	transform.rotation = Math::Degree(180+45);
}

void Border::FixedStep()
{
	float timeRate = 0.5f*Bricks::GetPoints();
	float cosTime = glm::cos(world->GetCurrentTime().asSeconds() * timeRate);
	cosTime *= cosTime; 
	cosTime *= cosTime;
	float pos = 1.05f - cosTime * 0.025f;

	{
		transform.position = { pos, pos };
		transform.rotation = Math::Degree(180 + 45);
		renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
		renderer.Display();
	}
	{
		transform.position = { -pos, pos };
		transform.rotation = Math::Degree(180 - 45);
		renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
		renderer.Display();
	}
	{
		transform.position = { -pos, -pos };
		transform.rotation = Math::Degree(180 - 135);
		renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
		renderer.Display();
	}
	{
		transform.position = { pos, -pos };
		transform.rotation = Math::Degree(180 - 225);
		renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
		renderer.Display();
	}
}

void Border::OnPause()
{
	Border::FixedStep();
}
