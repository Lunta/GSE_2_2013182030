#pragma once
#include "Scene.h"

class TestObject;

class MainScene : public Scene
{
private:
	TestObject* m_pTestObject;

public:
	MainScene(const Type& tag);
	virtual ~MainScene();

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Update(const double TimeElapsed);
	virtual void Render();

	virtual void Input_Key(unsigned char key, int x, int y);
	virtual void Input_SpecialKey(int key, int x, int y);
	virtual void Input_MouseButton(int button, int BottonPress, int x, int y);
};

