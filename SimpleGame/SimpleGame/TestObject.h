#pragma once
#include "GameObject.h"

#define COLLISION_TIME 0.1f

class TestObject : public GameObject
{
private:
	float m_fCollisionTimer;
public:
	TestObject();
	TestObject(const Vec3f& pos, float size, const Vec4f& color);
	TestObject(float x, float y, float z, float size, float r, float g, float b, float a);
	virtual ~TestObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);
};

