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

	// sound 저장
	CSoundManager::getInst()->addSound(L"bgm_stg1", L"sound\\bgm\\Dirtmouth1.wav", true);
	CSoundManager::getInst()->addSound(L"bgm_stage3", L"sound\\bgm\\Boss_Battle.wav", true);

	CSoundManager::getInst()->addSound(L"markoth_cast1", L"sound\\boss\\Markoth_cast_01.wav");
	CSoundManager::getInst()->addSound(L"markoth_cast2", L"sound\\boss\\Markoth_cast_02.wav");
	CSoundManager::getInst()->addSound(L"markoth_cast3", L"sound\\boss\\Markoth_cast_03.wav");
	CSoundManager::getInst()->addSound(L"markoth_cast4", L"sound\\boss\\Markoth_cast_04.wav");
	CSoundManager::getInst()->addSound(L"markoth_death", L"sound\\boss\\Markoth_Death.wav");
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
