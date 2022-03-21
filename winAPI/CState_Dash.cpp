#include "framework.h"
#include "CState_Dash.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Dash::CState_Dash(eSTATE_PLAYER state)
	: CState(state)
{
	m_fDura = 0.f;
	m_fSpd = 0.f;
	m_fDecel = 0.f;
}

CState_Dash::~CState_Dash()
{
}

// TODO dash 연속사용 제어
void CState_Dash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fDura -= fDT;

	if (m_fDura < 0.f)
	{
		if (chk & SP_AIR)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FALL);
		}
		else
		{
			changeAIState(getOwner(), eSTATE_PLAYER::DASH2IDLE);
		}
	}
	else if (m_fDura < 0.1f)
	{
		m_fDecel += 5000 * fDT;

		if (m_fDecel > m_fSpd)
			m_fDecel = m_fSpd;
	}

	if (chk & SP_DIR)
	{
		pos.x += (m_fSpd - m_fDecel)  * fDT;
	}
	else
	{
		pos.x -= (m_fSpd - m_fDecel) * fDT;
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

// TODO 현재
// noDmg true 해놔도 player update()에서 timer 재서 SP_NODMG 꺼버림
void CState_Dash::enter()
{
	getPlayer()->playAnim(L"Dash");
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_NODMG, true);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fNoDmgTimer += 0.5f;
	getPlayer()->setPlayerInfo(info);

	m_fDura = 0.35f;
	m_fSpd = 1100.f;
	m_fDecel = 0.f;
}

void CState_Dash::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);

	m_fDecel = 0.f;
	m_fDura = 0.f;
}

void CState_Dash::printInfo(HDC hDC)
{
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);
	LPCWSTR	strInfo = L"Dash";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
