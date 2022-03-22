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

	else if (KEY_ON('C'))
	{
		changeAIState(getOwner(), eSTATE_PLAYER::DASH);
	}

	else if (KEY_ON('Z') && !(chk & SP_DBJUMP))
	{
		changeAIState(getOwner(), eSTATE_PLAYER::DOUBLEJUMP);
	}

	else if (KEY_ON('A'))
	{
		if (info.uiSoul >= P_FIRESOUL)
		{
			changeAIState(getOwner(), eSTATE_PLAYER::FIRE);
		}
	}

	info.fSpdY -= info.fGravity * fDT;

	if (info.fSpdY < 0.f)
		chk |= SP_GODOWN;

	if (info.fSpdY < (float)P_SPDY_MIN)
		info.fSpdY = (float)P_SPDY_MIN;

	pos.y -= info.fSpdY * fDT;
		
	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Fall::enter()
{
	getPlayer()->playAnim(L"Fall");
	getPlayer()->setCheck(SP_STOPANIM, true);

	getPlayer()->setCheck(SP_AIR, true);
	getPlayer()->setCheck(SP_GODOWN, true);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.iBottomCnt = 0;
	getPlayer()->setPlayerInfo(info);
}

void CState_Fall::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);

	//getPlayer()->setCheck(SP_GODOWN, false);		// 슬래쉬처럼 공중 동작할 때에도 낙하하고 있는 경우 있음

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fSpdY = 0.f;
	getPlayer()->setPlayerInfo(info);
}

void CState_Fall::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Fall";
	wchar_t bufSpdY[255] = {};
	
	swprintf_s(bufSpdY, L"SpdY = %.1f", info.fSpdY);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufSpdY, (int)wcslen(bufSpdY));
}
