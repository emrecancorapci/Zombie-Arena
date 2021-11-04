#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	Vector2f _position;
	RectangleShape _bulletShape;

	bool _isFlying;

	float _bulletSpeed;
	float _bulletDistX;
	float _bulletDistY;

	float _maxX;
	float _minX;
	float _maxY;
	float _minY;

public:
	Bullet();

	FloatRect getPosition();
	RectangleShape getShape();

	void stop();
	void shoot(float startX, float startY, float targetX, float targetY);
	void update(float deltaTime);

	bool isFlying();

};

