#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	Vector2f _position;
	Sprite _sprite;
	float _speed;
	float _health;
	bool _alive;

public:
	// When bullet hits zombie
	bool hit();
	bool isAlive();

	// Spawn a zombie
	void spawn(float startX, float startY, int type, int seed);
	void update(float elapsedTime, Vector2f playerLocation);

	FloatRect getPosition();
	Sprite getSprite();
};

