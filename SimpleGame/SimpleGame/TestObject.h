#pragma once
#include "GameObject.h"



class TestObject : public GameObject
{
private:

public:
	TestObject();
	TestObject(const Vec3f& pos, float size, const Vec4f& color);
	TestObject(float x, float y, float z, float size, float r, float g, float b, float a);
	virtual ~TestObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void Collide();
};

