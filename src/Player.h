#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class Player final : public Sprite
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stopMovingX();
	void stopMovingY();

	bool checkCollision(GameObject* oObject);

	// setters
	//void setAnimationState(PlayerAnimationState new_state);

private:
	void m_move();
	void m_checkBounds();
	glm::vec2 m_direction;
	const float ACCELERATION = 10.0f;
	//void m_buildAnimations();
	//PlayerAnimationState m_currentAnimationState;
};

#endif /* defined (__PLAYER__) */