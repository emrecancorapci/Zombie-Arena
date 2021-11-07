#include <SFML/Graphics.hpp>
#include "ZombieArena.h"

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
