#include "framework.h"
#include "CState_Idle.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Idle::CState_Idle(eSTATE_PLAYER state)
	: CState(state)
{
	m_fTimer = 0.f;
}

CState_Idle::~CState_Idle()
{
}

// TODO getOwner() 두 단계 최선인가
void CState_Idle::update(UINT& chk)
{
	// jump enter에서 pos.y--해주면 될듯?
	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		changeAIState(getOwner(), eSTATE_PLAYER::RUN);
	}

	else if (KEY_HOLD(VK_RIGHT))
	{
		chk |= SP_DIR;
		changeAIState(getOwner(), eSTATE_PLAYER::RUN);
	}
	
	else if (KEY_ON('Z'))
	{
		changeAIState(getOwner(), eSTATE_PLAYER::JUMP);
	}
	
	else if (KEY_ON('X'))
	{
		if (KEY_HOLD(VK_UP))
		{
			changeAIState(getOwner(), eSTATE_PLAYER::UPSLASH);
		}
		else
		{
			changeAIState(getOwner(), eSTATE_PLAYER::SLASH1);
		}
	}

	else if (KEY_ON('C'))
	{
		changeAIState(getOwner(), eSTATE_PLAYER::DASH);
	}

	if (KEY_HOLD('A'))
	{
		m_fTimer += fDT;

		if (m_fTimer >= 0.5f)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FOCUS);
		}
	}
	
	else if (KEY_OFF('A'))
	{
		if (getPlayer()->getPlayerInfo().uiSoul >= P_FIRESOUL)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FIRE);
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
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);
	LPCWSTR	strInfo = L"Idle";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
