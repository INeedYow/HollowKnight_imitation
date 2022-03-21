#include "framework.h"
#include "CState_Doublejump.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Doublejump::CState_Doublejump(eSTATE_PLAYER state)
	: CState(state)
{
	m_fTimer = 0.f;
	m_fAccel = 0.f;
}

CState_Doublejump::~CState_Doublejump()
{
}

void CState_Doublejump::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (chk & SP_JUMPHOLD)
	{	// Z 누르고 있는 동안은 타이머만 증가(중력 증가 X)
		m_fTimer += fDT;
		m_fAccel += 300 * fDT;
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

	if (info.fSpdY + m_fAccel < info.fGravity)
	{
		chk |= SP_GODOWN;
		changeAIState(getOwner(), eSTATE_PLAYER::FALL);
	}

	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		pos.x -= info.fSpdX * fDT;
		getPlayer()->playAnim(L"DoubleJump");
	}
	else if (KEY_HOLD(VK_RIGHT))
	{
		chk |= SP_DIR;
		pos.x += info.fSpdX * fDT;
		getPlayer()->playAnim(L"DoubleJump");
	}

	pos.y -= (info.fSpdY + m_fAccel - info.fGravity) * fDT;

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Doublejump::enter()
{
	getPlayer()->playAnim(L"DoubleJump");
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_GODOWN, false);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fGravity = 0.f;
	getPlayer()->setPlayerInfo(info);
	getPlayer()->setCheck(SP_JUMPHOLD, true);
	getPlayer()->setCheck(SP_DBJUMP, true);

	m_fTimer = 0.f;
	m_fAccel = 0.f;
}

void CState_Doublejump::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
	m_fTimer = 0.f;
	m_fAccel = 0.f;
}

void CState_Doublejump::printInfo(HDC hDC)
{
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);
	LPCWSTR	strInfo = L"DoubleJump";
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 120, strInfo, (int)wcslen(strInfo));
}
