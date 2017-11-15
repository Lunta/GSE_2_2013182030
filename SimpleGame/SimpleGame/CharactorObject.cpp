#include "stdafx.h"
#include "CharactorObject.h"
#include "Renderer.h"
#include "ArrowObject.h"

CharactorObject::CharactorObject(ObjectTeam team, ObjectType tag)
	: GameObject(team, tag)
	, m_fShootTimer(0.f)
{
	m_fLife = DEFAULT_CHARACTOR_MAX_LIFE;
	m_fSpeed = DEFAULT_CHARACTOR_SPEED;
}
CharactorObject::CharactorObject(
	const Vec3f& pos
	, float size
	, const Vec4f& color
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(pos, size, color, team, tag)
	, m_fShootTimer(0.f)
{
	m_fLife = DEFAULT_CHARACTOR_MAX_LIFE;
	m_fSpeed = DEFAULT_CHARACTOR_SPEED;
}
CharactorObject::CharactorObject(
	float x, float y, float z, float size
	, float r, float g, float b, float a
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(x, y, z, size, r, g, b, a, team, tag)
	, m_fShootTimer(0.f)
{
	m_fLife = DEFAULT_CHARACTOR_MAX_LIFE;
	m_fSpeed = DEFAULT_CHARACTOR_SPEED;
}
CharactorObject::~CharactorObject()
{
	for (auto& p : *m_ArrowList)
	{
		auto arrow = dynamic_cast<ArrowObject*>(p);
		if (arrow)
		{
			if (this == arrow->GetLaunchedBy())
				p->SetLife(0.0f);
		}
	}
}

void CharactorObject::Update(const double TimeElapsed)
{
	if (!m_bActive) return;
	m_vec3fPos += m_vec3fDirection * m_fSpeed * TimeElapsed;
	m_BindingBox.SetPos(m_vec3fPos);
	m_fLifeTimer -= TimeElapsed;
	m_fShootTimer += TimeElapsed;
	if (m_fShootTimer > DEFAULT_CHARACTOR_SHOOT_DELAY) 
	{
		m_fShootTimer = 0.f;
		ShootBullet();
	}

	if (m_bIsCollision)
	{
		m_fCollisionTimer += TimeElapsed;
		if (m_fCollisionTimer > COLLISION_TIME)
		{
			m_bIsCollision = false;
			m_fCollisionTimer = 0.0f;
			m_pTarget = nullptr;
			m_vec4fColor += Vec4f{ 0.1f, 0.1f, 0.1f, 0.0f };
		}
	}

	if (m_vec3fPos.x > CLIENT_WIDTH / 2 ||
		m_vec3fPos.x < -CLIENT_WIDTH / 2)
		m_vec3fDirection.x = -m_vec3fDirection.x;
	if (m_vec3fPos.y > CLIENT_HEIGHT / 2 ||
		m_vec3fPos.y < -CLIENT_HEIGHT / 2)
		m_vec3fDirection.y = -m_vec3fDirection.y;
}

void CharactorObject::Render(Renderer * pRenderer)
{
	if (!m_bActive) return;
	pRenderer->DrawSolidRect(
		m_vec3fPos.x, m_vec3fPos.y, m_vec3fPos.z, m_fSize,
		m_vec4fColor.r, m_vec4fColor.g, m_vec4fColor.b, m_vec4fColor.a);
}

void CharactorObject::CollideWith(GameObject* other)
{
	if (!m_bActive) return;
	switch (other->GetTag())
	{
	case GameObject::ObjectType::OBJECT_BUILDING:
	{
		if (m_bIsCollision) break;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife = 0.0f;
		m_bActive = false;
		break;
	}
	case GameObject::ObjectType::OBJECT_BULLET:
	{
		if (m_bIsCollision) break;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife -= other->GetLife();
		m_vec4fColor -= Vec4f{ 0.1f, 0.1f, 0.1f, 0.0f };
		if (m_fLife <= 0.0f)
		{
			m_fLife = 0.0f;
			m_bActive = false;
		}
		break;
	}
	case GameObject::ObjectType::OBJECT_ARROW:
	{
		if (this == dynamic_cast<ArrowObject*>(other)->GetLaunchedBy()) return;
		if (m_bIsCollision) break;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife -= other->GetLife();
		m_vec4fColor -= Vec4f{ 0.1f, 0.1f, 0.1f, 0.0f };
		if (m_fLife <= 0.0f)
		{
			m_fLife = 0.0f;
			m_bActive = false;
		}
		break;
	}
	}
}

void CharactorObject::SetArrowList(std::list<GameObject*>* arrow_list)
{
	m_ArrowList = arrow_list;
}

void CharactorObject::ShootBullet()
{
	if (!m_ArrowList) return;
	ArrowObject* bullet = nullptr;
	switch (m_TeamTag)
	{
	case ObjectTeam::OBJECT_TEAM_1:
		bullet = new ArrowObject(
			m_vec3fPos
			, DEFAULT_ARROW_SIZE
			, ARROW_TEAM_1_COLOR
			, m_TeamTag
			, ObjectType::OBJECT_ARROW);
		break;
	case ObjectTeam::OBJECT_TEAM_2:
		bullet = new ArrowObject(
			m_vec3fPos
			, DEFAULT_ARROW_SIZE
			, ARROW_TEAM_1_COLOR
			, m_TeamTag
			, ObjectType::OBJECT_ARROW);
		break;
	}
	bullet->SetDirection(
		(1 - 2 * (rand() % 2))*(rand() % 100 / 100.0),
		(1 - 2 * (rand() % 2))*(rand() % 100 / 100.0));
	bullet->SetLaunchedBy(this);
	m_ArrowList->push_back(bullet);
}
