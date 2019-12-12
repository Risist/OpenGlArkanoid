#pragma once
#include <vector>
#include "Utility.h"
#include "Physics.h"

namespace sf
{
	class Window;
}

namespace Game
{

	class World;

	class GameObject
	{
	public:
		virtual ~GameObject()    {}

		virtual void Init()	     {}
		virtual void FixedStep() {}
		virtual void OnPause()   {}

	protected:
		World* world;
		friend class World;
	};


	class World
	{
	public:
		~World()
		{
			for (auto it : objects)
				delete it;
		}

		void AddObject(GameObject* obj)
		{
			objects.push_back(obj);
			obj->world = this;
			obj->Init();
		}

		void Update()
		{
			if (paused)
			{
				PauseStep();
			}
			else
			{

				timeAccumulator += stepClock.getElapsedTime();
				while (timeAccumulator > stepTime)
				{
					FixedStep();
					timeAccumulator -= stepTime;
				}
				stepClock.restart();
			}
		}


		bool GamePaused() {
			return paused;
		}
		void PauseGame(bool s)
		{
			if(s != paused)
				stepClock.restart();
			paused = s;
		}
		sf::Time GetCurrentTime()
		{
			return timer.getElapsedTime();
		}

		sf::Window* wnd;
		sf::Time stepTime;
		Physics::CollisionSurfaceSolver solver;
	private:
		sf::Clock timer;
		sf::Clock stepClock;
		sf::Time timeAccumulator;
		void FixedStep()
		{
			for (auto it : objects)
				it->FixedStep();
		}
		void PauseStep()
		{
			for (auto it : objects)
				it->OnPause();
		}
		bool paused = false;

		std::vector<GameObject*> objects;
	};
}