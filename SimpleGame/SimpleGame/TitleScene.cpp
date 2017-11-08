#include "stdafx.h"
#include "TitleScene.h"
#include "Framework.h"
#include "ArrowObject.h"

TitleScene::TitleScene(const Type& tag) : Scene(tag)
{
}
TitleScene::~TitleScene()
{
}

void TitleScene::BuildObjects()
{
	Scene::BuildObjects();
	m_vec4fBackgroundColor = { 0.0f, 0.3f, 0.3f, 1.0f };
	m_pTestObject = new ArrowObject(0, 0, 0, 4, 1, 0, 1, 1, GameObject::ObjectType::OBJECT_BULLET);
}

void TitleScene::ReleaseObjects()
{
	delete m_pTestObject;
}

void TitleScene::Update(const double TimeElapsed)
{
	m_pTestObject->Update(TimeElapsed);
}

void TitleScene::PrepareUpdate(const double TimeElapsed)
{
}

void TitleScene::PhysicsProcess(const double TimeElapsed)
{
}

void TitleScene::Render()
{
	glClearColor(
		m_vec4fBackgroundColor.r, 
		m_vec4fBackgroundColor.g, 
		m_vec4fBackgroundColor.b, 
		m_vec4fBackgroundColor.a);

	m_pTestObject->Render(m_pRenderer);
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
		GameFramework.ChangeScene(Scene::Type::Main);
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
