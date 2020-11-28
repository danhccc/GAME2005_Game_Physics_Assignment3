#include "Plane.h"
#include "TextureManager.h"
#include "Util.h"
#include "SoundManager.h"

Plane::Plane()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	m_buildAnimations();
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", getAnimation("plane"),
		x, y, 0.5f, 0, 255, true);
}

void Plane::update()
{
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

void Plane::clean()
{
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}

void Plane::moveLeft()
{
	m_direction.x = -1;
}

void Plane::moveRight()
{
	m_direction.x = 1;
}

void Plane::moveUp()
{
	m_direction.y = -1;
}

void Plane::moveDown()
{
	m_direction.y = 1;
}

void Plane::stopMovingX()
{
	m_direction.x = 0;
}

void Plane::stopMovingY()
{
	m_direction.y = 0;
}

std::string Plane::checkDistance(GameObject* pGameObject)
{
	// Use Pythagorean a^2 + b^2 = c^2 OR c = sqrt(a^2 + b^2)
	float x = pGameObject->getTransform()->position.x - getTransform()->position.x;
	float y = pGameObject->getTransform()->position.y - getTransform()->position.y;
	std::string hit = "HIT";
	if (sqrt(x * x + y * y) <= 28)
	{
		SoundManager::Instance().playSound("yay", 0);
		return hit;
	}
	else return std::to_string(sqrt(x * x + y * y));
}

bool Plane::checkCollision(GameObject* oObject)
{
	glm::vec2 pPosition = getTransform()->position;
	glm::vec2 bPosition = oObject->getTransform()->position;
	
	float planeRadius = getWidth() / 2;
	float bulletRadius = oObject->getWidth() / 2;
	float radiusSum = planeRadius + bulletRadius;

	float x = bPosition.x - pPosition.x;
	float y = bPosition.y - pPosition.y;
	float bpDistance = sqrt(x * x + y * y);

	if (bpDistance <= radiusSum) return true;
	else return false;
}