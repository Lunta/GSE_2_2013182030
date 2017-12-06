#pragma once
#include "Sound.h"
class CSoundManager :
	public Sound
{
public:
	enum class SoundTag {
		  BackGround
		, Explosion
	};

public:
	CSoundManager();
	~CSoundManager();

	void Init();
	void PlaySoundByTag(SoundTag tag, bool bLoop, float volume);

private:
	std::map<SoundTag, int> m_lstSound;
};

