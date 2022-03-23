#include "framework.h"
#include "CState_Idle.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Idle::CState_Idle(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fTimer = 0.f;
}

CState_Idle::~CState_Idle()
{
}

// TODO getOwner() 두 단계 최선인가
void CState_Idle::update(UINT& chk)
{
	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		changeMyState(getOwner(), eSTATE_PLAYER::RUN);
	}

	else if (KEY_HOLD(VK_RIGHT))
	{
		chk |= SP_DIR;
		changeMyState(getOwner(), eSTATE_PLAYER::RUN);
	}
	
	else if (KEY_ON('Z'))
	{
		changeMyState(getOwner(), eSTATE_PLAYER::JUMP);
	}
	
	else if (KEY_ON('X'))
	{
		if (KEY_HOLD(VK_UP))
		{
			changeMyState(getOwner(), eSTATE_PLAYER::UPSLASH);
		}
		else
		{
			changeMyState(getOwner(), eSTATE_PLAYER::SLASH1);
		}
	}

	else if (KEY_ON('C'))
	{
		changeMyState(getOwner(), eSTATE_PLAYER::DASH);
	}

	if (KEY_HOLD('A'))
	{
		m_fTimer += fDT;

		if (m_fTimer >= 0.5f)
		{
			changeMyState(getOwner(), eSTATE_PLAYER::FOCUS);
		}
	}
	
	else if (KEY_OFF('A'))
	{
		if (getPlayer()->getPlayerInfo().uiSoul >= P_FIRESOUL)
		{
			changeMyState(getOwner(), eSTATE_PLAYER::FIRE);
		}
	}
}

void CState_Idle::enter()
{
	getPlayer()->playAnim(L"Idle");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Idle::exit()
{
	m_fTimer = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);
}

void CState_Idle::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Idle";

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
}
