#pragma once
#include "BindingBox.h"

#define DEFAULT_MAX_LIFE	100.0f
#define DEFAULT_LIFE_TIME	10000.0f
#define COLLISION_TIME		0.1f

class Renderer;

class GameObject
{
public:
	enum class ObjectType {
		OBJECT_BUILDING = 0
		, OBJECT_CHARACTER
		, OBJECT_BULLET
		, OBJECT_ARROW
	};

protected:
	ObjectType			m_Tag;
	bool				m_bActive;

	Vec3f				m_vec3fPos;
	Vec4f				m_vec4fColor;
	float				m_fSize;

	Vec3f				m_vec3fDirection;
	float				m_fSpeed;

	BindingBox			m_BindingBox;
	GameObject			*m_pTarget;
	bool				m_bIsCollision;

	float				m_fLife;
	float				m_fLifeTimer;
	float				m_fCollisionTimer;

public:
	GameObject(ObjectType tag);
	GameObject(const Vec3f& pos, float size, const Vec4f& color, ObjectType tag);
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a, ObjectType tag);
	virtual ~GameObject();

	virtual void Update(const double TimeElapsed) = 0;
	virtual void Render(Renderer* pRenderer) = 0;

	virtual void CollideWith(GameObject* other) = 0;

	void Awake() { m_bActive = true; };
	void Sleep() { m_bActive = false; };

	void SetParameter(const Vec3f& pos, float size, const Vec4f& color);
	void SetParameter(float x, float y, float z, float size, float r, float g, float b, float a);
	void SetPos(const Vec3f& pos);
	void SetPos(float x, float y, float z);
	void SetColor(const Vec4f& color);
	void SetColor(float r, float g, float b, float a);
	void SetSize(float size);
	void SetDirection(const Vec3f& direction);
	void SetDirection(float x, float y, float z = 0);
	void SetSpeed(float speed);
	void SetLife(float life);
	void SetLifeTime(float life_time);

	const ObjectType&	GetTag()		const { return m_Tag; }
	const Vec3f&		GetPos()		const { return m_vec3fPos; }
	float				GetSize()		const { return m_fSize; }
	float				GetLife()		const { return m_fLife; }
	const BindingBox&	GetBindingBox() const { return m_BindingBox; }

	bool IsActive() const { return m_bActive; }
	bool IsCollide() const { return m_bIsCollision; }
	bool IsDie() const {
		return (m_fLifeTimer <= 0.0f || m_fLife <= 0.0f); }
};



