#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("A3_startBG", 400, 300, 0, 255, true);
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void StartScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/A3_startBG.jpg", "A3_startBG");

	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color white = { 255, 255, 255, 255 };
	m_pStartLabel = new Label("Physics Assignment 3", "Consolas", 60, white, glm::vec2(400.0f, 60.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Hancong Zhang(101234068)", "Consolas", 20, white, glm::vec2(200.0f, 550.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel = new Label("Zijie Wang(101283316)", "Consolas", 20, white, glm::vec2(600.0f, 550.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Scene 1 button
	m_pScene1 = new Button("../Assets/textures/scene1button.png","scene1button",SCENE1_BUTTON);
	m_pScene1->getTransform()->position = glm::vec2(300.0f, 450.0f);

	m_pScene1->addEventListener(CLICK, [&]()-> void
		{
			m_pScene1->setActive(false);
			TheGame::Instance()->changeSceneState(PLAY_SCENE);
		});

	m_pScene1->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene1->setAlpha(128);
		});

	m_pScene1->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene1->setAlpha(255);
		});
	addChild(m_pScene1);

	// Scene 2 button
	m_pScene2 = new Button("../Assets/textures/scene2button.png", "scene2button", SCENE2_BUTTON);
	m_pScene2->getTransform()->position = glm::vec2(500.0f, 450.0f);

	m_pScene2->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_pScene2->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2->setAlpha(128);
		});

	m_pScene2->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2->setAlpha(255);
		});
	addChild(m_pScene2);
}

