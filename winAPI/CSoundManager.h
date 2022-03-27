#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib,"FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSoundManager
{
	SINGLETON(CSoundManager);

private:
	map<wstring, CSound*> m_mapSound;	// 사운드들을 관리하기 위한 자료구조

	System* m_pSystem;					// 사운드 시스템

public:
	System* getSystem();

	void init();
	void update();

	void addSound(wstring keyName, wstring filePath, bool bgm = false, bool loop = false);
	void play(wstring keyName, float volume);
	void stop(wstring keyName);
	void pause(wstring keyName);
	void resume(wstring keyName);

	bool isPlaySound(wstring keyName);
	bool isPauseSound(wstring keyName);
};

