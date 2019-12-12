#include "Bricks.h"

int Bricks::points = 0;

void Bricks::Init()
{
	float l = 1.0f;
	float r = 1.0f;
	const float sqrt3 = 1.73205080757;

	glm::vec2 v1 = { 0.0f,	   -sqrt3*0.5f*l };
	glm::vec2 v2 = { 0.5f*r,    0 };
	glm::vec2 v3 = {-0.5f*r,    0 };
	glm::vec2 middle = (v1 + v2 + v3) / 3.0f;

	v1 -= middle;
	v2 -= middle;
	v3 -= middle;


	Rendering::Vertex v[] = {

		{ v1,   {0.15f, 0.15f, 0.5f} },
		{ v2,   {0.15f, 0.25f, 0.3f} },
		{ v3,   {0.2f, 0.4f, 0.6f} },

		{ -v1,   {0.15f, 0.15f, 0.5f} },
		{ -v2,   {0.15f, 0.25f, 0.3f} },
		{ -v3,   {0.2f, 0.4f, 0.6f} },

	};
	InitModel(v, 2);

	transform.scale *= 0.1f;
	transform.position = { 0,0.8 };

	
	static const float spacing = 1.1f;
	transforms.reserve(3 + 9 * 3 * 2*2);
	for (int j = 0; j < 3; ++j)
	{
		AddBrick(glm::vec2{ 0, -j }*spacing);
		for (int i = 1; i < 9; ++i)
		{
			AddBrick(glm::vec2{ i, -j }*spacing);
			AddBrick(glm::vec2{-i, -j }*spacing);
		}
	}
}

void Bricks::FixedStep()
{
	for (int i = 0; i < active.size(); ++i)
	{
		if (!active[i])
		{
			transforms[i].position += glm::vec2{ 0, -0.15f };

			transforms[i].rotation += Math::Degree(10.0f);
		}
		renderer.material.SetUniformMat3fv("mvp", transforms[i].GetMatrix());
		renderer.Display();
	}
}

void Bricks::OnPause()
{
	for (int i = 0; i < active.size(); ++i)
	{
		renderer.material.SetUniformMat3fv("mvp", transforms[i].GetMatrix());
		renderer.Display();
	}
}

bool Bricks::Won()
{
	return points >= 51;
}

void Bricks::AddBrick(glm::vec2 position)
{
	transforms.push_back(Math::Transform(position));
	transforms.back().parent = &transform;
	active.push_back(true);
	int id = active.size()-1;
	world->solver.AddTrigger({ &transforms.data()[id], &collider, [&,id]() {
			if (active[id])
			{
				points++;
				cout << "points: " << points << endl;
			}
			active[id] = false;
		}});

}
