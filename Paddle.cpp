#include "Paddle.h"

void Paddle::Init()
{
	world->solver.AddSurface({ &transform, &collider, {0,1} });

	float l = 0.75f;
	float r = 3.0f;
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
		{ v1,  { 0.9f, 0.15f, 0.0f} },
		{ v2,  { 0.9f, 0.15f, 0.0f} },
		{ v3,  { 0.95f, 0.2f, 0.15f} },
	};
	InitModel(v, 1);

	transform.scale *= 0.125f;
	transform.position = { 0.0f,-0.9f };

	collider.halfExtends = { r*0.5f,sqrt3 * 0.125f * l };
}

void Paddle::FixedStep()
{
	Game::Renderable::FixedStep();
	static const float movementSpeed = 0.02f;
	static const float clampValue = 0.85f;
	static const float rotationAmount = 17.50f;
	static const float lerpFactor = 0.75f;
	float rotation = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		transform.position.x = glm::clamp(transform.position.x - movementSpeed, -clampValue, clampValue);
		rotation += rotationAmount;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		transform.position.x = glm::clamp(transform.position.x + movementSpeed, -clampValue, clampValue);
		rotation -= rotationAmount;
	}
	/**
	{
		auto mousePosition = Utility::GetMousePosition(*world->wnd);
		//cout << mousePosition.x << ", " << mousePosition.y << "\n";

		float dot = glm::dot(glm::vec2{ 0,1 }, glm::normalize(Utility::GetMousePosition(*world->wnd) + glm::vec2{ 0,1.05f }));
		Math::Angle angle = Math::Radian(glm::acos(dot));
		if (mousePosition.x < 0)
			angle *= -1.0f;
		angle = Math::Degree(glm::clamp(angle.asDegree(), -rotationAmount, rotationAmount));
		//cout << angle.asDegree() << "\n";
	}/**/

	transform.rotation = Math::Degree(glm::mix(rotation, transform.rotation.asDegree(), lerpFactor));
}
