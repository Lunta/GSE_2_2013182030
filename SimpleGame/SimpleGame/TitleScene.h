#pragma once
#include "Scene.h"

class GameObject;

class TitleScene final : public Scene
{
private:
	GameObject* m_pTestObject;

public:
	TitleScene(const Type& tag);
	virtual ~TitleScene() override;

	virtual void BuildObjects() override;
	virtual void ReleaseObjects() override;

	virtual void Update(const double TimeElapsed) override;
	virtual void PrepareUpdate(const double TimeElapsed) override;
	virtual void PhysicsProcess(const double TimeElapsed) override;
	virtual void Render() override;

	virtual void Input_Key(unsigned char key, int x, int y) override;
	virtual void Input_SpecialKey(int key, int x, int y) override;
	virtual void Input_MouseButton(int button, int state, int x, int y) override;
};

