#include "stdafx.h"
#include "Renderer.h"
#include "Particle.h"


Particle::Particle(const Vec3f& pos, const Vec3f& direction, float size)
	: GameObject(GameObject::ObjectTeam::OBJECT_TEAM_NONE, GameObject::ObjectType::OBJECT_PARTICLE)
	, m_fParticleLifeTimer(0)
{
	m_vec3fPos = pos;
	m_vec3fDirection = direction;
	m_fSize = size;
}
Particle::~Particle()
{
}

void Particle::Update(const double TimeElapsed)
{
	m_fParticleLifeTimer += TimeElapsed;
}

void Particle::Render(Renderer * pRenderer)
{
	pRenderer->DrawParticle(
		m_vec3fPos.x
		, m_vec3fPos.y
		, m_vec3fPos.z
		, m_fSize * 10
		, 1, 1, 1, 1.f - (m_fParticleLifeTimer / PARTICLE_LIFE_TIME)
		, -m_vec3fDirection.x
		, -m_vec3fDirection.y
		, m_iTexture, m_fParticleLifeTimer, LEVEL_PARTICLE);
}
