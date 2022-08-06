#include "framework.h"
#include "CGameManager.h"
#include "CPlayer.h"

CGameManager::CGameManager()
{
	m_pPlayer = nullptr;
	m_tPlayerInformation = {};
	m_tPlayerInformation.uiHP = 5;
	m_tPlayerInformation.fSpdX = (float)P_SPDX;
	m_tPlayerInformation.fGravity = (float)P_GRAV;
	m_tPlayerInformation.fKnockBackSpd = P_KB_SPD;

	m_pEnterPos = nullptr;
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

fPoint prevPos = {};

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
	m_tPlayerInformation.iBottomCnt = 0;				// 맵 이동시 이전 BottomCnt는 가져갈 필요 없음 
}

void CGameManager::loadPlayerInfo(CPlayer* pNewPlayer)
{
	if (m_pPlayer == nullptr) return;
	
	pNewPlayer->setPlayerInfo(m_tPlayerInformation);

	if (nullptr != m_pEnterPos)
	{	// 시작위치 저장된 곳으로 해주고 delete
		pNewPlayer->setPos(*m_pEnterPos);	
		delete m_pEnterPos;
	}
}

void CGameManager::setEnterPos(fPoint* pos)
{
	m_pEnterPos = pos;
}

CPlayer* CGameManager::getPlayer()
{
	return m_pPlayer;
}