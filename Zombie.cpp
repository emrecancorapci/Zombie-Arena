#include "Zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		// Bloater
		_sprite = Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		_speed = BLOATER_SPEED;
		_health = BLOATER_HEALTH;
		break;
	case 1:
		// Chaser
		_sprite = Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		_speed = CHASER_SPEED;
		_health = CHASER_HEALTH;
		break;
	case 2:
		// Crawler
		_sprite = Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		_speed = CRAWLER_SPEED;
		_health = CRAWLER_HEALTH;
		break;
	default:
		break;
	}

	srand((int)time(0) * seed);
	float modifier = ((rand() % MAX_VARIANCE) + OFFSET) / 100;
	_speed *= modifier;

	_position.x = startX;
	_position.y = startY;

	_sprite.setOrigin(25,25);
	_sprite.setPosition(_position);
}

bool Zombie::hit()
{
	_health--;

	if (_health < 0)
	{
		_alive = false;
		_sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		return true;
	}

	return false;
}

bool Zombie::isAlive()
{
	return _alive;
}

FloatRect Zombie::getPosition()
{
	return _sprite.getGlobalBounds();
}

Sprite Zombie::getSprite()
{
	return _sprite;
}

void Zombie::update(float elapsedTime, Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (playerX > _position.x)
	{
		_position.x += _speed * elapsedTime;
	}
	if (playerY > _position.y)
	{
		_position.y += _speed * elapsedTime;
	}
	if (playerX < _position.x)
	{
		_position.x -= _speed * elapsedTime;
	}
	if (playerY < _position.y)
	{
		_position.y -= _speed * elapsedTime;
	}

	_sprite.setPosition(_position);

	float angle = atan2(playerY - _position.y,
		playerX - _position.x) * 180 / 3.141f;

	_sprite.setRotation(angle);
}
