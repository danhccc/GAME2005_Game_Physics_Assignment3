#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "Player.h"
#include "ship.h"

class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


private:
	Label* m_label{};
	Player* m_pPlayer;
	Ship* m_pBall;
	Button* m_pBackButton;
	//Button* m_pRestartButton;
	void getCollide();
	void GUI_Function() const;
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;

};

#endif /* defined (__END_SCENE__) */