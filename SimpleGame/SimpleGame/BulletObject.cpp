#include "stdafx.h"
#include "Particle.h"
#include "BulletObject.h"

#include "Renderer.h"

BulletObject::BulletObject(ObjectTeam team, ObjectType tag)
	: GameObject(team, tag)
{
	m_fLife = DEFAULT_BULLET_MAX_LIFE;
	m_fSpeed = DEFAULT_BULLET_SPEED;
	m_pParticle = new Particle(m_vec3fPos, m_vec3fDirection);
}
BulletObject::BulletObject(
	const Vec3f & pos
	, float size
	, const Vec4f & color
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(pos, size, color, team, tag)
{
	m_fLife = DEFAULT_BULLET_MAX_LIFE;
	m_fSpeed = DEFAULT_BULLET_SPEED;
	m_pParticle = new Particle(m_vec3fPos, m_vec3fDirection);
}
BulletObject::BulletObject(
	float x, float y, float z
	, float size
	, float r, float g, float b, float a
	, ObjectTeam team
	, ObjectType tag)
	: GameObject(x, y, z, size, r, g, b, a, team, tag)
{
	m_fLife = DEFAULT_BULLET_MAX_LIFE;
	m_fSpeed = DEFAULT_BULLET_SPEED;
	m_pParticle = new Particle(m_vec3fPos, m_vec3fDirection);
}
BulletObject::~BulletObject()
{
	if (m_pParticle) delete m_pParticle;
}

void BulletObject::Update(const double TimeElapsed)
{
	if (!m_bActive) return;
	m_vec3fPos += m_vec3fDirection * m_fSpeed * TimeElapsed;
	m_fLifeTimer -= TimeElapsed;

	m_BindingBox.SetPos(m_vec3fPos);
	if (m_pParticle) {
		m_pParticle->SetPos(m_vec3fPos);
		m_pParticle->SetDirection(m_vec3fDirection);
		m_pParticle->Update(TimeElapsed);
		if (m_pParticle->IsDie())
		{
			delete m_pParticle;
			m_pParticle = nullptr;
		}
	}
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
		m_vec3fPos.x < -CLIENT_WIDTH / 2 ||
		m_vec3fPos.y > CLIENT_HEIGHT / 2 ||
		m_vec3fPos.y < -CLIENT_HEIGHT / 2)
		m_fLife = 0.0f;
}

void BulletObject::Render(Renderer * pRenderer)
{
	if (!m_bActive) return;
	pRenderer->DrawSolidRect(
		m_vec3fPos.x, m_vec3fPos.y, m_vec3fPos.z, m_fSize
		, m_vec4fColor.r, m_vec4fColor.g, m_vec4fColor.b, m_vec4fColor.a
		, LEVEL_PROJECTILE);
	if (m_pParticle) m_pParticle->Render(pRenderer);
}

void BulletObject::CollideWith(GameObject* other)
{
	if (!m_bActive) return;
	switch (other->GetTag())
	{
	case GameObject::ObjectType::OBJECT_CHARACTER:
	{
		if (m_pLaunchedBy == other) return;
		if (m_bIsCollision) break;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife = 0.0f;
		m_bActive = false;
		break;
	}
	case GameObject::ObjectType::OBJECT_BUILDING:
	{
		if (m_pLaunchedBy == other) return;
		if (m_bIsCollision) break;
		m_bIsCollision = true;
		m_fCollisionTimer = 0.0f;
		m_pTarget = other;
		m_fLife = 0.0f;
		m_bActive = false;
		break;
	}
	}
}

void BulletObject::LoadTexture(Renderer * pRenderer, char * path)
{
	m_iTexture = pRenderer->CreatePngTexture(path);
	if (m_pParticle) m_pParticle->LoadTexture(pRenderer, path);
}

void BulletObject::SetTexture(UINT textureID)
{
	m_iTexture = textureID;
	if (m_pParticle) m_pParticle->SetTexture(textureID);
}

void BulletObject::SetLaunchedBy(GameObject * other)
{
	m_pLaunchedBy = other;
}