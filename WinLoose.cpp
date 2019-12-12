#include "WinLoose.h"
#include "Bricks.h"
#include "Ball.h"

void WinLoose::Init()
{
	float l = 0.75f;
	float r = 2.0f;
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
		{ v1,  glm::vec3{ 0.9f, 0.15f, 0.0f}*0.25f },
		{ v2,  glm::vec3{ 0.9f, 0.15f, 0.0f} },
		{ v3,  glm::vec3{ 0.95f, 0.2f, 0.15f} },

		{ -v1,  glm::vec3{ 0.15f, 0.9f, 0.0f }*1.0f  },
		{ -v2,  glm::vec3{ 0.15f, 0.9f, 0.0f }*0.25f },
		{ -v3,  glm::vec3{ 0.2f,  0.95f,0.15f}*0.25f },
	};
	InitModel(v, 2);
	transform.scale *= 0.75;

}

void WinLoose::FixedStep()
{
	if (Bricks::Won() || ball->Loose())
	{
		static const float winOffset = 0.5f;
		bool won = Bricks::Won();
		transform.position = { 0, glm::sin(world->GetCurrentTime().asSeconds() * 10) * 0.1f - winOffset + 2 * winOffset * won };

		renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
		renderer.Display(3 * won, 3);
	}
}

void WinLoose::OnPause()
{
	WinLoose::FixedStep();
}
