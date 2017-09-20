#pragma once
#include "GameObject.h"

class TestObject : public GameObject
{
public:
	TestObject(Renderer * pRenderer);
	TestObject(Renderer * pRenderer, const Vec3f& pos, float size, const Vec4f& color);
	TestObject(Renderer * pRenderer, float x, float y, float z, float size, float r, float g, float b, float a);
	virtual ~TestObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render();
};

