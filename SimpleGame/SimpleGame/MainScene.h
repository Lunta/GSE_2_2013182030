#pragma once
#include "Scene.h"
#include "GameObject.h"

#define MAX_OBJECTS_COUNT 50

class GameObject;

class MainScene final : public Scene
{
private:
	std::list<GameObject*> m_pCharactorList;
	std::list<GameObject*> m_pBuildingList;
	std::list<GameObject*> m_pBulletList;

public:
	MainScene(const Type& tag);
	virtual ~MainScene() override;

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
