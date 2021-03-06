#pragma once
#include "GameObject.h"

#define DEFAULT_CHARACTOR_MAX_LIFE			100.0f
#define DEFAULT_CHARACTOR_SPEED				300.0f
#define DEFAULT_CHARACTOR_SHOOT_DELAY		1.0f
#define DEFAULT_CHARACTOR_SHOOT_RANGE		100.0f
#define DEFAULT_CHARACTOR_SIZE				30.0f

#define CHARACTOR_TEAM_1_COLOR				Vec4f(1, 0, 0, 1)
#define CHARACTOR_TEAM_2_COLOR				Vec4f(0, 0, 1, 1)

#define CHARACTOR_TEXTURE_PATH				"./Assets/player.png"
#define CHARACTOR_TEXTURE_ANIMATION_SPEED	8.f		// 초당 프레임
#define CHARACTOR_TEXTURE_DOWN				0
#define CHARACTOR_TEXTURE_LEFT				1
#define CHARACTOR_TEXTURE_RIGHT				2
#define CHARACTOR_TEXTURE_UP				3

class CharactorObject : public GameObject
{
private:
	float						m_fShootTimer;
	std::list<GameObject*>		*m_ArrowList;

public:
	CharactorObject(ObjectTeam team, ObjectType tag = ObjectType::OBJECT_CHARACTER);
	CharactorObject(
		const Vec3f& pos
		, float size
		, const Vec4f& color
		, ObjectTeam team
		, ObjectType tag = ObjectType::OBJECT_CHARACTER);
	CharactorObject(
		float x, float y, float z, float size
		, float r, float g, float b, float a
		, ObjectTeam team
		, ObjectType tag = ObjectType::OBJECT_CHARACTER);
	virtual ~CharactorObject();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer * pRenderer);

	virtual void CollideWith(GameObject* other);

	void SetArrowList(std::list<GameObject*>* arrow_list);

	void ShootBullet();
};