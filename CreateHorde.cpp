#include "Zombie.h"
#include "ZombieArena.h"

Zombie* createHorde(int numZombies, IntRect arena)
{
	Zombie* zombies = new Zombie[numZombies];

	int maxX = arena.width - 30;
	int minX = arena.left + 30;
	int maxY = arena.height - 30;
	int minY = arena.top + 30;

	for (int i = 0; i < numZombies; i++)
	{
		// zombies' spawn side
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = rand() % maxY + minY;
			break;
		case 1:
			// right
			x = maxX;
			y = rand() % maxY + minY;
			break;
		case 2:
			// top
			x = rand() % maxX + minX;
			y = minY;
			break;
		case 3:
			// bottom
			x = rand() % maxX + minX;
			y = maxY;
			break;
		}

		// which type
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);

		zombies[i].spawn(x, y, type, i);
	}
	return zombies;
}