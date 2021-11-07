#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"
#include "Bullet.h"

using namespace sf;

int main()
{

#pragma region START

	TextureHolder textureHolder;

	enum class State{ PAUSED, LEVELING_UP, GAME_OVER, PLAYING};

	State state(State::GAME_OVER);

	// Window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(
		VideoMode(resolution.x, resolution.y),
		"Zombie Arena", Style::Fullscreen);

	View mainView(FloatRect(0,0, resolution.x, resolution.y));

	// Time
	Clock clock;

	Time gameTimeTotal;
	Time lastPressed;

	// Mouse
	Vector2f mouseWorldPosition;
	Vector2i mouseScreenPosition;

	Player player;

	// Background
	IntRect arena;

	VertexArray background;
	Texture backgroundTexture = TextureHolder::GetTexture("graphics/background_sheet.png");

	// Zombies
	int numZombies;
	int numZombiesAlive;

	Zombie* zombies = nullptr;

	// Bullets
	Bullet bullets[100];

	int currentBullet = 0;
	int bulletsSpare = 24;
	int bulletsInClip = 6;
	int clipSize = 6;
	float fireRate = 1;

	// Cursor and crosshair
	window.setMouseCursorVisible(false);
	Sprite spriteCrosshair;
	Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25,25);

#pragma endregion

	while(window.isOpen())
	{

	#pragma region PRE-UPDATE

		// Events
		Event event{};
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
					// Reloading
					if (event.key.code == Keyboard::R)
					{
						if (bulletsSpare >= clipSize)
						{
							bulletsInClip = clipSize;
							bulletsSpare -= clipSize;
						}
						else if (bulletsSpare > 0)
						{
							bulletsInClip = bulletsSpare;
							bulletsSpare = 0;
						}
						else
						{
							// ...
						}
					}
				}
			}
		}

		// Closing Window
		if(Keyboard::isKeyPressed(Keyboard::Escape))
			window.close();

		// WASD
		if (state == State::PLAYING)
		{
			Keyboard::isKeyPressed(Keyboard::W)? player.moveUp() : player.stopUp();
			Keyboard::isKeyPressed(Keyboard::S)? player.moveDown() : player.stopDown();
			Keyboard::isKeyPressed(Keyboard::A)? player.moveLeft() : player.stopLeft();
			Keyboard::isKeyPressed(Keyboard::D)? player.moveRight() : player.stopRight();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (gameTimeTotal.asMilliseconds() * 1.0f - lastPressed.asMilliseconds() > 1000 / fireRate
					&& bulletsInClip > 0)
				{
					bullets[currentBullet].shoot(
						player.getCenter().x, 
						player.getCenter().y,
						mouseWorldPosition.x, 
						mouseWorldPosition.y);

					currentBullet++;

					if (currentBullet > 99)
					{
						currentBullet = 0;
					}

					lastPressed = gameTimeTotal;

					bulletsInClip--;
				}
			}
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

				int tileSize = createBackground(background, arena);

				player.spawn(arena,resolution, tileSize);

				numZombies = 10;

				delete[] zombies;

				zombies = createHorde(numZombies,arena);
				numZombiesAlive = numZombies;


				clock.restart();
			}
		}

#pragma endregion


	#pragma region UPDATE

		if(state == State::PLAYING)
		{
			// Time
			Time deltaTime(clock.restart());
			gameTimeTotal += deltaTime;
			float dtAsSeconds(deltaTime.asSeconds());

			// Mouse
			mouseScreenPosition = Mouse::getPosition();
			mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, mainView);
			spriteCrosshair.setPosition(mouseWorldPosition);

			// Player
			player.update(dtAsSeconds, mouseScreenPosition);

			Vector2f playerPosition(player.getCenter());
			mainView.setCenter(playerPosition);

			// Zombies
			for (int i = 0; numZombies > i; i++)
			{
				if(zombies[i].isAlive())
					zombies[i].update(deltaTime.asSeconds(), playerPosition);
			}

			// Bullets
			for (auto& bullet : bullets)
			{
				if (bullet.isFlying())
				{
					bullet.update(dtAsSeconds);
				}
			}
		}

	#pragma endregion


	#pragma region DRAW

		if(state == State::PLAYING)
		{
			window.clear();

			window.setView(mainView);
			window.draw(background, &backgroundTexture);

			// Zombies
			for (int i = 0; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}

			// Bullets
			for (auto& bullet : bullets)
			{
				window.draw(bullet.getShape());
			}

			//Player
			window.draw(player.getSprirte());

			// Crosshair
			window.draw(spriteCrosshair);

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
			std::cout << "game-over" << std::endl;;
		}

		window.display();

	#pragma endregion

	}

	delete[] zombies;

	return 0;
}
