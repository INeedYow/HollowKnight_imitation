#include "framework.h"
#include "CState_Run.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Run::CState_Run(eSTATE_PLAYER state)
	: CState_Player(state)
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
		changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
	}

	if (KEY_ON('Z'))
	{
		changeMyState(getOwner(), eSTATE_PLAYER::JUMP);
	}

	else if (KEY_ON('X'))
	{
		if (KEY_HOLD(VK_UP))
		{
			changeMyState(getOwner(), eSTATE_PLAYER::UPSLASH);
		}
		else
		{
			changeMyState(getOwner(), eSTATE_PLAYER::SLASH1);
		}
	}

	else if (KEY_ON('C'))
	{
		changeMyState(getOwner(), eSTATE_PLAYER::DASH);
	}

	else if (KEY_ON('A'))
	{
		if (getPlayer()->getPlayerInfo().uiSoul >= P_FIRESOUL)
		{
			changeMyState(getOwner(), eSTATE_PLAYER::FIRE);
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

void CState_Run::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Run";
	wchar_t bufSpdX[255] = {};

	swprintf_s(bufSpdX, L"SpdX = %.1f", info.fSpdX);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufSpdX, (int)wcslen(bufSpdX));
}