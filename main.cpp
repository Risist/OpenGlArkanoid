#include <SFML/Window.hpp>

#include "Rendering.h"
#include "Game.h"


#include "Ball.h"
#include "Paddle.h"
#include "Bricks.h"
#include "Walls.h"
#include "Background.h"
#include "Pause.h"
#include "WinLoose.h"
#include "Border.h"

int main()
{
	srand(time(nullptr)* time(nullptr));

	sf::Window window;
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	window.create(sf::VideoMode(800, 800), "OpenGL", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
	}

	Game::World world;
	world.stepTime = sf::seconds(0.01f);
	world.wnd = &window;

	auto winLoose = new WinLoose();
	auto ball = new Ball();
	winLoose->ball = ball;

	world.AddObject(new Background());
	world.AddObject(new Paddle());
	world.AddObject(new Bricks());
	world.AddObject(ball); 
	world.AddObject(new Walls());
	world.AddObject(new Border());
	world.AddObject(new Pause());
	world.AddObject(winLoose);

	


	bool running = true;
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);

		world.Update();

		window.display();
	}
}