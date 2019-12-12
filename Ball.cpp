#include "Ball.h"
#include "Bricks.h"

void Ball::Init()
{
	InitModel();
	InitPhysics();

	transform.scale *= 0.125f;
}

void Ball::FixedStep()
{
	Game::Renderable::FixedStep();
	if (!Bricks::Won())
	{
		float yPosFactor = (1 + rigidbody.position.y) * 0.5f;
		transform.rotation += Math::Degree(10.0f* yPosFactor + 4.0f);
		static const float stepLength = 0.0005f;
		world->solver.ResolveCollisions({ &transform, &collider, &rigidbody }, stepLength, 2.5f);
	
		rigidbody.Step();
		transform.position = rigidbody.position;
	}
	else
	{
		transform.rotation += Math::Degree(17.5f);
	}
}

void Ball::InitPhysics()
{
	rigidbody.inverseMass = 1.0f;
	rigidbody.dragFactor = 1.0f;
	rigidbody.position = { 0,0.8 };
	rigidbody.velocity = { 0.0f, -0.025f };
}

void Ball::InitModel()
{
	renderer.Init();

	renderer.material.InitProgramFromFile("BasicShader.vert", "BasicShader.frag");

	struct Vertex
	{
		float x;
		float y;

		float r;
		float g;
		float b; 
	};

	float l = 1.0f;
	const float sqrt2 = 1.41421356;
	const float sqrt3 = 1.73205080757;

	glm::vec2 v1 = { 0.0f,    sqrt3 * 0.25f * l };
	glm::vec2 v2 = { 0.5f*l, -sqrt3 * 0.25f * l };
	glm::vec2 v3 = {-0.5f*l, -sqrt3 * 0.25f * l };
	glm::vec2 middle = (v1 + v2 + v3) / 3.0f;


	v1 -= middle;
	v2 -= middle;
	v3 -= middle;


	collider.halfExtends = { 0.5f * l, sqrt3 * 0.25f * l };


	Vertex v[] = {
		{ v1.x, v1.y,   0.85f, 0.35f, 0.25f},
		{ v2.x, v2.y,   0.75f, 0.45f, 0.25f},
		{ v3.x, v3.y,   0.65f, 0.35f, 0.5f}
	};
	renderer.GenerateVertexBuffer(v, 3);

	renderer.material.Bind();
	renderer.layout.AddLayoutElemFloat("position", 2);
	renderer.layout.AddLayoutElemFloat("color", 3);
	renderer.ApplyLayout();
}
