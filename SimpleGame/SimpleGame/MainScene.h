#pragma once
#include "Scene.h"

#define MAX_OBJECTS_COUNT 50

class GameObject;
class TestObject;

class MainScene final : public Scene
{
private:
	std::vector<TestObject*> m_vecpTestObjects;

public:
	MainScene(const Type& tag);
	virtual ~MainScene() override;

	virtual void BuildObjects() override;
	virtual void ReleaseObjects() override;

	virtual void Update(const double TimeElapsed) override;
	virtual void Render() override;

	virtual void Input_Key(unsigned char key, int x, int y) override;
	virtual void Input_SpecialKey(int key, int x, int y) override;
	virtual void Input_MouseButton(int button, int state, int x, int y) override;

	bool IsCollision(GameObject* a, GameObject* b);
};
