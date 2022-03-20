#include "framework.h"
#include "CState_Jump.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Jump::CState_Jump(eSTATE_PLAYER state)
	: CState(state)
{
	m_fTimer = 0.f;
}

CState_Jump::~CState_Jump()
{
}

void CState_Jump::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (chk & SP_JUMPHOLD)
	{	// Z 누르고 있는 동안은 타이머만 증가(중력 증가 X)
		m_fTimer += fDT;
	}
	else
	{	// 중력 증가
		if (info.fGravity < P_GRAVMAX)
			info.fGravity += P_GRAV * fDT;
	}

	if (KEY_OFF('Z') || m_fTimer >= P_JUMPHOLDMAX)
	{	// Z 떼거나 점프 유지 최대시간 지나면
		chk &= ~(SP_JUMPHOLD);
	}

	if (info.fSpdY < info.fGravity)
	{
		chk |= SP_GODOWN;
		changeAIState(getOwner(), eSTATE_PLAYER::FALL);
	}

	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		pos.x -= info.fSpdX * fDT;
		getPlayer()->playAnim(L"Jump");
	}
	else if (KEY_HOLD(VK_RIGHT))
	{
		chk |= SP_DIR;
		pos.x += info.fSpdX * fDT;
		getPlayer()->playAnim(L"Jump");
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

	pos.y -= (info.fSpdY - info.fGravity) * fDT;

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Jump::enter()
{
	getPlayer()->playAnim(L"Jump");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Jump::exit()
{
	m_fTimer = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);
}
