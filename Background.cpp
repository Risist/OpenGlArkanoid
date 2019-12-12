#include "Background.h"

void Background::Init()
{
	static const int sizeX = 19;
	static const int sizeY = 19;
	glm::vec3 color{ 0.25f, 0.35f, 0.8f };
	color *= 0.25f;

	Rendering::Vertex v[sizeY][10*sizeX];

	transform.scale *= 0.05;
	for (int i = 0; i < sizeY; ++i)
	{
		for (int j = 0; j < sizeX; ++j)
		{
			glm::vec2 offset{ 
				2 * j - sizeX + 1, 
				2 * i - sizeY + 1 };
			v[i][10 * j]     = { offset + glm::vec2{ -1,-1 }, color };
			v[i][10 * j + 1] = { offset + glm::vec2{  1, 1 }, color };

			v[i][10 * j + 2] = { offset + glm::vec2{ -1, 1 }, color };
			v[i][10 * j + 3] = { offset + glm::vec2{  1, 1 }, color };

			v[i][10 * j + 4] = { offset + glm::vec2{ -1,-1 }, color };
			v[i][10 * j + 5] = { offset + glm::vec2{  1,-1 }, color };

			v[i][10 * j + 6] = { offset + glm::vec2{ -1,-1 }, color };
			v[i][10 * j + 7] = { offset + glm::vec2{ -1, 1 }, color };

			v[i][10 * j + 8] = { offset + glm::vec2{  1,-1 }, color };
			v[i][10 * j + 9] = { offset + glm::vec2{  1, 1 }, color };
		}
	}
	InitModel((Rendering::Vertex*)v, sizeof(v)/sizeof(Rendering::Vertex)/2);
}

void Background::FixedStep()
{
	renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
	renderer.Display();
}

void Background::OnPause()
{
	renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
	renderer.Display();
}

void Background::InitModel(Rendering::Vertex* v, unsigned int nV)
{
	renderer.Init();
	renderer.material.InitProgramFromFile("BasicShader.vert", "BasicShader.frag");

	renderer.GenerateVertexBuffer(v, nV * 2);

	renderer.material.Bind();
	renderer.layout.AddLayoutElemFloat("position", 2);
	renderer.layout.AddLayoutElemFloat("color", 3);
	renderer.ApplyLayout();
}
