#pragma once
#include "Scene.h"
#include "GameObject.h"

#define MAX_OBJECTS_COUNT				100
#define TEAM_1_CHARACTOR_RESPAWN_DELAY	1.0f
#define TEAM_2_CHARACTOR_RESPAWN_DELAY	2.0f

class GameObject;

class MainScene final : public Scene
{
private:
	UINT						m_BackGroundTexture;

	std::list<GameObject*>		m_pCharactorList;
	std::list<GameObject*>		m_pBuildingList;
	std::list<GameObject*>		m_pBulletList;

	float						m_fTeam1_SpawnTimer;
	float						m_fTeam2_SpawnTimer;

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

	void RandomSpawnCharactor(GameObject::ObjectTeam team);
	void SpawnCharactor(const Vec3f& pos);
};
