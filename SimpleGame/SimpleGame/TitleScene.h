#pragma once
#include "Scene.h"

class TestObject;

class TitleScene : public Scene
{
private:
	TestObject* m_pTestObject;

public:
	TitleScene(const Type& tag);
	virtual ~TitleScene();

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void Update(const double TimeElapsed);
	virtual void Render();

	virtual void Input_Key(unsigned char key, int x, int y);
	virtual void Input_SpecialKey(int key, int x, int y);
	virtual void Input_MouseButton(int button, int BottonPress, int x, int y);
};

