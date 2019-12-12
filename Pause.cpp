#include "Pause.h"

void Pause::Init()
{

	float l = 0.5f;
	float r = 3.0f;
	const float sqrt3 = 1.73205080757;

	glm::vec2 v1 = { 0.0f,    -sqrt3 * 0.5f * l };
	glm::vec2 v2 = { 0.5f * r,   0 };
	glm::vec2 v3 = { -0.5f * r,   0 };
	glm::vec2 middle = (v1 + v2 + v3) / 3.0f;

	v1 -= middle;
	v2 -= middle;
	v3 -= middle;

	glm::vec2 offset(0, 0.3f);
	Rendering::Vertex v[] = {
		{ v1 - offset,  { 0.9f, 0.15f, 0.f} },
		{ v2 - offset,  { 0.9f, 0.15f, 0.f} },
		{ v3 - offset,  { 0.9f, 0.25f, 0.25f} },

		{-v1 + offset,  { 0.9f, 0.15f, 0.f} },
		{-v2 + offset,  { 0.9f, 0.15f, 0.f} },
		{-v3 + offset,  { 0.9f, 0.25f, 0.25f} },
	};
	InitModel(v, 2);

	transform.scale *= 0.25f;
	transform.rotation = Math::Degree(90);
}

void Pause::FixedStep()
{
	if (world->wnd->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!pressed)
		{
			world->PauseGame(true);
			pressed = true;
		}
	}
	else
		pressed = false;
}

void Pause::OnPause()
{
	if (world->wnd->hasFocus() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!pressed)
		{
			world->PauseGame(false);
			pressed = true;
		}
	}
	else
		pressed = false;

	GameObjectTriangle::OnPause();
}
