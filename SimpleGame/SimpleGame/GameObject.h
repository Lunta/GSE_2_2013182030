#pragma once
#include "BindingBox.h"

#define DEFAULT_MAX_LIFE	5.0f
#define DEFAULT_LIFE_TIME	10000.0f
#define COLLISION_TIME		0.1f

class Renderer;

class GameObject
{
protected:
	Vec3f				m_vec3fPos;
	Vec4f				m_vec4fColor;
	float				m_fSize;

	Vec3f				m_vec3fDirection;
	float				m_fSpeed;

	BindingBox			m_BindingBox;
	bool				m_bIsCollision;

	float				m_fLife;
	float				m_fLifeTimer;
	float				m_fCollisionTimer;

public:
	GameObject();
	GameObject(const Vec3f& pos, float size, const Vec4f& color);
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a);
	virtual ~GameObject();

	virtual void Update(const double TimeElapsed) = 0;
	virtual void Render(Renderer* pRenderer) = 0;

	virtual void Collide();

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

	const Vec3f&		GetPos() const { return m_vec3fPos; }
	const float&		GetSize() const { return m_fSize; }
	const BindingBox&	GetBindingBox() const { return m_BindingBox; }

	bool IsCollide() const { return m_bIsCollision; }
	bool IsDie() const {
		return (m_fLifeTimer <= 0.0f || m_fLife <= 0.0f); }
};



