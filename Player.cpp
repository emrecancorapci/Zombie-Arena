#include "Player.h"
#include "TextureHolder.h"

Player::Player()
{
	_speed = START_SPEED;
	_health = START_HEALTH;
	_maxHealth = START_HEALTH;

	_sprite = Sprite(TextureHolder::GetTexture("graphics/player.png"));

	_sprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	_position.x = arena.width / 2;
	_position.y = arena.height / 2;

	_arena.left = arena.left;
	_arena.width = arena.width;
	_arena.top = arena.top;
	_arena.height = arena.height;

	_tileSize = tileSize;

	_resolution.x = resolution.x;
	_resolution.y = resolution.y;
}

void Player::resetPlayerState()
{
	_speed = START_SPEED;
	_health = START_HEALTH;
	_maxHealth = START_HEALTH;
}

Time Player::getLastHitTime()
{
	return _lastHit;
}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - _lastHit.asMilliseconds() > 200)
	{
		_lastHit = timeHit;
		_health -= 10;

		return true;
	}
	else return false;
}

FloatRect Player::getPosition()
{
	return _sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return _position;
}

float Player::getRotation()
{
	return _sprite.getRotation();
}

Sprite Player::getSprirte()
{
	return _sprite;
}

int Player::getHealth()
{
	return _health;
}


void Player::moveLeft()
{
	_pressedLeft = true;
}
void Player::moveRight()
{
	_pressedRight = true;
}
void Player::moveUp()
{
	_pressedUp = true;
}
void Player::moveDown()
{
	_pressedDown = true;
}

void Player::stopLeft()
{
	_pressedLeft = false;
}
void Player::stopRight()
{
	_pressedRight = false;
}
void Player::stopUp()
{
	_pressedUp = false;
}
void Player::stopDown()
{
	_pressedDown = false;
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{
	if (_pressedUp)
	{
		_position.y -= _speed * elapsedTime;
	}
	if (_pressedDown)
	{
		_position.y += _speed * elapsedTime;
	}
	if (_pressedRight)
	{
		_position.x += _speed * elapsedTime;
	}
	if (_pressedLeft)
	{
		_position.x -= _speed * elapsedTime;
	}

	_sprite.setPosition(_position);

	// Keep player in the arena
	if (_position.x > _arena.width - _tileSize)
	{
		_position.x = _arena.width - _tileSize;
	}

	if (_position.x < _arena.left + _tileSize)
	{
		_position.x = _arena.left + _tileSize;
	}

	if (_position.y > _arena.height - _tileSize)
	{
		_position.y = _arena.height - _tileSize;
	}

	if (_position.y < _arena.top + _tileSize)
	{
		_position.y = _arena.top + _tileSize;
	}

	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - _resolution.y / 2.f,
		mousePosition.x - _resolution.x / 2.f)) *
		180 / 3.141;

	_sprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	_speed += (START_SPEED * .2);
}

void Player::upgradeHealth()
{
	_maxHealth += (START_HEALTH * .2);
}

void Player::increaseHealthLevel(int amount)
{
	_health += amount;

	_health > _maxHealth ? _health = _maxHealth : NULL;
}

