#include "stdafx.h"
#include "SoundManager.h"
#include "Framework.h"
#include "GameTimer.h"

#include "TitleScene.h"
#include "MainScene.h"


Framework::Framework() 
	: m_pCurrentScene(nullptr)
	, m_pSound(nullptr)
{
	for (int i = 0; i < SceneTypeToIdx(Count); ++i)
		m_pSceneArr[i] = nullptr;
}
Framework::~Framework()
{
	for (int i = 0; i < SceneTypeToIdx(Count); ++i)
		if(m_pSceneArr[i]) delete m_pSceneArr[i];
	if (m_pSound) delete m_pSound;
}

void Framework::Init(int client_width, int client_height)
{
	m_iClientWidth = client_width;
	m_iClientHeight = client_height;

	Timer.Init();

	BuildObjects();
	BuildScenes();

	std::cout << "\n\n The game framework is ready to run.\n";
}

void Framework::BuildObjects()
{
	m_pSound = new CSoundManager();
	m_pSound->Init();
}

void Framework::BuildScenes()
{
	m_pSceneArr[SceneTypeToIdx(Title)] = new TitleScene(Scene::Type::Title);
	m_pSceneArr[SceneTypeToIdx(Title)]->BuildObjects();
	m_pSceneArr[SceneTypeToIdx(Title)]->SetSound(m_pSound);

	m_pSceneArr[SceneTypeToIdx(Main)] = new MainScene(Scene::Type::Main);
	m_pSceneArr[SceneTypeToIdx(Main)]->BuildObjects();
	m_pSceneArr[SceneTypeToIdx(Main)]->SetSound(m_pSound);

	m_pCurrentScene = m_pSceneArr[SceneTypeToIdx(Main)];
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

/*    BUTTON_STATE    */
// - MOUSE_BUTTON_UP
// - MOUSE_BUTTON_DOWN
void Framework::Input_MouseButton(int button, int state, int x, int y)
{
	if(m_pCurrentScene)
		m_pCurrentScene->Input_MouseButton(button, state, x, y);
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
		std::to_string((int)Timer.GetFPS()) + ")";
	return m_strTitle.data();
}

Framework& Framework::GetInstance()
{
	static Framework instance;
	return instance;
}