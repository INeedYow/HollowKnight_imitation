#include "framework.h"
#include "CState_Upslash.h"
#include "CStatus.h"
#include "CPlayer.h"


CState_Upslash::CState_Upslash(eSTATE_PLAYER state)
	: CState_Player(state) 
{
	m_fAttackDelay = 0.f;
}

CState_Upslash::~CState_Upslash()
{
}

void CState_Upslash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	if (chk & SP_AIR)
	{
		info.fSpdY -= info.fGravity * fDT;

		if (info.fSpdY <= 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;
		
		pos.y -= info.fSpdY * fDT;

		
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

void CState_Upslash::enter()
{
	getPlayer()->upSlash();
	getPlayer()->playAnim(L"UpSlash");
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Upslash::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
	m_fAttackDelay = 0.f;
}

void CState_Upslash::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"UpSlash";
	wchar_t bufDelay[255] = {};

	swprintf_s(bufDelay, L"delay = %.1f", m_fAttackDelay);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDelay, (int)wcslen(bufDelay));

	if (getPlayer()->isCheck(SP_AIR))
	{	// 공중에 있을 때 y속력 출력
		wchar_t bufSpdY[255] = {};
		swprintf_s(bufSpdY, L"SpdY = %.1f", info.fSpdY);
		TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 100, bufSpdY, (int)wcslen(bufSpdY));
	}
}