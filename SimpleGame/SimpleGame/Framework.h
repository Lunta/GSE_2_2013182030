#pragma once
#include "Scene.h"

class Sound;
class Framework final
{
private:
	std::string				m_strTitle;
	int						m_iClientWidth;
	int						m_iClientHeight;

	Scene*					m_pSceneArr[SceneTypeToIdx(Count)];
	Scene*					m_pCurrentScene;

	CSoundManager*			m_pSound;

private:
	Framework();
	Framework(const Framework& _framework) = delete;

public:
	~Framework();

	void Init(int client_width, int client_height);
	void BuildObjects();
	void BuildScenes();
	void ChangeScene(const Scene::Type& type);

	void Update(double TimeElapsed);
	void Render();

	void Input_Key(unsigned char key, int x, int y);
	void Input_SpecialKey(int key, int x, int y);
	void Input_MouseButton(int button, int state, int x, int y);

	const char* GetTitleStr();
	const int GetClientWidth() const { return m_iClientWidth; }
	const int GetClientHeight() const { return m_iClientHeight; }

public:
	static Framework& GetInstance();
};

static Framework& GameFramework = Framework::GetInstance();
