#pragma once

#include "Timer.h"
#include <glm/vec2.hpp>
#include <SFML/Window.hpp>

namespace Utility
{
	/// returns mouse position in ogl coordinates
	inline glm::vec2 GetMousePosition(const sf::Window& wnd)
	{
		glm::vec2 position = {
				sf::Mouse::getPosition(wnd).x / (float)wnd.getSize().x,
				sf::Mouse::getPosition(wnd).y / (float)wnd.getSize().y
		};

		position = position*2.0f - glm::vec2{ 1,1 };
		position = { position.x, -position.y };
		return position;
	}
}