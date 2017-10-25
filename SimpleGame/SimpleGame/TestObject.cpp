#include "stdafx.h"
#include "TestObject.h"
#include "Renderer.h"

TestObject::TestObject() 
	: GameObject()
{
}

TestObject::TestObject(
	  const Vec3f & pos
	, float size
	, const Vec4f & color)
	: GameObject(pos, size, color)
{
}

TestObject::TestObject(
	  float x, float y, float z
	, float size
	, float r, float g, float b, float a)
	: GameObject(x, y, z, size, r, g, b, a)
{
}

TestObject::~TestObject()
{
}

void TestObject::Update(const double TimeElapsed)
{
	m_vec3fPos += m_vec3fDirection * m_fSpeed * TimeElapsed;
	m_fLife -= TimeElapsed;
	m_fLifeTimer -= TimeElapsed;

	m_BindingBox.SetPos(m_vec3fPos);
	if (m_bIsCollision)
	{
		m_fCollisionTimer += TimeElapsed;
		if (m_fCollisionTimer > COLLISION_TIME)
		{
			m_bIsCollision = false;
			m_fCollisionTimer = 0.0f;
			m_vec4fColor = Vec4f{ 1, 1, 1, 1 };
		}
	}

	if (m_vec3fPos.x > CLIENT_WIDTH / 2 ||
		m_vec3fPos.x < -CLIENT_WIDTH / 2)
		m_vec3fDirection.x = -m_vec3fDirection.x;
	if (m_vec3fPos.y > CLIENT_HEIGHT / 2 ||
		m_vec3fPos.y < -CLIENT_HEIGHT / 2)
		m_vec3fDirection.y = -m_vec3fDirection.y;
}

void TestObject::Render(Renderer * pRenderer)
{
	// Renderer Test
	pRenderer->DrawSolidRect(
		m_vec3fPos.x, m_vec3fPos.y, m_vec3fPos.z, m_fSize, 
		m_vec4fColor.r, m_vec4fColor.g, m_vec4fColor.b, m_vec4fColor.a);
}

void TestObject::Collide()
{
	m_bIsCollision = true;
	m_fCollisionTimer = 0.0f;
	m_vec4fColor = Vec4f{ 1, 0, 0, 1 };
}
