#include "framework.h"
#include "CState_Fire.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Fire::CState_Fire(eSTATE_PLAYER state)
	: CState(state)
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
			changeAIState(getOwner(), eSTATE_PLAYER::FALL);
		}
		else
		{
			changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
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

	// 중간에 상태 강제로 이탈되면 soul 결과값으로 바로 감소
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.uiSoul = m_uiResultSoul;
	getPlayer()->setPlayerInfo(info);
}

void CState_Fire::printInfo(HDC hDC)
{
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Fire";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
