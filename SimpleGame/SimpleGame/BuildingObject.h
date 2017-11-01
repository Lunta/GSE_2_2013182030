#pragma once
#include "GameObject.h"

#define DEFAULT_BUILDING_MAX_LIFE	100.0f
#define DEFAULT_SHOOT_DELAY			0.5f

class BuildingObject : public GameObject
{
private:
	float				m_fShootTimer;

public:
	BuildingObject(ObjectType tag = ObjectType::OBJECT_BUILDING);
	BuildingObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag = ObjectType::OBJECT_BUILDING);
	BuildingObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag = ObjectType::OBJECT_BUILDING);
	virtual ~BuildingObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);

	GameObject* ShootBullet();
};

