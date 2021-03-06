#pragma once
#include <winnt.h>
#include "CPlayer.h"

class CPlayer;
struct tPlayerInfo;

class CGameManager
{
	SINGLETON(CGameManager);

private:
	CPlayer*	m_pPlayer;						// 보스, 적등이 플레이어 정보 필요할 때 쓰기 위해
	tPlayerInfo m_tPlayerInformation;			// 씬 이동 시 플레이어 정보 보존하기 위해
	fPoint*		m_pStartPos;					// 맵에서 플레이어 시작 위치 (동적할당해서 받기위해 포인터로)

private:
	void updatePrevInfo();

public:
	void update();

	void registPlayer(CPlayer* pPlayer);
	void unRegistPlayer();

	void savePlayerInfo();						// 씬 넘어가기 전에 exit에서 플레이어 인포 저장
	void loadPlayerInfo(CPlayer* pNewPlayer);	// 씬 넘어가서 enter에서 플레이어 생성하며 복사

	void setStartPos(fPoint* pos);
	fPoint getStartPos();

	CPlayer* getPlayer();
};