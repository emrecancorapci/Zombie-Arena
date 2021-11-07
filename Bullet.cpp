#include "Bullet.h"

Bullet::Bullet()
{
	_bulletShape.setSize(sf::Vector2f(2,2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
	_isFlying = true;
	_position.x = startX;
	_position.y = startY;

	float gradient = (startX - targetX) / (startY - targetY);

	if (gradient < 0)
	{
		gradient *= -1;
	}

	float ratioXY = _bulletSpeed / (gradient + 1);

	_bulletDistX = ratioXY * gradient;
	_bulletDistY = ratioXY;

	if (targetX < startX)
	{
		_bulletDistX *= -1;
	}

	if (targetY < startY)
	{
		_bulletDistY *= -1;
	}

	float range = 1000;
	_minX = startX - range;
	_maxX = startX + range;
	_minY = startY - range;
	_maxY = startY + range;

	_bulletShape.setPosition(_position);
}

void Bullet::stop()
{
	_isFlying = false;
}

bool Bullet::isFlying()
{
	return _isFlying;
}


FloatRect Bullet::getPosition()
{
	return _bulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
	return _bulletShape;
}

void Bullet::update(float deltaTime)
{
	_position.x += _bulletDistX * deltaTime;
	_position.y += _bulletDistY * deltaTime;

	_bulletShape.setPosition(_position);

	if (_position.x < _minX || _position.x > _maxX ||
		_position.y < _minY || _position.y > _maxY)
	{
		_isFlying = false;
	}
}


