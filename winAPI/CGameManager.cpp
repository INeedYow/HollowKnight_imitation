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

	m_fpSavePos = { -1.f, -1.f };
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

	if (m_fpSavePos != fPoint(-1.f, -1.f))
	{	// 씬 이동간 플레이어 시작위치가 바뀌어야 하는 경우 지정해주는 식으로 사용하려고
		m_pPlayer->setPos(m_fpSavePos);
		m_fpSavePos = fPoint(-1.f, -1.f);		// 1회성
	}
}

void CGameManager::savePos(fPoint pos)
{
	m_fpSavePos = pos;
}

fPoint CGameManager::loadPos()
{
	return m_fpSavePos;
}

CPlayer* CGameManager::getPlayer()
{
	return m_pPlayer;
}