#pragma once
#include <winnt.h>
#include "CPlayer.h"

class CPlayer;
struct tPlayerInfo;

class CGameManager
{
	SINGLETON(CGameManager);

private:
	CPlayer*	m_pPlayer;						// ����, ������ �÷��̾� ���� �ʿ��� �� ���� ����
	tPlayerInfo m_tPlayerInformation;			// �� �̵� �� �÷��̾� ���� �����ϱ� ����
	fPoint		m_fpSavePos;					// ��ġ����(1ȸ������)

private:
	void updatePrevInfo();

public:
	void update();

	void registPlayer(CPlayer* pPlayer);
	void unRegistPlayer();

	void savePlayerInfo();						// �� �Ѿ�� ���� exit���� �÷��̾� ���� ����
	void loadPlayerInfo(CPlayer* pNewPlayer);	// �� �Ѿ�� enter���� �÷��̾� �����ϸ� ����

	void savePos(fPoint pos = fPoint(-1.f, -1.f));
	fPoint loadPos();

	CPlayer* getPlayer();
};