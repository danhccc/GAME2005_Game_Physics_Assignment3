#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Target.h"
#include "Button.h"
#include "Label.h"
#include "BulletPool.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;

	const float bulletSpawnTimeDuration = 400.0f;
	float bulletSpawnTimerStart;
	BulletPool* m_pPool;

	Plane* m_pPlaneSprite;
	Target* m_pTarget;
	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	void SpawnBullet();
};

#endif /* defined (__PLAY_SCENE__) */