#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ZombieArena.h"
#include "TextureHolder.h"

using namespace sf;

int createBackground(VertexArray& vertexArray, IntRect arena)
{
	// Size of each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	vertexArray.setPrimitiveType(Quads);

	// Size of the vertex array
	vertexArray.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	int currentVertex = 0;

	for (int i = 0; i < worldWidth; i++)
	{
		for(int j = 0; j < worldHeight; j++)
		{
			vertexArray[currentVertex + 0].position = Vector2f(i * TILE_SIZE,j * TILE_SIZE);
			vertexArray[currentVertex + 1].position = Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
			vertexArray[currentVertex + 2].position = Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
			vertexArray[currentVertex + 3].position = Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

			if(i == (0 || worldWidth - 1) || j == (0 || worldHeight - 1))
			{
				vertexArray[currentVertex + 0].texCoords = Vector2f(0, TILE_TYPES * TILE_SIZE);
				vertexArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, TILE_TYPES * TILE_SIZE);
				vertexArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, (TILE_TYPES +1) * TILE_SIZE);
				vertexArray[currentVertex + 3].texCoords = Vector2f(0, (TILE_TYPES +1) * TILE_SIZE);
			}
			else
			{
				srand((int)time(0) + j * (i-1));
				int randomTile = rand() % TILE_TYPES;
				int verticalOffset = randomTile * TILE_SIZE;

				vertexArray[currentVertex + 0].texCoords = Vector2f(0, verticalOffset);
				vertexArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, verticalOffset);
				vertexArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, verticalOffset + TILE_SIZE);
				vertexArray[currentVertex + 3].texCoords = Vector2f(0, verticalOffset + TILE_SIZE);

			}

			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}


int main()
{

#pragma region START

	TextureHolder textureHolder;

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

	VertexArray background;
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("graphics/background_sheet.png");

	int numZombies;
	int numZombiesAlive;
	Zombie* zombies = nullptr;

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

				int tileSize = createBackground(background, arena);

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

			window.draw(background, &backgroundTexture);

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
			std::cout << "game-over" << std::endl;;
		}

		window.display();

	#pragma endregion

	}

	return 0;
}
