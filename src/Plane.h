#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"
#include "Label.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMovingX();
	void stopMovingY();

	bool isColliding(GameObject* pOther);
	std::string checkDistance(GameObject* pGameObject);

private:
	void m_buildAnimations();
	const float ACCELERATION = 10.0f;
	glm::vec2 m_direction;
};

#endif /* defined (__PLANE__) */
