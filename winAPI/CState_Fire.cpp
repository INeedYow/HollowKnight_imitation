#include "framework.h"
#include "CState_Fire.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Fire::CState_Fire(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fAttackDelay = 0.f;

	m_fSoul = 0.f;
	m_uiResultSoul = 0;
	m_fDecreaseSpd = (float)P_FIRESOUL / (float)P_FIREDELAY;
}

CState_Fire::~CState_Fire()
{
}

void CState_Fire::update(UINT& chk)
{
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;
	m_fSoul -= m_fDecreaseSpd * fDT;

	if (m_fAttackDelay > (float)P_ATTDELAY)
	{
		if (chk & SP_AIR)
		{
			changeMyState(getOwner(), eSTATE_PLAYER::FALL);
		}
		else
		{
			changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
		}
	}

	info.uiSoul = (int)m_fSoul;
	getPlayer()->setPlayerInfo(info);
}

void CState_Fire::enter()
{
	m_uiResultSoul = getPlayer()->getPlayerInfo().uiSoul - P_FIRESOUL;
	m_fSoul = (float)(getPlayer()->getPlayerInfo().uiSoul);

	getPlayer()->createMissile();

	getPlayer()->playAnim(L"Fire");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Fire::exit()
{
	m_fAttackDelay = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);

	// �߰��� ���� ������ ��Ż�Ǹ� soul ��������� �ٷ� ����
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.uiSoul = m_uiResultSoul;
	getPlayer()->setPlayerInfo(info);
}

void CState_Fire::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Fire";
	wchar_t bufDelay[255] = {};

	swprintf_s(bufDelay, L"Delay = %.1f", m_fAttackDelay);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDelay, (int)wcslen(bufDelay));
		
}
