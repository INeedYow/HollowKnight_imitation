#include "framework.h"
#include "CState_Fall.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Fall::CState_Fall(eSTATE_PLAYER state)
	: CState(state)
{
}

CState_Fall::~CState_Fall()
{
}

void CState_Fall::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (!(chk & SP_AIR))
	{
		changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
	}

	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		pos.x -= info.fSpdX * fDT;
		getPlayer()->playAnim(L"Fall");
	}
	else if (KEY_HOLD(VK_RIGHT))
	{
		chk |= SP_DIR;
		pos.x += info.fSpdX * fDT;
		getPlayer()->playAnim(L"Fall");
	}

	if (KEY_ON('X'))
	{
		if (KEY_HOLD(VK_UP))
		{
			changeAIState(getOwner(), eSTATE_PLAYER::UPSLASH);
		}
		else if (KEY_HOLD(VK_DOWN))
		{
			changeAIState(getOwner(), eSTATE_PLAYER::DOWNSLASH);
		}
		else
		{
			changeAIState(getOwner(), eSTATE_PLAYER::SLASH1);
		}
	}

	else if (KEY_ON('A'))
	{
		if (info.uiSoul >= P_FIRESOUL)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FIRE);
		}
	}

	if (info.fGravity < P_GRAVMAX)
		info.fGravity += P_GRAV * fDT;

	pos.y -= (info.fSpdY - info.fGravity) * fDT;
		
	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Fall::enter()
{
	getPlayer()->playAnim(L"Fall");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Fall::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
}
