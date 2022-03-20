#include "framework.h"
#include "CState_Run.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Run::CState_Run(eSTATE_PLAYER state)
	: CState(state)
{
}

CState_Run::~CState_Run()
{
}

void CState_Run::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		pos.x -= info.fSpdX * fDT;
		getPlayer()->playAnim(L"Run");
	}
	else if (KEY_HOLD(VK_RIGHT))
	{
		chk |= SP_DIR;
		pos.x += info.fSpdX * fDT;
		getPlayer()->playAnim(L"Run");
	}
	else
	{
		changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
	}

	if (KEY_ON('Z'))
	{
		chk |= SP_JUMPHOLD;
		chk |= SP_AIR;
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

	else if (KEY_ON('A'))
	{
		if (getPlayer()->getPlayerInfo().uiSoul >= P_FIRESOUL)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FIRE);
		}
	}

	getPlayer()->setPos(pos);
}

void CState_Run::enter()
{
	getPlayer()->playAnim(L"Run");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Run::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
}
