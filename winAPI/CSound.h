#pragma once
#include "FMOD/inc/fmod.hpp"
#include "CResource.h"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSound : public CResource
{
	Sound*		m_pSound;
	Channel*	m_pChannel;

public:
	CSound();
	~CSound();

	void play(float volume);
	void stop();
	void pause();
	void resume();

	bool isPlaying();
	bool isPaused();

	void setLoop(bool loop);

	void load(const wstring& strRelativePath, bool bgm);

};

