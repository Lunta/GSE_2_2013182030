#pragma once
#include "GameObject.h"

#define PARTICLE_LIFE_TIME 1.0f

class Particle : public GameObject
{
private:
	float					m_fParticleLifeTimer;
public:
	Particle(const Vec3f& pos, const Vec3f& direction, float size = 1.f);
	virtual ~Particle();

	virtual void Update(const double TimeElapsed);
	virtual void Render(Renderer* pRenderer);

	virtual void CollideWith(GameObject* other) {}

	virtual bool IsDie() const { return m_fParticleLifeTimer > PARTICLE_LIFE_TIME; }
};

