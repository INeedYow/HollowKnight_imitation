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
	{	// Z ������ �ִ� ������ Ÿ�̸Ӹ� ����(�߷� ���� X)
		m_fTimer += fDT;
		m_fAccel += 300 * fDT;
	}
	else
	{	// �߷� ���� ���ӵ� �߰�
		info.fSpdY -= (info.fGravity - m_fAccel) * fDT;

		if (info.fSpdY < 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;
	}

	if (KEY_OFF('Z') || m_fTimer >= P_JUMPHOLDMAX)
	{	// Z ���ų� ���� ���� �ִ�ð� ������
		chk &= ~(SP_JUMPHOLD);
	}

	//if (info.fSpdY + m_fAccel < info.fGravity)
	if (info.fSpdY < 0.f)
	{
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

	pos.y -=info.fSpdY * fDT;

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Doublejump::enter()
{
	getPlayer()->playAnim(L"DoubleJump");
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_GODOWN, false);
	getPlayer()->setCheck(SP_DBJUMP, true);
	getPlayer()->setCheck(SP_JUMPHOLD, true);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fSpdY = P_SPDY;
	getPlayer()->setPlayerInfo(info);

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
	SelectGDI font(hDC, eFONT::COMIC28);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"DoubleJump";
	wchar_t bufSpdY[255] = {};
	wchar_t bufAccel[255] = {};

	swprintf_s(bufSpdY, L"SpdY = %.1f", info.fSpdY);
	swprintf_s(bufAccel, L"Accel = %.1f", m_fAccel);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufSpdY, (int)wcslen(bufSpdY));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 100, bufAccel, (int)wcslen(bufAccel));

}
