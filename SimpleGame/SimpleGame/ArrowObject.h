#pragma once
#include "GameObject.h"

#define DEFAULT_ARROW_MAX_LIFE	10.0f
#define DEFAULT_ARROW_SPEED		100.0f
#define DEFAULT_ARROW_SIZE		4.0f

#define ARROW_TEAM_1_COLOR		Vec4f(0.5, 0.2, 0.7, 1)
#define ARROW_TEAM_2_COLOR		Vec4f(1, 1, 0, 1)

class ArrowObject : public GameObject
{
private:
	GameObject* m_pLaunchedBy;

public:
	ArrowObject(ObjectTeam team, ObjectType tag = ObjectType::OBJECT_ARROW);
	ArrowObject(
		const Vec3f& pos
		, float size
		, const Vec4f& color
		, ObjectTeam team
		, ObjectType tag);
	ArrowObject(
		float x, float y, float z, float size
		, float r, float g, float b, float a
		, ObjectTeam team
		, ObjectType tag);
	virtual ~ArrowObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);

	void SetLaunchedBy(GameObject* other);
	GameObject* GetLaunchedBy() const { return m_pLaunchedBy; }
};

