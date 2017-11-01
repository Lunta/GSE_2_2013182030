#include "stdafx.h"
#include "MainScene.h"
#include "Framework.h"
#include "CharactorObject.h"
#include "BuildingObject.h"

MainScene::MainScene(const Type& tag) : Scene(tag)
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

	GameObject* obj = new BuildingObject(
		0, 0, 0, 50, 1, 1, 0, 1, GameObject::ObjectType::OBJECT_BUILDING);
	m_pBuildingList.push_back(obj);
	while(m_pCharactorList.size() < MAX_OBJECTS_COUNT / 2)
	{
		GameObject* obj = new CharactorObject(
			  (1 - 2 * (rand() % 2))*(rand() % CLIENT_WIDTH / 2.0)
			, (1 - 2 * (rand() % 2))*(rand() % CLIENT_HEIGHT / 2.0)
			, 0, 10, 0, 0, 1, 1, GameObject::ObjectType::OBJECT_CHARACTER);
		obj->SetDirection(
			(1 - 2 * (rand() % 2))*(rand() % 100 / 100.0),
			(1 - 2 * (rand() % 2))*(rand() % 100 / 100.0));
		obj->SetSpeed(100);
		m_pCharactorList.push_back(obj);
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

	if(m_pBuildingList.size() < MAX_OBJECTS_COUNT)
		for (auto& p : m_pBuildingList)
		{
			BuildingObject* building = static_cast<BuildingObject*>(p);
			GameObject* bullet = building->ShootBullet();
			if (bullet)
				m_pBulletList.push_back(bullet);
		}
	
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
}

void MainScene::PhysicsProcess(const double TimeElapsed)
{
	for (auto& p : m_pBuildingList)
		for (auto& q : m_pCharactorList)
		{
			if (p == q || (p->IsCollide() && q->IsCollide())) continue;
			if (p->GetBindingBox().CheckCollision(q->GetBindingBox()))
			{
				p->CollideWith(q);
				q->CollideWith(p);
			}
		}
	for (auto& p : m_pCharactorList)
		for (auto& q : m_pBulletList)
		{
			if (p == q || (p->IsCollide() && q->IsCollide())) continue;
			if (p->GetBindingBox().CheckCollision(q->GetBindingBox()))
			{
				p->CollideWith(q);
				q->CollideWith(p);
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
			if (m_pCharactorList.size() < MAX_OBJECTS_COUNT)
			{
				//for (int i = 0; i < 50; ++i)
				{
					GameObject* obj = new CharactorObject(
						x - CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2 - y, 0,
						10, 0, 0, 1, 1, GameObject::ObjectType::OBJECT_CHARACTER);
					obj->SetDirection(
						(1 - 2 * (rand() % 2))*(rand() % 100 / 100.0),
						(1 - 2 * (rand() % 2))*(rand() % 100 / 100.0));
					obj->SetSpeed(100);
					m_pCharactorList.push_back(obj);
				}
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
