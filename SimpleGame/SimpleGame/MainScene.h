#pragma once
#include "Scene.h"
#include "GameObject.h"

#define MAX_OBJECTS_COUNT				100
#define TEAM_1_CHARACTOR_RESPAWN_DELAY	1.0f
#define TEAM_2_CHARACTOR_RESPAWN_DELAY	2.0f
#define MAIN_SCENE_SHAKING_TIME			0.5f
#define MAIN_SCENE_SHAKING_FACTOR		10.f

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

	bool						m_bShake;
	float						m_fShakingTimer;
	float						m_fShakingFactor;
	Vec2f						m_vec2fShakingVelocity;

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
