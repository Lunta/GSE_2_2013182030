#include "stdafx.h"
#include "BuildingObject.h"
#include "Renderer.h"
#include "BulletObject.h"
#include "Framework.h"

BuildingObject::BuildingObject(ObjectTeam team, ObjectType tag)
	: GameObject(team, tag)
	, m_fShootTimer(0.f)
{
	m_fLife = DEFAULT_BUILDING_MAX_LIFE;
}
BuildingObject::BuildingObject(
	const Vec3f& pos
	, float size
	, const Vec4f& color
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(pos, size, color, team, tag)
	, m_fShootTimer(0.f)
{
	m_fLife = DEFAULT_BUILDING_MAX_LIFE;
}
BuildingObject::BuildingObject(
	float x, float y, float z, float size
	, float r, float g, float b, float a
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(x, y, z, size, r, g, b, a, team, tag)
	, m_fShootTimer(0.f)
{
	m_fLife = DEFAULT_BUILDING_MAX_LIFE;
}
BuildingObject::~BuildingObject()
{
	for (auto& p : *m_BulletList)
	{
		auto bullet = dynamic_cast<BulletObject*>(p);
		if (bullet)
		{
			if(this == bullet->GetLaunchedBy())
				p->SetLife(0.0f);
		}
	}
}

void BuildingObject::Update(const double TimeElapsed)
{
	if (!m_bActive) return;
	m_vec3fPos += m_vec3fDirection * m_fSpeed * TimeElapsed;
	m_BindingBox.SetPos(m_vec3fPos);
	m_fShootTimer += TimeElapsed;
	m_fLifeTimer -= TimeElapsed;
	if (m_fShootTimer > DEFAULT_BUILDING_SHOOT_DELAY && Length(m_vec3fDirection) > 0.1f)
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
}

void BuildingObject::Render(Renderer * pRenderer)
{
	if (!m_bActive) return;

	pRenderer->DrawTexturedRect(
		m_vec3fPos.x, m_vec3fPos.y, m_vec3fPos.z, m_fSize
		, m_vec4fColor.r, m_vec4fColor.g, m_vec4fColor.b, m_vec4fColor.a, m_iTexture
		, LEVEL_BUILDING);

	switch (m_TeamTag)
	{
	case ObjectTeam::OBJECT_TEAM_1:
		pRenderer->DrawSolidRectGauge(
			m_vec3fPos.x, m_vec3fPos.y + m_fSize * 0.5f, m_vec3fPos.z
			, OBJECT_GAUGE_WIDTH_FACTOR * m_fSize
			, OBJECT_GAUGE_HEIGHT_FACTOR * m_fSize
			, 1, 0, 0, 1
			, m_fLife / DEFAULT_BUILDING_MAX_LIFE
			, LEVEL_UNIT);
		
		break;
	case ObjectTeam::OBJECT_TEAM_2:
		pRenderer->DrawSolidRectGauge(
			m_vec3fPos.x, m_vec3fPos.y + m_fSize * 0.5f, m_vec3fPos.z
			, OBJECT_GAUGE_WIDTH_FACTOR * m_fSize
			, OBJECT_GAUGE_HEIGHT_FACTOR * m_fSize
			, 0, 0, 1, 1
			, m_fLife / DEFAULT_BUILDING_MAX_LIFE
			, LEVEL_UNIT);
		break;
	}
	pRenderer->DrawTextW(
		  m_vec3fPos.x + m_fSize * 0.5f, m_vec3fPos.y + m_fSize * 0.47f
		, GLUT_BITMAP_HELVETICA_10
		, 1, 1, 1
		, &std::to_string(static_cast<int>(m_fLife))[0]);
}

void BuildingObject::CollideWith(GameObject * other)
{
	if (!m_bActive) return;
	switch (other->GetTag())
	{
	case GameObject::ObjectType::OBJECT_CHARACTER:
	{
		if (m_bIsCollision) return;
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
		if (m_bIsCollision) return;
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
	case GameObject::ObjectType::OBJECT_BULLET:
	{
		if (m_bIsCollision) return;
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

void BuildingObject::SetBulletList(std::list<GameObject*>* bullet_list)
{
	m_BulletList = bullet_list;
}

void BuildingObject::ShootBullet()
{
	if (!m_BulletList) return;

	BulletObject* bullet = nullptr;
	switch (m_TeamTag)
	{
	case ObjectTeam::OBJECT_TEAM_1:
	{
		bullet = new BulletObject(
			m_vec3fPos
			, DEFAULT_BULLET_SIZE
			, BULLET_TEAM_1_COLOR
			, m_TeamTag
			, ObjectType::OBJECT_BULLET);
		break;
	}
		
	case ObjectTeam::OBJECT_TEAM_2:
	{
		bullet = new BulletObject(
			m_vec3fPos
			, DEFAULT_BULLET_SIZE
			, BULLET_TEAM_2_COLOR
			, m_TeamTag
			, ObjectType::OBJECT_BULLET);
		break;
	}
	}
	bullet->SetDirection(m_vec3fDirection);
	bullet->SetLaunchedBy(this);
	bullet->SetTexture(m_iBulletTexture);
	bullet->SetTextureSize({ 8, 3 });
	m_BulletList->push_back(bullet);
}
