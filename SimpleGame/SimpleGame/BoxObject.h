#pragma once
#include "GameObject.h"

class BoxObject : public GameObject
{
private:

public:
	BoxObject(ObjectType tag);
	BoxObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag);
	BoxObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag);
	virtual ~BoxObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);
};

