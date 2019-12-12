#pragma once
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Rendering.h"
#include <SFML/Window.hpp>
#include "Transform.h"

namespace Game
{
	class Renderable : public GameObject
	{
	public:
		virtual void Init() override{}
		virtual void FixedStep() override {
			renderer.material.SetUniformMat3fv("mvp", transform.GetMatrix());
			renderer.Display();
		}
		virtual void OnPause() override
		{
			Game::Renderable::FixedStep();
		}

	protected:
		Math::Transform transform;
		Rendering::RenderObject<> renderer;
	};
}

