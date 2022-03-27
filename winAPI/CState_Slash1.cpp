#include "framework.h"
#include "CState_Slash1.h"
#include "CStatus.h"
#include "CPlayer.h"

#include "CEffect.h"

CState_Slash1::CState_Slash1(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fAttackDelay = 0.f;
}

CState_Slash1::~CState_Slash1()
{
}

void CState_Slash1::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	if (chk & SP_AIR)
	{	// 공중에서 공격할 때 중력적용
		info.fSpdY -= info.fGravity * fDT;

		if (info.fSpdY <= 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;

		pos.y -= info.fSpdY * fDT;
	}
	else
	{
		// TODO Slash2
	}
	
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

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Slash1::enter()
{
	getPlayer()->firstSlash();
	getPlayer()->playAnim(L"Slash1");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Slash1::exit()
{
	m_fAttackDelay = 0.f;
	getPlayer()->setCheck(SP_STOPANIM, false);
}

void CState_Slash1::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Slash1";
	wchar_t bufDelay[255] = {};

	swprintf_s(bufDelay, L"Delay = %.1f", m_fAttackDelay);
	
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDelay, (int)wcslen(bufDelay));

	if (getPlayer()->isCheck(SP_AIR))
	{
		tPlayerInfo info = getPlayer()->getPlayerInfo();
		wchar_t bufSpdY[255] = {};
		swprintf_s(bufSpdY, L"SpdY = %.1f", info.fSpdY);
		TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufSpdY, (int)wcslen(bufSpdY));
	}
}
