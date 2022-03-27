#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib,"FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSoundManager
{
	SINGLETON(CSoundManager);

private:
	map<wstring, CSound*> m_mapSound;	// ������� �����ϱ� ���� �ڷᱸ��

	System* m_pSystem;					// ���� �ý���

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

