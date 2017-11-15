#include "stdafx.h"
#include "ArrowObject.h"
#include "Renderer.h"

ArrowObject::ArrowObject(ObjectTeam team, ObjectType tag)
	: GameObject(team, tag)
	, m_pLaunchedBy(nullptr)
{
	m_fLife = DEFAULT_ARROW_MAX_LIFE;
	m_fSpeed = DEFAULT_ARROW_SPEED;
}
ArrowObject::ArrowObject(
	  const Vec3f & pos
	, float size
	, const Vec4f & color
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(pos, size, color, team, tag)
	, m_pLaunchedBy(nullptr)
{
	m_fLife = DEFAULT_ARROW_MAX_LIFE;
	m_fSpeed = DEFAULT_ARROW_SPEED;
}
ArrowObject::ArrowObject(
	  float x, float y, float z
	, float size
	, float r, float g, float b, float a
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(x, y, z, size, r, g, b, a, team, tag)
	, m_pLaunchedBy(nullptr)
{
	m_fLife = DEFAULT_ARROW_MAX_LIFE;
	m_fSpeed = DEFAULT_ARROW_SPEED;
}
ArrowObject::~ArrowObject()
{
}

void ArrowObject::Update(const double TimeElapsed)
{
	if (!m_bActive) return;
	m_vec3fPos += m_vec3fDirection * m_fSpeed * TimeElapsed;
	m_fLifeTimer -= TimeElapsed;

	m_BindingBox.SetPos(m_vec3fPos);
	if (m_bIsCollision)
	{
		m_fCollisionTimer += TimeElapsed;
		if (m_fCollisionTimer > COLLISION_TIME)
		{
			m_bIsCollision = false;
			m_fCollisionTimer = 0.0f;
			m_pTarget = nullptr;
		}
	}

	if (m_vec3fPos.x > CLIENT_WIDTH / 2 ||
		m_vec3fPos.x < -CLIENT_WIDTH / 2)
		m_vec3fDirection.x = -m_vec3fDirection.x;
	if (m_vec3fPos.y > CLIENT_HEIGHT / 2 ||
		m_vec3fPos.y < -CLIENT_HEIGHT / 2)
		m_vec3fDirection.y = -m_vec3fDirection.y;
}

void ArrowObject::Render(Renderer * pRenderer)
{
	if (!m_bActive) return;
	pRenderer->DrawSolidRect(
		m_vec3fPos.x, m_vec3fPos.y, m_vec3fPos.z, m_fSize, 
		m_vec4fColor.r, m_vec4fColor.g, m_vec4fColor.b, m_vec4fColor.a);
}

void ArrowObject::CollideWith(GameObject* other)
{
	if (!m_bActive) return;
	switch(other->GetTag())
	{
	case GameObject::ObjectType::OBJECT_CHARACTER:
	{
		if (m_pLaunchedBy == other) return;
		if (m_bIsCollision) return;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife = 0.0f;
		m_bActive = false;
	}
	case GameObject::ObjectType::OBJECT_BUILDING:
	{
		if (m_bIsCollision) return;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife = 0.0f;
		m_bActive = false;
	}
	}
}

void ArrowObject::SetLaunchedBy(GameObject * other)
{
	m_pLaunchedBy = other;
}
