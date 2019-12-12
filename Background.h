#pragma once
#include "Game.h"
#include "Rendering.h"

class Background : public Game::GameObject
{
public:
	virtual void Init() override;
	virtual void FixedStep() override;
	virtual void OnPause() override;

private:
	void InitModel(Rendering::Vertex* v, unsigned int nV);

	Math::Transform transform;
	Rendering::RenderObject< Rendering::EDrawMode::EStaticDraw, Rendering::EPrimitiveType::ELines> renderer;
};

