#include "framework.h"
#include "CGameManager.h"
#include "CPlayer.h"

CGameManager::CGameManager()
{
	m_pPlayer = nullptr;
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

	// gamaMgr���� ������ �� �þ�� �߰��� ����
}

void CGameManager::registPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

void CGameManager::unRegistPlayer()
{
	m_pPlayer = nullptr;
}

CPlayer* CGameManager::getPlayer()
{
	return m_pPlayer;
}