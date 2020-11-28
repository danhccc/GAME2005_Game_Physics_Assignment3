#include "Target.h"
#include "TextureManager.h"


Target::Target()
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png","bullet");

	const auto size = TextureManager::Instance()->getTextureSize("bullet");
	setWidth(size.x);
	setHeight(size.y);
	getTransform()->position = glm::vec2(100.0f, 100.0f);
	getRigidBody()->velocity = glm::vec2(0, 0);
	getRigidBody()->isColliding = false;

	setType(TARGET);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the target
	TextureManager::Instance()->draw("bullet", x, y, 0, 255, true);
}

void Target::update()
{
	m_move();
	m_checkBounds();
}

void Target::clean()
{
}

void Target::m_move()
{
	float deltaTime = 1.0f / 30.0f;
	glm::vec2 gravity = glm::vec2(0, 9.8f);

	getRigidBody()->velocity += (getRigidBody()->acceleration + gravity) * deltaTime;

	//if (!isGravityEnabled) getRigidBody()->velocity.y = 0;

	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Target::m_checkBounds()
{
}

void Target::Reset()
{
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8f);
	getRigidBody()->isColliding = false;
}
