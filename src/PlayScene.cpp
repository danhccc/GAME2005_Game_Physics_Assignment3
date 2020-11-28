#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include <vector>
#include "CollisionManager.h"
#include "Util.h"
#include "Plane.h"
using namespace std;

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();

	//m_pPool = new BulletPool(10);
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("Scene1BG", 400, 300, 0, 225, true);
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void PlayScene::update()
{
	updateDisplayList();
	if (SDL_GetTicks() - bulletSpawnTimerStart >= bulletSpawnTimeDuration)
	{
		SpawnBullet();
	}
	vector<Target*>& activeBullets = m_pPool->all;
	for (vector<Target*>::iterator myiter = activeBullets.begin(); myiter != activeBullets.end(); myiter++)
	{
		Target* bullet = *myiter;
		if (bullet->active && bullet->getTransform()->position.y >= 600)
		{
			m_pPool->Despawn(*myiter);
			break;
		}
		if (m_pPlaneSprite->checkCollision(bullet))
		{
			cout << "Plane hit!" << endl;
			SoundManager::Instance().playSound("boom", 0);
		}
	}
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_pPlaneSprite->moveLeft();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
	{
		m_pPlaneSprite->moveRight();
	}
	else
	{
		m_pPlaneSprite->stopMovingX();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
	{
		m_pPlaneSprite->moveUp();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		m_pPlaneSprite->moveDown();
	}
	else
	{
		m_pPlaneSprite->stopMovingY();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/A3_S1BG.jpg", "Scene1BG");
	SoundManager::Instance().load("../Assets/audio/explosion.wav", "boom", SOUND_SFX);



	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Plane Sprite
	m_pPlaneSprite = new Plane();
	addChild(m_pPlaneSprite);

	// Target Sprite
	m_pTarget = new Target();
	addChild(m_pTarget);

	m_pPool = new BulletPool(10);
	for (vector<Target*>::iterator myiter = m_pPool->all.begin(); myiter != m_pPool->all.end(); myiter++)
	{
		Target* bullet = *myiter;
		addChild(bullet);
	}
	bulletSpawnTimerStart = SDL_GetTicks();

	// Player Sprite
	//m_pPlayer = new Player();
	//addChild(m_pPlayer);
	//m_playerFacingRight = true;

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(75.0f, 575.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Button("My Button"))
	{
		std::cout << "My Button Pressed" << std::endl;
	}

	ImGui::Separator();

	//ImGui::Value("Plane magnitude: ", m_pPlaneSprite->magnitude);
	ImGui::Value("Object pool size: ", m_pPool->all.size());

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void PlayScene::SpawnBullet()
{
	Target* bullet = m_pPool->Spawn();
	if (bullet) {
		//addChild(bullet);
		bullet->getTransform()->position = glm::vec2(50 + rand() % 700, 0);
	}
	bulletSpawnTimerStart = SDL_GetTicks() - 2;
}