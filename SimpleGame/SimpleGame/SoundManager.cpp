#include "stdafx.h"
#include "SoundManager.h"


CSoundManager::CSoundManager()
	: Sound()
{
}
CSoundManager::~CSoundManager()
{
	for (auto& p : m_lstSound)
		DeleteSound(p.second);
	m_lstSound.clear();
}

void CSoundManager::Init()
{
	m_lstSound.insert(std::make_pair<SoundTag, int>(SoundTag::BackGround, CreateSound("./Dependencies/SoundSamples/MF-W-90.XM")));
	m_lstSound.insert(std::make_pair<SoundTag, int>(SoundTag::Explosion, CreateSound("./Dependencies/SoundSamples/explosion.wav")));
}

void CSoundManager::PlaySoundByTag(SoundTag tag, bool bLoop, float volume)
{
	PlaySound(m_lstSound.find(tag)->second, bLoop, volume);
}
