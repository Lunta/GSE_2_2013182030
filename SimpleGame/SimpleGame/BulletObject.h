#pragma once
#include "GameObject.h"

#define DEFAULT_BULLET_MAX_LIFE		20.0f
#define DEFAULT_BULLET_SPEED		300.0f

class BulletObject : public GameObject
{
private:

public:
	BulletObject(ObjectType tag);
	BulletObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag);
	BulletObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag);
	virtual ~BulletObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);
};
