#pragma once
class BindingBox
{
private:
	Vec3f	m_vec3fPos;
	float	m_fSize;

public:
	RECT	rcBindingBox;
	
public:
	BindingBox();
	BindingBox(const Vec3f& pos, const float size);
	BindingBox(const float x, const float y, const float size);
	~BindingBox();

	void SetPos(const Vec3f& pos);
	void SetPos(const float x, const float y);
	void SetSize(const float size);
	bool CheckCollision(const BindingBox& otherBox) const;
};

