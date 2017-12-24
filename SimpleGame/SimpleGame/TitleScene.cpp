#include "stdafx.h"
#include "TitleScene.h"
#include "Framework.h"
#include "ArrowObject.h"

TitleScene::TitleScene(const Type& tag) : Scene(tag)
{
}
TitleScene::~TitleScene()
{
	m_pRenderer->DeleteTexture(m_BackGroundTexture);
}

void TitleScene::BuildObjects()
{
	Scene::BuildObjects();
	m_BackGroundTexture = m_pRenderer->CreatePngTexture("./Assets/Title.png");
}

void TitleScene::ReleaseObjects()
{
}

void TitleScene::Update(const double TimeElapsed)
{
}

void TitleScene::PrepareUpdate(const double TimeElapsed)
{
}

void TitleScene::PhysicsProcess(const double TimeElapsed)
{
}

void TitleScene::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_pRenderer->DrawTexturedRect(0, 0, 0, CLIENT_HEIGHT
		, 1, 1, 1, 1, m_BackGroundTexture, LEVEL_BACKGROUND);
	
	m_pRenderer->DrawTextW(
		-90, -250
		, GLUT_BITMAP_HELVETICA_18
		, static_cast<float>(rand() % 10000) / 10000.f
		, static_cast<float>(rand() % 10000) / 10000.f
		, static_cast<float>(rand() % 10000) / 10000.f
		, "PRESS SPACE KEY TO START GAME");
}

void TitleScene::Input_Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case KEY_TAB:
		break;
	case KEY_BACKSPACE:
		break;
	case KEY_SPACE:
		GameFramework.ChangeScene(Scene::Type::Main, true);
		m_pSound->PlaySoundByTag(CSoundManager::SoundTag::BackGround, true, 0.3f);
		break;
	case KEY_ENTER:
		break;
	default:
		break;
	}
}

void TitleScene::Input_SpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case SPECIAL_KEY_SHIFT:
		break;
	case SPECIAL_KEY_CTRL:
		break;
	case SPECIAL_KEY_ALT:
		break;
	case SPECIAL_KEY_LEFT:
		break;
	case SPECIAL_KEY_UP:
		break;
	case SPECIAL_KEY_RIGHT:
		break;
	case SPECIAL_KEY_DOWN:
		break;
	default:
		break;
	}
}

void TitleScene::Input_MouseButton(int button, int state, int x, int y)
{
	switch (button)
	{
	case MOUSE_LEFT_BUTTON:
		break;
	case MOUSE_WHEEL_BUTTON:
		break;
	case MOUSE_RIGHT_BUTTON:
		break;
	case MOUSE_WHEEL_UP:
		break;
	case MOUSE_WHEEL_DOWN:
		break;
	default:
		break;
	}
}
