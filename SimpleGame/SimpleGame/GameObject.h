#pragma once
class Renderer;

class GameObject
{
protected:
	Vec3f		m_vec3fPos;
	Vec4f		m_vec4fColor;
	float		m_fSize;

	Vec3f		m_vec3fDirection;
	float		m_fSpeed;

	bool		m_bIsCollision;

public:
	GameObject();
	GameObject(const Vec3f& pos, float size, const Vec4f& color);
	GameObject(float x, float y, float z, float size, float r, float g, float b, float a);
	virtual ~GameObject();

	virtual void Update(const double TimeElapsed) = 0;
	virtual void Render(Renderer* pRenderer) = 0;

	void Collide();

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

	const Vec3f& GetPos() const { return m_vec3fPos; }
	const float& GetSize() const { return m_fSize; }

	bool IsCollide() const { return m_bIsCollision; }
};



