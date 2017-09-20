#include "stdafx.h"
#include "TestObject.h"
#include "Renderer.h"


TestObject::TestObject(Renderer * pRenderer) :
	GameObject(pRenderer)
{
}

TestObject::TestObject(Renderer * pRenderer, const Vec3f & pos, float size, const Vec4f & color) :
	GameObject(pRenderer, pos, size, color)
{
}

TestObject::TestObject(Renderer * pRenderer, float x, float y, float z, float size, float r, float g, float b, float a) :
	GameObject(pRenderer, x, y, z, size, r, g, b, a)
{
}

TestObject::~TestObject()
{
}

void TestObject::Update(const double TimeElapsed)
{
}

void TestObject::Render()
{
	// Renderer Test
	m_pRenderer->DrawSolidRect(
		m_vec3fPos.x, m_vec3fPos.y, m_vec3fPos.z, m_fSize, 
		m_vec4fColor.r, m_vec4fColor.g, m_vec4fColor.b, m_vec4fColor.a);
}
