#include "framework.h"
#include "CState_Doublejump.h"
#include "CStatus.h"
#include "CPlayer.h"
#include "CEffect.h"

CState_Doublejump::CState_Doublejump(eSTATE_PLAYER state)
	: CState_Player(state)
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
	{	// 중력 증가 가속도 추가
		info.fSpdY -= (info.fGravity - m_fAccel) * fDT;

		if (info.fSpdY < 0.f)
			chk |= SP_GODOWN;

		if (info.fSpdY < (float)P_SPDY_MIN)
			info.fSpdY = (float)P_SPDY_MIN;
	}

	if (KEY_OFF('Z') || m_fTimer >= P_JUMPHOLDMAX)
	{	// Z 떼거나 점프 유지 최대시간 지나면
		chk &= ~(SP_JUMPHOLD);
	}

	//if (info.fSpdY + m_fAccel < info.fGravity)
	if (info.fSpdY < 0.f)
	{
		changeMyState(getOwner(), eSTATE_PLAYER::FALL);
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

	fPoint pos = getPlayer()->getPos();

	CEffect* pEff = new CEffect;
	pEff->load(L"Effect_dbJump", L"texture\\effect\\effect_doublejump.bmp");
	pEff->setFollow(getPlayer());
	pEff->setDuration(0.2f);
	if (getPlayer()->isCheck(SP_DIR))
	{
		pEff->createAnim(L"effect_dbjump", pEff->getTex(),
			fPoint(0, 0), fPoint(146, 289), fPoint(146, 0), 0.05f, 4, false);
		pos.x += 10.f;
	}
	else
	{
		pEff->createAnim(L"effect_dbjump", pEff->getTex(),
			fPoint(438, 289), fPoint(146, 289), fPoint(-146, 0), 0.05f, 4, false);
		pos.x -= 10.f;
	}
	pos.y += 75.f;
	pEff->setPos(pos);
	pEff->PLAY(L"effect_dbjump");
	createObj(pEff, eOBJ::EFFECT);

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
