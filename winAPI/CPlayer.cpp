#include "framework.h"
#include "CPlayer.h"
#include "CMissile.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\texPlayer.bmp");
	setName(OBJNAME::PLAYER);
	setSize(fPoint(60.f, 120.f));

	m_eAction = eACT::IDLE;
	m_uiState = 0;

	m_fSpdX = P_SPDX;
	m_fSpdY = P_SPDY;
	m_fGravity = P_GRAV;
	m_fTimer = 0.f;
	m_iBottomCnt = 0;

	m_uiHP = 5;
	m_uiSoul = 0;
	m_uiZio = 0;


	createCollider();
	getCollider()->setSize(fPoint(90.f, 120.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));

	createAnimator();
	createAnim(L"Idle_R",		m_pTex,	fPoint(0.f, 0.f),			fPoint(60.f, 127.f),		fPoint(60.f, 0.f),			0.25f,	6);
	createAnim(L"Idle_L",		m_pTex,	fPoint(300.f, 127.f),		fPoint(60.f, 127.f),		fPoint(-60.f, 0.f),			0.25f,	6);

	createAnim(L"Run_R",		m_pTex,	fPoint(360.f, 0.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	12);
	createAnim(L"Run_L",		m_pTex,	fPoint(1262.f, 127.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	12);

	createAnim(L"Jump_R",		m_pTex,	fPoint(1344.f, 0.f),		fPoint(77.f, 127.f),		fPoint(77.f, 0.f),			0.2f,	6);
	createAnim(L"Jump_L",		m_pTex,	fPoint(1729.f, 127.f),		fPoint(77.f, 127.f),		fPoint(-77.f, 0.f),			0.2f,	6);

	createAnim(L"Fall_R",		m_pTex,	fPoint(1806.f, 0.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.2f,	6);
	createAnim(L"Fall_L",		m_pTex,	fPoint(2241.f, 127.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.2f,	6);

	createAnim(L"Land_R",		m_pTex,	fPoint(2328.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.3f,	3);
	createAnim(L"Land_L",		m_pTex,	fPoint(2480.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.3f,	3);

	createAnim(L"Stun_R",		m_pTex,	fPoint(2556.f, 0.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1);
	createAnim(L"Stun_L",		m_pTex,	fPoint(2556.f, 127.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1);

	createAnim(L"Slash1_R",		m_pTex,	fPoint(0.f, 254.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	5);
	createAnim(L"Slash1_L",		m_pTex,	fPoint(328.f, 381.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	5);

	createAnim(L"Slash2_R",		m_pTex,	fPoint(410.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.2f,	5);
	createAnim(L"Slash2_L",		m_pTex,	fPoint(882.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.2f,	5);

	createAnim(L"UpSlash_R",	m_pTex,	fPoint(1000.f, 254.f),		fPoint(95.f, 127.f),		fPoint(95.f, 0.f),			0.2f,	5);
	createAnim(L"UpSlash_L",	m_pTex,	fPoint(1380.f, 381.f),		fPoint(95.f, 127.f),		fPoint(-95.f, 0.f),			0.2f,	5);

	createAnim(L"DownSlash_R",	m_pTex,	fPoint(1475.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.2f,	5);
	createAnim(L"DownSlash_L",	m_pTex,	fPoint(1947.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.2f,	5);

	createAnim(L"Fire_R",		m_pTex,	fPoint(2065.f, 254.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.2f,	7);
	createAnim(L"Fire_L",		m_pTex,	fPoint(2587.f, 381.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.2f,	7);

	createAnim(L"Focus2Idle_R",	m_pTex,	fPoint(0.f, 508.f),			fPoint(64.f, 127.f),		fPoint(64.f, 0.f),			0.2f,	2);
	createAnim(L"Focus2Idle_L",	m_pTex,	fPoint(64.f, 635.f),		fPoint(64.f, 127.f),		fPoint(-64.f, 0.f),			0.2f,	2);

	createAnim(L"Death_R",		m_pTex,	fPoint(128.f, 508.f),		fPoint(107.f, 127.f),		fPoint(107.f, 0.f),			0.2f,	12);
	createAnim(L"Death_L",		m_pTex,	fPoint(1305.f, 635.f),		fPoint(107.f, 127.f),		fPoint(-107.f, 0.f),		0.2f,	12);

	createAnim(L"Focus_R",		m_pTex,	fPoint(1412.f, 508.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.2f,	10);
	createAnim(L"Focus_L",		m_pTex,	fPoint(2258.f, 635.f),		fPoint(94.f, 127.f),		fPoint(-94.f, 0.f),			0.2f,	10);

	PLAY(L"Idle_R");
}



CPlayer::~CPlayer()
{

}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

void CPlayer::playAnim(const wstring& commonName)
{
	wstring strKey = commonName;

	if (m_uiState & SP_DIR)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
}

void CPlayer::update()
{
	if (KEY_ON('P')) g_bDebug = !g_bDebug;

	fPoint pos = getPos();

	if (KEY_ON(VK_LEFT))
		m_uiState &= ~(SP_DIR);
	if (KEY_ON(VK_RIGHT))
		m_uiState |= SP_DIR;
	
	switch (m_eAction)
	{
	case eACT::IDLE:
	{	// 좌우이동, 점프, 공격, 스킬
		if (KEY_ON('Z') && !(m_uiState & SP_AIR))
		{
			m_uiState |= SP_AIR;
			m_eAction = eACT::JUMP;
		}

		if (KEY_ON(VK_LEFT) || KEY_ON(VK_RIGHT))
		{
			m_eAction = eACT::RUN;
		}

		if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eAction = eACT::UPSLASH;
			}
			else
			{
				m_eAction = eACT::SLASH1;
			}
		}

		if (KEY_ON('A') /*&& m_uiSoul >= mp소모량*/)
		{
			m_eAction = eACT::FIRE;
		}

		playAnim(L"Idle");
	}
		break;
	case eACT::RUN:
	{
		if (KEY_ON('Z') && !(m_uiState & SP_AIR))
		{
			m_uiState |= SP_AIR;
			m_eAction = eACT::JUMP;
		}

		if (KEY_ON(VK_LEFT))
		{
			m_uiState &= ~(SP_DIR);
			m_fSpdX *= -1.f;
		}
		else if (KEY_ON(VK_RIGHT))
		{
			m_uiState |= SP_DIR;
			m_fSpdX *= -1.f;
		}

		if (KEY_OFF(VK_LEFT) || KEY_OFF(VK_RIGHT))
		{
			m_eAction = eACT::IDLE;
		}

		playAnim(L"Run");
	}
		break;
	case eACT::JUMP:
	{	// 공격, 낙하
		if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_LEFT))
			{
				// TODO 하단공격
			}

			else if (KEY_HOLD(VK_UP))
			{
				// TODO 상단공격
			}

			else
			{
				// TODO 정면공격(좌, 우)
			}
		}

		m_fTimer += fDT;

		// TODO 구현 방법 두 개 갈팡질팡해서 아무것도 안 되는 중 
		// y좌표 변화량이 양수가 되면 fall로 처리하도록 딱 정함
		// 따라서 수정필요
		if (KEY_OFF('Z') || m_fTimer > 0.6f)
		{
			m_eAction = eACT::FALL;
			m_fTimer = 0.f;
		}

		pos.y -= (m_fSpdY - m_fGravity) * fDT;

		if (m_fGravity < P_GRAVMAX)
		{
			m_fGravity += P_GRAV * fDT;
		}
	}
		break;

	case eACT::FALL:
	{
		pos.y -= (m_fSpdY - m_fGravity) * fDT;

		if (m_fGravity < P_GRAVMAX)
		{
			m_fGravity += P_GRAV * fDT;
		}
	}
		break;
	}

	pos.x += m_fSpdX * fDT;
	
	
	setPos(pos);
	getAnimator()->update();
}

void CPlayer::render(HDC hDC)
{
	if (g_bDebug)
	{
		fPoint pos = getPos();

		wchar_t bufX[255] = {};
		wchar_t bufY[255] = {};

		swprintf_s(bufX, L"x = %d", (int)pos.x);
		swprintf_s(bufY, L"y = %d", (int)pos.y);

		pos = rendPos(pos);

		TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 60, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 75, bufY, (int)wcslen(bufY));
	}

	componentRender(hDC);
}

void CPlayer::collisionKeep(CCollider* pOther)
{
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	//벽 충돌
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
		{	// 지면과 1픽셀 겹치게 위치시켜서 exit말고 keep 호출되도록, 
			if (m_eAction == eACT::FALL)
			{	// 점프 동작 중 내려오는 동안에 충돌 시 착지
				fPoint pos = getPos();
				pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
					- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
				setPos(pos);
				if (m_uiState & SP_AIR)
					m_uiState &= ~(SP_AIR);
				m_iBottomCnt++;
			}
			break;
		}
		case DIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				- pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpdX = 0.f;
			break;
		}
		case DIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				+ pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpdX = 0.f;
			break;
		}
		case DIR::BOTTOM:	// 머리콩
			m_fSpdY = 0.f;
			break;
		}
		break;
	}
}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case OBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case DIR::TOP:
			if (--m_iBottomCnt <= 0)
			{
				/*if (m_iBottomCnt < 0)
					m_iBottomCnt = 0;*/
				m_uiState |= SP_AIR;
				m_fGravity = false;
			}
			break;
		}
		break;
	}
}

void CPlayer::createMissile()
{
	fPoint fpMissilePos = getPos();
	fpMissilePos.x += getSize().x / 2.f;

	// Misiile Object
	CMissile* pMissile = new CMissile;
	pMissile->setPos(fpMissilePos);
	pMissile->setDir(fVec2(1, 0));

	createObj(pMissile, OBJ::MISSILE_PLAYER);
}

void CPlayer::firstSlash()
{
}

void CPlayer::secondSlash()
{
}

void CPlayer::upSlash()
{
}

void CPlayer::downSlash()
{
}

void CPlayer::setAction(eACT act)
{
	switch (act)
	{
	case eACT::IDLE:
		m_fSpdX = 0.f;
		break;
	case eACT::RUN:
		m_fSpdX = P_SPDX;
		break;
	case eACT::JUMP:
		break;
	}
}
