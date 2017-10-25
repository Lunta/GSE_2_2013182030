#pragma once
#include "GameObject.h"

class BoxObject : public GameObject
{
private:

public:
	BoxObject();
	BoxObject(const Vec3f& pos, float size, const Vec4f& color);
	BoxObject(float x, float y, float z, float size, float r, float g, float b, float a);
	virtual ~BoxObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void Collide();
};

