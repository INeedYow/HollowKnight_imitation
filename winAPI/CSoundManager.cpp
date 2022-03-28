#include "framework.h"
#include "CSoundManager.h"
#include "CSound.h"

CSoundManager::CSoundManager()
{
	m_pSystem = nullptr;
}

CSoundManager::~CSoundManager()
{
	m_pSystem->release();
	m_pSystem->close();
}

System* CSoundManager::getSystem()
{
	return m_pSystem;
}

void CSoundManager::init()
{
	// 사운드 시스템 생성
	System_Create(&m_pSystem);
	assert(m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
}

void CSoundManager::update()
{
	m_pSystem->update();		// 매 프레임마다 업데이트 되어야 함.
}

void CSoundManager::addSound(wstring keyName, wstring filePath, bool bgm, bool loop)
{
	CSound* pSound;
	if (bgm)
	{
		pSound = CResourceManager::getInst()->loadBGM(keyName, filePath);
	}
	else
	{
		pSound = CResourceManager::getInst()->loadSound(keyName, filePath);
	}
	m_mapSound.insert(make_pair(keyName, pSound));
}

void CSoundManager::play(wstring keyName, float volume)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->play(volume);
}

void CSoundManager::stop(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->stop();
}

void CSoundManager::pause(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->pause();
}

void CSoundManager::resume(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->resume();
}

bool CSoundManager::isPlaySound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		return iter->second->isPlaying();
	return false;
}

bool CSoundManager::isPauseSound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		return iter->second->isPaused();
	return false;
}
