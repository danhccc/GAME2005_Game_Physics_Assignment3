#include "Player.h"
#include "TextureManager.h"
#include "Util.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/Brick.png", "Brick");

	const auto size = TextureManager::Instance()->getTextureSize("Brick");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(PLAYER);
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	TextureManager::Instance()->draw("Brick", x, y, 0, 255, true);
}

void Player::update()
{
	//m_move();
	//m_checkBounds();
	const float deltaTime = 1.0f / 60.f;

	// Normalize direction vector: Since mag * num = 1; Therefore num = 1 / mag
	float dirMagnitude = Util::magnitude(m_direction);			// Need this because we can't
	if (dirMagnitude > 0)										// have 1/0, since 1/0 = error
	{
		/*m_direction = m_direction * dirMagnitude;*/	// Need to be here cuz if dirMagnitude=0, it will brake

		getRigidBody()->acceleration = Util::normalize(m_direction) * ACCELERATION;		// setting acceleration
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0)
	{
		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity) * -ACCELERATION;
	}

	// Should always run this, or player will stop when no key input
	getRigidBody()->velocity = getRigidBody()->velocity + getRigidBody()->acceleration;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Player::clean()
{
}

void Player::moveLeft()
{
	m_direction.x = -1;
}

void Player::moveRight()
{
	m_direction.x = 1;
}

void Player::moveUp()
{
	m_direction.y = -1;
}

void Player::moveDown()
{
	m_direction.y = 1;
}

void Player::stopMovingX()
{
	m_direction.x = 0;
}

void Player::stopMovingY()
{
	m_direction.y = 0;
}