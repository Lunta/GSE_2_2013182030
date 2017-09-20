#include "stdafx.h"
#include "TestObject.h"
#include "MainScene.h"
#include "Framework.h"


MainScene::MainScene(const Type& tag) : Scene(tag)
{
}


MainScene::~MainScene()
{
}

void MainScene::BuildObjects()
{
	Scene::BuildObjects();
	m_pTestObject = new TestObject(m_pRenderer, 0, 0, 0, 5, 1, 0, 1, 1);
}

void MainScene::ReleaseObjects()
{
	delete m_pTestObject;
}

void MainScene::Update(const double TimeElapsed)
{
	m_pTestObject->Update(TimeElapsed);
}

void MainScene::Render()
{
	m_pTestObject->Render();

}

void MainScene::Input_Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case KEY_TAB:
		break;
	case KEY_BACKSPACE:
		break;
	case KEY_SPACE:
		GameFramework->ChangeScene(Scene::Type::Title);
		break;
	case KEY_ENTER:
		break;
	default:
		break;
	}
}

void MainScene::Input_SpecialKey(int key, int x, int y)
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

void MainScene::Input_MouseButton(int button, int BottonPress, int x, int y)
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
