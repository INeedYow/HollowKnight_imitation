#include "framework.h"
#include "CSound.h"

CSound::CSound()
{
	m_pSound = nullptr;
	m_pChannel = nullptr;
}

CSound::~CSound()
{
	stop();
	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}

void CSound::load(const wstring& strFilePath, bool bgm)
{
	char str[255];
	wcstombs_s(nullptr, str, strFilePath.c_str(), 255);

	if (bgm)
	{
		CSoundManager::getInst()->getSystem()->createStream(str, FMOD_LOOP_NORMAL, 0, &m_pSound);
	}
	else
	{
		CSoundManager::getInst()->getSystem()->createSound(str, FMOD_LOOP_OFF, 0, &m_pSound);
	}
}

void CSound::play(float volume)
{
	CSoundManager::getInst()->getSystem()->playSound(m_pSound, 0, false, &m_pChannel);
	m_pChannel->setVolume(volume);
	assert(m_pChannel);
}

void CSound::pause()
{
	assert(m_pChannel);
	m_pChannel->setPaused(true);
}

void CSound::stop()
{
	assert(m_pChannel);
	m_pChannel->stop();
}

void CSound::resume()
{
	assert(m_pChannel);
	m_pChannel->setPaused(true);
}

bool CSound::isPlaying()
{
	bool playing = false;
	assert(m_pChannel);
	m_pChannel->isPlaying(&playing);
	return playing;
}

bool CSound::isPaused()
{
	bool paused = false;
	assert(m_pChannel);
	m_pChannel->getPaused(&paused);
	return paused;
}

void CSound::setLoop(bool loop)
{
	if (loop)
	{
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		m_pSound->setMode(FMOD_LOOP_OFF);
	}
}