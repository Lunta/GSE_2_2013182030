#include "stdafx.h"
#include "GameObject.h"
#include "Renderer.h"


GameObject::GameObject(Renderer * pRenderer) :
	m_pRenderer(pRenderer),
	m_vec3fPos({ 0, 0, 0 }), 
	m_vec4fColor({ 0, 0, 0, 0 }), 
	m_fSize(0.0f)
{
}
GameObject::GameObject(Renderer * pRenderer, const Vec3f& pos, float size, const Vec4f& color) :
	m_pRenderer(pRenderer),
	m_vec3fPos(pos),
	m_vec4fColor(color),
	m_fSize(size)
{
}
GameObject::GameObject(Renderer * pRenderer, float x, float y, float z, float size, float r, float g, float b, float a) :
	m_pRenderer(pRenderer),
	m_vec3fPos({ x, y, z }),
	m_vec4fColor({ r, g, b, a }),
	m_fSize(size)
{
}
GameObject::~GameObject()
{
}

void GameObject::SetParameter(const Vec3f& pos, float size, const Vec4f& color)
{
	m_vec3fPos = pos;
	m_vec4fColor = color;
	m_fSize = size;
}

void GameObject::SetParameter(float x, float y, float z, float size, float r, float g, float b, float a)
{
	m_vec3fPos = { x, y, z };
	m_vec4fColor = { r, g, b, a };
	m_fSize = size;
}

void GameObject::SetPos(const Vec3f & pos)
{
	m_vec3fPos = pos;
}

void GameObject::SetPos(float x, float y, float z)
{
	m_vec3fPos = { x, y, z };
}

void GameObject::SetColor(const Vec4f & color)
{
	m_vec4fColor = color;
}

void GameObject::SetColor(float r, float g, float b, float a)
{
	m_vec4fColor = { r, g, b, a };
}

void GameObject::SetSize(float size)
{
	m_fSize = size;
}
