#include "stdafx.h"
#include "BindingBox.h"


BindingBox::BindingBox() :
	m_vec3fPos({ 0, 0, 0 }), m_fSize(0.f), rcBindingBox({ 0, 0, 0, 0 })
{
}

BindingBox::BindingBox(const Vec3f& pos, const float size)
	: m_vec3fPos(pos), m_fSize(size), rcBindingBox({ 0, 0, 0, 0 })
{
	rcBindingBox = {
		  LONG(m_vec3fPos.x - m_fSize / 2.f)
		, LONG(m_vec3fPos.y + m_fSize / 2.f)
		, LONG(m_vec3fPos.x + m_fSize / 2.f)
		, LONG(m_vec3fPos.y - m_fSize / 2.f) };
}

BindingBox::BindingBox(const float x, const float y, const float size)
	: m_vec3fPos({ x, y, 0 }), m_fSize(size), rcBindingBox({ 0, 0, 0, 0 })
{
	rcBindingBox = {
		  LONG(m_vec3fPos.x - m_fSize / 2.f)
		, LONG(m_vec3fPos.y + m_fSize / 2.f)
		, LONG(m_vec3fPos.x + m_fSize / 2.f)
		, LONG(m_vec3fPos.y - m_fSize / 2.f) };
}

BindingBox::~BindingBox()
{
}

void BindingBox::SetPos(const Vec3f & pos)
{
	m_vec3fPos = pos;
	rcBindingBox = {
		  LONG(m_vec3fPos.x - m_fSize / 2.f)
		, LONG(m_vec3fPos.y + m_fSize / 2.f)
		, LONG(m_vec3fPos.x + m_fSize / 2.f)
		, LONG(m_vec3fPos.y - m_fSize / 2.f) };
}

void BindingBox::SetPos(const float x, const float y)
{
	m_vec3fPos = { x, y, 0 };
	rcBindingBox = {
		  LONG(m_vec3fPos.x - m_fSize / 2.f)
		, LONG(m_vec3fPos.y + m_fSize / 2.f)
		, LONG(m_vec3fPos.x + m_fSize / 2.f)
		, LONG(m_vec3fPos.y - m_fSize / 2.f) };
}

void BindingBox::SetSize(const float size)
{
	m_fSize = size;
	rcBindingBox = {
		  LONG(m_vec3fPos.x - m_fSize / 2.f)
		, LONG(m_vec3fPos.y + m_fSize / 2.f)
		, LONG(m_vec3fPos.x + m_fSize / 2.f)
		, LONG(m_vec3fPos.y - m_fSize / 2.f) };
}

bool BindingBox::CheckCollision(const BindingBox & otherBox) const
{
	if (rcBindingBox.left	> otherBox.rcBindingBox.right)	return false;
	if (rcBindingBox.right	< otherBox.rcBindingBox.left)	return false;
	if (rcBindingBox.bottom	> otherBox.rcBindingBox.top)	return false;
	if (rcBindingBox.top	< otherBox.rcBindingBox.bottom) return false;
	return true;
}
