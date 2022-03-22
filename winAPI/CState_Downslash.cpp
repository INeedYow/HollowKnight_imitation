#include "framework.h"
#include "CState_Downslash.h"
#include "CAI.h"
#include "CPlayer.h"

CState_Downslash::CState_Downslash(eSTATE_PLAYER state)
	: CState(state)
{
	m_fAttackDelay = 0.f;
}

CState_Downslash::~CState_Downslash()
{
}

// TODO 하단 공격 시 점프 -> 현재 난사 가능함, 수정필요.
void CState_Downslash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fAttackDelay += fDT;

	info.fSpdY -= info.fGravity * fDT;

	if (info.fSpdY <= 0.f)
		chk |= SP_GODOWN;

	if (info.fSpdY < (float)P_SPDY_MIN)
		info.fSpdY = (float)P_SPDY_MIN;

	pos.y -= info.fSpdY * fDT;
	
	if (m_fAttackDelay > (float)P_ATTDELAY)
	{
		if (chk & SP_AIR)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FALL);
		}
		else
		{	// 혹시 모르니
			changeAIState(getOwner(), eSTATE_PLAYER::IDLE);
		}
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Downslash::enter()
{
	getPlayer()->downSlash();
	getPlayer()->playAnim(L"DownSlash");
	
	getPlayer()->setCheck(SP_STOPANIM, true);
}

void CState_Downslash::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);
	m_fAttackDelay = 0.f;
}

void CState_Downslash::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"DownSlash";
	wchar_t bufSpdY[255] = {};
	wchar_t bufDelay[255] = {};
	
	swprintf_s(bufSpdY, L"SpdY = %.1f", info.fSpdY);
	
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufSpdY, (int)wcslen(bufSpdY));
	
}
