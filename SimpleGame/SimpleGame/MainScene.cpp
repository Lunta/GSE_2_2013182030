#include "stdafx.h"
#include "MainScene.h"
#include "Framework.h"
#include "CharactorObject.h"
#include "BuildingObject.h"

MainScene::MainScene(const Type& tag) 
	: Scene(tag)
	, m_fTeam1_SpawnTimer(0)
	, m_fTeam2_SpawnTimer(0)
{
}
MainScene::~MainScene()
{
	ReleaseObjects();
}

void MainScene::BuildObjects()
{
	Scene::BuildObjects();
	m_vec4fBackgroundColor = { 0.0f, 0.3f, 0.3f, 1.0f };
	
	float building_stride_width = (float)CLIENT_WIDTH * 0.25f;
	float building_pos_y = (float)CLIENT_HEIGHT * 0.4f;
	for (int i = -1; i < 2; ++i)
	{
		BuildingObject* obj = new BuildingObject(Vec3f(
			  building_stride_width * i
			, building_pos_y
			, 0)
			, DEFAULT_BUILDING_SIZE
			, Vec4f(1, 1, 1, 1)
			, GameObject::ObjectTeam::OBJECT_TEAM_1
			, GameObject::ObjectType::OBJECT_BUILDING);
		obj->LoadTexture(m_pRenderer, BUILDING_TEAM_1_TEXTURE_PATH);
		obj->SetBulletList(&m_pBulletList);
		m_pBuildingList.push_back(obj);

		obj = new BuildingObject(Vec3f(
			building_stride_width * i
			, -building_pos_y
			, 0)
			, DEFAULT_BUILDING_SIZE
			, Vec4f(1, 1, 1, 1)
			, GameObject::ObjectTeam::OBJECT_TEAM_2
			, GameObject::ObjectType::OBJECT_BUILDING);
		obj->LoadTexture(m_pRenderer, BUILDING_TEAM_2_TEXTURE_PATH);
		obj->SetBulletList(&m_pBulletList);
		m_pBuildingList.push_back(obj);
	}
	
	
}

void MainScene::ReleaseObjects()
{
	for (auto& p : m_pBuildingList)
		if (p) delete p;
	for (auto& p : m_pBulletList)
		if (p) delete p;
	for (auto& p : m_pCharactorList)
		if (p) delete p;
	m_pBuildingList.clear();
	m_pBulletList.clear();
	m_pCharactorList.clear();
}

void MainScene::Update(const double TimeElapsed)
{
	PrepareUpdate(TimeElapsed);

	for (auto& p : m_pBuildingList)
		p->Update(TimeElapsed);
	for (auto& p : m_pBulletList)
		p->Update(TimeElapsed);
	for (auto& p : m_pCharactorList)
		p->Update(TimeElapsed);
	
	PhysicsProcess(TimeElapsed);
}

void MainScene::PrepareUpdate(const double TimeElapsed)
{
	m_pBuildingList.remove_if(
		[](const GameObject* pObj)->bool {
		if (pObj->IsDie()) { delete pObj; return true; }
		return false; });
	m_pBulletList.remove_if(
		[](const GameObject* pObj)->bool {
		if (pObj->IsDie()) { delete pObj; return true; }
		return false; });
	m_pCharactorList.remove_if(
		[](const GameObject* pObj)->bool {
		if (pObj->IsDie()) { delete pObj; return true; }
		return false; });

	m_fTeam1_SpawnTimer += TimeElapsed;
	if (m_fTeam1_SpawnTimer > TEAM_1_CHARACTOR_RESPAWN_DELAY)
	{
		RandomSpawnCharactor(GameObject::ObjectTeam::OBJECT_TEAM_1);
		m_fTeam1_SpawnTimer = 0.f;
	}
	m_fTeam2_SpawnTimer += TimeElapsed;
}

void MainScene::PhysicsProcess(const double TimeElapsed)
{
	for (auto& p : m_pBuildingList)
		for (auto& q : m_pCharactorList)
		{
			if (p->GetTeamTag() == q->GetTeamTag()) continue;
			if (p == q || (p->IsCollide() && q->IsCollide())) continue;
			if (p->GetBindingBox().CheckCollision(q->GetBindingBox()))
			{
				p->CollideWith(q);
				q->CollideWith(p);
			}
		}
	for (auto& q : m_pBulletList)
	{
		for (auto& p : m_pCharactorList)
		{
			if (p->GetTeamTag() == q->GetTeamTag()) continue;
			if (p == q || (p->IsCollide() && q->IsCollide())) continue;
			if (p->GetBindingBox().CheckCollision(q->GetBindingBox()))
			{
				p->CollideWith(q);
				q->CollideWith(p);
			}
		}
		for (auto& p : m_pBuildingList)
		{
			if (p->GetTeamTag() == q->GetTeamTag()) continue;
			if (p == q || (p->IsCollide() && q->IsCollide())) continue;
			if (p->GetBindingBox().CheckCollision(q->GetBindingBox()))
			{
				p->CollideWith(q);
				q->CollideWith(p);
			}
		}
	}
}

