#include "stdafx.h"
#include "BindingBox.h"

BindingBox::BindingBox() 
	: m_vec3fPos({ 0, 0, 0 })
	, m_fSize(0.f)
	, rc({ 0, 0, 0, 0 })
{
}
BindingBox::BindingBox(const Vec3f& pos, const float size)
	: m_vec3fPos(pos)
	, m_fSize(size)
{
	UpdateBox();
}
BindingBox::BindingBox(const float x, const float y, const float size)
	: m_vec3fPos({ x, y, 0 })
	, m_fSize(size)
{
	UpdateBox();
}
BindingBox::~BindingBox()
{
}

void BindingBox::SetPos(const Vec3f & pos)
{
	m_vec3fPos = pos;
	UpdateBox();
}
void BindingBox::SetPos(const float x, const float y)
{
	m_vec3fPos = { x, y, 0 };
	UpdateBox();
}
void BindingBox::SetSize(const float size)
{
	m_fSize = size;
	UpdateBox();
}

void BindingBox::UpdateBox()
{
	rc = {
		LONG(m_vec3fPos.x - m_fSize / 2.f)
		, LONG(m_vec3fPos.y + m_fSize / 2.f)
		, LONG(m_vec3fPos.x + m_fSize / 2.f)
		, LONG(m_vec3fPos.y - m_fSize / 2.f) };
}

bool BindingBox::CheckCollision(const BindingBox & otherBox) const
{
	if (rc.left	> otherBox.rc.right)	return false;
	if (rc.right	< otherBox.rc.left)	return false;
	if (rc.bottom	> otherBox.rc.top)	return false;
	if (rc.top	< otherBox.rc.bottom) return false;
	return true;
}
