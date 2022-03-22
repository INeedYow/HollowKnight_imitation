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
		info.fSpdY -= info.fGravity * fDT;

		if (info.fSpdY < 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;

		/*if (info.fGravity < P_GRAVMAX)
			info.fGravity += P_GRAV * fDT;*/
	}

	if (KEY_OFF('Z') || m_fTimer >= P_JUMPHOLDMAX)
	{	// Z 떼거나 점프 유지 최대시간 지나면
		chk &= ~(SP_JUMPHOLD);
	}

	//if (info.fSpdY < info.fGravity)
	if (info.fSpdY < 0.f)
	{
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

	else if (KEY_ON('C'))
	{
		changeAIState(getOwner(), eSTATE_PLAYER::DASH);
	}

	else if (KEY_ON('A'))
	{
		if (info.uiSoul >= P_FIRESOUL)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FIRE);
		}
	}

	pos.y -= (info.fSpdY /*- info.fGravity*/) * fDT;

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Jump::enter()
{
	getPlayer()->playAnim(L"Jump");
	getPlayer()->setCheck(SP_STOPANIM, true);

	getPlayer()->setCheck(SP_JUMPHOLD, true);
	getPlayer()->setCheck(SP_AIR, true);
	getPlayer()->setCheck(SP_DBJUMP, false);
	getPlayer()->setCheck(SP_GODOWN, false);

	// 
	//getPlayer()->setCheck(SP_GOUP, true);
	//fPoint pos = getPlayer()->getPos();
	//pos.y -= 1;
	//getPlayer()->setPos(pos);

	// 점프속도
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (getPlayer()->isCheck(SP_DWSLASH))
		info.fSpdY = (float)P_SPDY / 3.f;
	else
		info.fSpdY = (float)P_SPDY;

	getPlayer()->setPlayerInfo(info);
}

void CState_Jump::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);

	getPlayer()->setCheck(SP_JUMPHOLD, false);
	getPlayer()->setCheck(SP_DWSLASH, false);
	m_fTimer = 0.f;
}

void CState_Jump::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC18);
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Jump";

	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
