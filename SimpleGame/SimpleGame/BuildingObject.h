#pragma once
#include "GameObject.h"

#define DEFAULT_BUILDING_MAX_LIFE		500.0f
#define DEFAULT_BUILDING_SHOOT_DELAY	0.5f

class BuildingObject : public GameObject
{
private:
	float						m_fShootTimer;
	unsigned int				m_texture;
	std::list<GameObject*>		*m_BulletList;

public:
	BuildingObject(ObjectType tag = ObjectType::OBJECT_BUILDING);
	BuildingObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag = ObjectType::OBJECT_BUILDING);
	BuildingObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag = ObjectType::OBJECT_BUILDING);
	virtual ~BuildingObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);

	void SetBulletList(std::list<GameObject*>* bullet_list);

	void LoadTexture(Renderer * pRenderer, path texPath);
	GameObject* ShootBullet();
};

