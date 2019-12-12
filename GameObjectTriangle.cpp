#include "GameObjectTriangle.h"

void GameObjectTriangle::InitModel(Rendering::Vertex* v, unsigned int nV)
{
	renderer.Init();
	renderer.material.InitProgramFromFile("BasicShader.vert", "BasicShader.frag");

	renderer.GenerateVertexBuffer(v, nV*3);

	renderer.material.Bind();
	renderer.layout.AddLayoutElemFloat("position", 2);
	renderer.layout.AddLayoutElemFloat("color", 3);
	renderer.ApplyLayout();
}
