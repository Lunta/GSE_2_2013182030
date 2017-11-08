#pragma once
#include "GameObject.h"

#define DEFAULT_ARROW_MAX_LIFE	10.0f
#define DEFAULT_ARROW_SPEED		100.0f

class ArrowObject : public GameObject
{
private:
	GameObject* m_pLaunchedBy;

public:
	ArrowObject(ObjectType tag);
	ArrowObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag);
	ArrowObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag);
	virtual ~ArrowObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);

	void SetLaunchedBy(GameObject* other);
	GameObject* GetLaunchedBy() const { return m_pLaunchedBy; }
};

