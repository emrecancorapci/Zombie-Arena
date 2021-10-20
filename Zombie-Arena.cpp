#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

int main()
{

#pragma region START

	enum class State{ PAUSED, LEVELING_UP, GAME_OVER, PLAYING};

	State state(State::GAME_OVER);

	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(
		VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	View mainView(FloatRect(0,0, resolution.x, resolution.y));

	Clock clock;
	Time gameTimeTotal;

	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	Player player;

	IntRect arena;

#pragma endregion

	while(window.isOpen())
	{

	#pragma region PRE-UPDATE

		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Return)
				{
					if (state == State::PLAYING)
						state = State::PAUSED;

					else if (state == State::PAUSED)
					{
						state = State::PLAYING;
						clock.restart();
					}
					else if (state == State::GAME_OVER)
						state = State::LEVELING_UP;
				}
				if(state == State::PLAYING)
				{
					// ...
				}
			}
		}

		if(Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// WASD
		if (state == State::PLAYING)
		{
			Keyboard::isKeyPressed(Keyboard::W)?
				player.moveUp() : player.stopUp();
			Keyboard::isKeyPressed(Keyboard::S)?
				player.moveDown() : player.stopDown();
			Keyboard::isKeyPressed(Keyboard::A)?
				player.moveLeft() : player.stopLeft();
			Keyboard::isKeyPressed(Keyboard::D)?
				player.moveRight() : player.stopRight();
		}

		// Leveling Up
		if (state==State::LEVELING_UP)
		{
			event.key.code == Keyboard::Num1 ? state = State::PLAYING :
			event.key.code == Keyboard::Num2 ? state = State::PLAYING :
			event.key.code == Keyboard::Num3 ? state = State::PLAYING :
			event.key.code == Keyboard::Num4 ? state = State::PLAYING :
			event.key.code == Keyboard::Num5 ? state = State::PLAYING :
			event.key.code == Keyboard::Num6 ? state = State::PLAYING : state = State::LEVELING_UP;

			if (state == State::PLAYING)
			{
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				// Will be modified
				int tileSize = 50;

				player.spawn(arena,resolution, tileSize);

				clock.restart();
			}
		}

#pragma endregion


	#pragma region UPDATE

		if(state == State::PLAYING)
		{
			Time deltaTime(clock.restart());
			gameTimeTotal += deltaTime;
			float dtAsSeconds(deltaTime.asSeconds());

			mouseScreenPosition = Mouse::getPosition();
			mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);

			player.update(dtAsSeconds, mouseScreenPosition);

			Vector2f playerPosition(player.getCenter());
			mainView.setCenter(playerPosition);
		}

	#pragma endregion


	#pragma region DRAW

		if(state == State::PLAYING)
		{
			std::cout << "playing" << std::endl;;
			window.clear();

			window.setView(mainView);
			window.draw(player.getSprirte());
		}

		if (state == State::LEVELING_UP)
		{
			std::cout << "leveling up" << std::endl;;
			// ...
		}

		if (state == State::PAUSED)
		{
			std::cout << "paused" << std::endl;;
			// ...
		}

		if (state == State::GAME_OVER)
		{
			std::cout << "gameover" << std::endl;;
		}

		window.display();

	#pragma endregion

	}

	return 0;
}
