#pragma once
#include "GameObject.h"

#define DEFAULT_CHARACTOR_MAX_LIFE		10.0f
#define DEFAULT_CHARACTOR_SPEED			100.0f
#define DEFAULT_CHARACTOR_SHOOT_DELAY	0.5f

class CharactorObject : public GameObject
{
private:
	float						m_fShootTimer;
	std::list<GameObject*>		*m_ArrowList;

public:
	CharactorObject(ObjectType tag = ObjectType::OBJECT_CHARACTER);
	CharactorObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag = ObjectType::OBJECT_CHARACTER);
	CharactorObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag = ObjectType::OBJECT_CHARACTER);
	virtual ~CharactorObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);

	void SetArrowList(std::list<GameObject*>* arrow_list);

	void ShootBullet();
};