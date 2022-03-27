#include "framework.h"
#include "CState_Jump.h"
#include "CStatus.h"
#include "CPlayer.h"

CState_Jump::CState_Jump(eSTATE_PLAYER state)
	: CState_Player(state)
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
	{	// Z ������ �ִ� ������ Ÿ�̸Ӹ� ����(�߷� ���� X)
		m_fTimer += fDT;
	}
	else
	{	// �߷� ����
		info.fSpdY -= info.fGravity * fDT;

		if (info.fSpdY < 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;
	}

	if (KEY_OFF('Z') || m_fTimer >= P_JUMPHOLDMAX)
	{	// Z ���ų� ���� ���� �ִ�ð� ������
		chk &= ~(SP_JUMPHOLD);
	}

	//if (info.fSpdY < info.fGravity)
	if (info.fSpdY < 0.f)
	{
		changeMyState(getOwner(), eSTATE_PLAYER::FALL);
	}

	if (KEY_HOLD(VK_LEFT))
	{
		chk &= ~(SP_DIR);
		pos.x -= info.fSpdX * fDT;
		getPlayer()->playAnim(L"Jump");		// �¿� ���⿡ ���� �ٽ� ���
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
			changeMyState(getOwner(), eSTATE_PLAYER::UPSLASH);
		}
		else if (KEY_HOLD(VK_DOWN))
		{
			changeMyState(getOwner(), eSTATE_PLAYER::DOWNSLASH);
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
		if (info.uiSoul >= P_FIRESOUL)
		{
			changeMyState(getOwner(), eSTATE_PLAYER::FIRE);
		}
	}

	pos.y -= info.fSpdY * fDT;

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

	fPoint pos = getPlayer()->getPos();
	pos.y -= 1;
	getPlayer()->setPos(pos);

	// �����ӵ�
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	if (getPlayer()->isCheck(SP_DWSLASH))
		info.fSpdY = (float)P_SPDY_DW;
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
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Jump";
	wchar_t bufSpdY[255] = {};

	swprintf_s(bufSpdY, L"SpdY = %.1f", info.fSpdY);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufSpdY, (int)wcslen(bufSpdY));
}
