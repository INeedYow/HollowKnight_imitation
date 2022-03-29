#include "framework.h"
#include "CGameManager.h"
#include "CPlayer.h"

CGameManager::CGameManager()
{
	m_pPlayer = nullptr;
	m_tPlayerInformation = {};
}

CGameManager::~CGameManager()
{

}

void CGameManager::updatePrevInfo()
{
	tPlayerPrevInfo prevInfo;
	prevInfo.fpPrevPos = m_pPlayer->getPos();
	m_pPlayer->updatePrevInfo(prevInfo);
}

void CGameManager::update()
{
	if (nullptr != m_pPlayer)
		updatePrevInfo();

}

void CGameManager::registPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

void CGameManager::unRegistPlayer()
{
	m_pPlayer = nullptr;
}

void CGameManager::savePlayerInfo()
{
	if (m_pPlayer == nullptr) return;
	m_tPlayerInformation = m_pPlayer->getPlayerInfo();
}

void CGameManager::loadPlayerInfo(CPlayer* pNewPlayer)
{
	if (m_pPlayer == nullptr) return;
	pNewPlayer->setPlayerInfo(m_tPlayerInformation);
}

CPlayer* CGameManager::getPlayer()
{
	return m_pPlayer;
}