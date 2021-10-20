#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 200;
	const float START_HEALTH = 100;

	Vector2f _position;
	Sprite _sprite;
	Texture _texture;
	Time _lastHit;

	int _health;
	int _maxHealth;
	float _speed;

	bool _pressedUp;
	bool _pressedDown;
	bool _pressedLeft;
	bool _pressedRight;

protected:
	Vector2f _resolution;
	IntRect _arena;
	int _tileSize;

public:
	Player();

	Vector2f getCenter();
	Time getLastHitTime();
	FloatRect getPosition();
	Sprite getSprirte();


	float getRotation();
	int getHealth();
	bool hit(Time timeHit);

	void spawn(IntRect arena, Vector2f resolution, int tileSize);
	void update(float elapsedTime, Vector2i mousePosition);
	void resetPlayerState();

	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);

	void moveRight();
	void stopRight();
	void moveLeft();
	void stopLeft();
	void moveUp();
	void stopUp();
	void moveDown();
	void stopDown();
};

