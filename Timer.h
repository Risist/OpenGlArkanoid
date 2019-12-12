#pragma once
#include <SFML/System.hpp>

namespace Utility
{
	class Timer
	{
	public:
		Timer(sf::Time cd) : cd(cd) {}

		inline void Restart()
		{
			clock.restart();
		}
		inline bool isReady()
		{
			return clock.getElapsedTime() > cd;
		}
		inline bool isReadyRestart()
		{
			if (isReady())
			{
				Restart();
				return true;
			}
			return false;
		}

		sf::Time cd;
	private:
		sf::Clock clock;
	};
}