void MainScene::Render()
{
	glClearColor(
		m_vec4fBackgroundColor.r,
		m_vec4fBackgroundColor.g,
		m_vec4fBackgroundColor.b,
		m_vec4fBackgroundColor.a);

	for (auto& p : m_pBuildingList)
		p->Render(m_pRenderer);
	for (auto& p : m_pBulletList)
		p->Render(m_pRenderer);
	for (auto& p : m_pCharactorList)
		p->Render(m_pRenderer);
}

void MainScene::Input_Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case KEY_TAB:
		break;
	case KEY_BACKSPACE:
		break;
	case KEY_SPACE:
		GameFramework.ChangeScene(Scene::Type::Title);
		break;
	case KEY_ENTER:
		break;
	default:
		break;
	}
}

void MainScene::Input_SpecialKey(int key, int x, int y)
{
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

void MainScene::Input_MouseButton(int button, int state, int x, int y)
{
	switch (button)
	{
	case MOUSE_LEFT_BUTTON:
		if (state == MOUSE_BUTTON_UP)
		{
			float PosY = CLIENT_HEIGHT / 2 - y;
			if (PosY > 0) break;
			if (m_fTeam2_SpawnTimer > TEAM_2_CHARACTOR_RESPAWN_DELAY)
			{
				SpawnCharactor(Vec3f(x - CLIENT_WIDTH / 2, PosY, 0));
				m_fTeam2_SpawnTimer = 0.f;
			}
		}
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

void MainScene::RandomSpawnCharactor(GameObject::ObjectTeam team)
{
	if (m_pCharactorList.size() < MAX_OBJECTS_COUNT)
	{
		switch (team)
		{
		case GameObject::ObjectTeam::OBJECT_TEAM_1: 
		{
			CharactorObject* obj = new CharactorObject(Vec3f(
				(rand() % CLIENT_WIDTH) - (CLIENT_WIDTH / 2)
				, rand() % (CLIENT_HEIGHT / 2)
				, 0)
				, DEFAULT_CHARACTOR_SIZE
				, CHARACTOR_TEAM_1_COLOR
				, GameObject::ObjectTeam::OBJECT_TEAM_1
				, GameObject::ObjectType::OBJECT_CHARACTER);
			obj->SetDirection(
				(rand() % 2000) - (rand() / 1000),
				(rand() % 2000) - (rand() / 1000));
			obj->SetArrowList(&m_pBulletList);
			m_pCharactorList.push_back(obj);
			break;
		}
		case GameObject::ObjectTeam::OBJECT_TEAM_2:	
		{
			CharactorObject* obj = new CharactorObject(Vec3f(
				(rand() % CLIENT_WIDTH) - (CLIENT_WIDTH / 2)
				, -rand() % (CLIENT_HEIGHT / 2)
				, 0)
				, DEFAULT_CHARACTOR_SIZE
				, CHARACTOR_TEAM_2_COLOR
				, GameObject::ObjectTeam::OBJECT_TEAM_2
				, GameObject::ObjectType::OBJECT_CHARACTER);
			obj->SetDirection(
				(rand() % 2000) - (rand() / 1000),
				(rand() % 2000) - (rand() / 1000));
			obj->SetArrowList(&m_pBulletList);
			m_pCharactorList.push_back(obj);
			break;
		}
		}
		
	}
}

void MainScene::SpawnCharactor(const Vec3f & pos)
{
	if (m_pCharactorList.size() < MAX_OBJECTS_COUNT)
	{
		if (pos.y > 0)
		{
			//CharactorObject* obj = new CharactorObject(
			//	  pos
			//	, DEFAULT_CHARACTOR_SIZE
			//	, CHARACTOR_TEAM_1_COLOR
			//	, GameObject::ObjectTeam::OBJECT_TEAM_1
			//	, GameObject::ObjectType::OBJECT_CHARACTER);
			//obj->SetDirection(
			//	(rand() % 2000) - (rand() / 1000),
			//	(rand() % 2000) - (rand() / 1000));
			//obj->SetArrowList(&m_pBulletList);
			//m_pCharactorList.push_back(obj);
		}
		else if (pos.y < 0)
		{
			CharactorObject* obj = new CharactorObject(
				  pos
				, DEFAULT_CHARACTOR_SIZE
				, CHARACTOR_TEAM_2_COLOR
				, GameObject::ObjectTeam::OBJECT_TEAM_2
				, GameObject::ObjectType::OBJECT_CHARACTER);
			obj->SetDirection(
				(rand() % 2000) - (rand() / 1000),
				(rand() % 2000) - (rand() / 1000));
			obj->SetArrowList(&m_pBulletList);
			m_pCharactorList.push_back(obj);
		}
	}
}
