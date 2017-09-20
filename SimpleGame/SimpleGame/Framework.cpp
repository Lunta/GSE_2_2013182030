#include "stdafx.h"
#include "Framework.h"
#include "GameTimer.h"

#include "TitleScene.h"
#include "MainScene.h"


Framework::Framework() : m_pCurrentScene(nullptr)
{
	for (int i = 0; i < SceneTypeToIdx(Count); ++i)
		m_pSceneArr[i] = nullptr;
}
Framework::~Framework()
{
}

void Framework::Init(int client_width, int client_height)
{
	m_iClientWidth = client_width;
	m_iClientHeight = client_height;
	Timer->Init();
	BuildScenes();
	BuildObjects();
}

void Framework::BuildObjects()
{
	if (m_pCurrentScene)
		m_pCurrentScene->BuildObjects();
}

void Framework::BuildScenes()
{
	m_pSceneArr[SceneTypeToIdx(Title)] = new TitleScene(Scene::Type::Title);
	m_pSceneArr[SceneTypeToIdx(Title)]->BuildObjects();

	m_pSceneArr[SceneTypeToIdx(Main)] = new MainScene(Scene::Type::Main);
	m_pSceneArr[SceneTypeToIdx(Main)]->BuildObjects();

	m_pCurrentScene = m_pSceneArr[SceneTypeToIdx(Title)];
}

void Framework::ChangeScene(const Scene::Type & type)
{
	if (!m_pCurrentScene)
		BuildScenes();

	m_pCurrentScene = m_pSceneArr[GetEnumValueByType(type)];
}

void Framework::Update(double TimeElapsed)
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update(TimeElapsed);
}

void Framework::Render()
{
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
	
}

void Framework::Input_Key(unsigned char key, int x, int y)
{
	if (m_pCurrentScene)
		m_pCurrentScene->Input_Key(key, x, y);
	else
		switch (key)
		{
		case KEY_TAB:
			break;
		case KEY_BACKSPACE:
			break;
		case KEY_SPACE:
			break;
		case KEY_ENTER:
			break;
		default:
			break;
		}
}

void Framework::Input_SpecialKey(int key, int x, int y)
{
	if (m_pCurrentScene)
		m_pCurrentScene->Input_SpecialKey(key, x, y);
	else
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

/*   BottonPress        */
// - MOUSE_BUTTON_UP
// - MOUSE_BUTTON_DOWN
void Framework::Input_MouseButton(int button, int BottonPress, int x, int y)
{
	if(m_pCurrentScene)
		m_pCurrentScene->Input_MouseButton(button, BottonPress, x, y);
	else
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

const char * Framework::GetTitleStr()
{
	m_strTitle = std::string(CLIENT_TITLE) + " (FPS " + 
		std::to_string((int)Timer->GetFPS()) + ")";
	return m_strTitle.data();
}

const int Framework::GetClientWidth()
{
	return m_iClientWidth;
}

const int Framework::GetClientHeight()
{
	return m_iClientHeight;
}

Framework* Framework::GetInstance()
{
	static Framework* instance = nullptr;
	if (!instance)
		instance = new Framework();
	return instance;
}