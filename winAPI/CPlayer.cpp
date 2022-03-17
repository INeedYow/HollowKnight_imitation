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
	setSize(fPoint(90.f, 150.f));

	m_eAction = eACT::IDLE;
	m_uiState = 0;

	m_fSpdX = P_SPDX;
	m_fSpdY = P_SPDY;
	m_fGravity = P_GRAV;
	m_iBottomCnt = 0;

	m_fTimer = 0.f;
	m_fAttackDelay = 0.f;

	m_uiHP = 5;
	m_uiSoul = 100.f;
	m_uiZio = 0;

	createCollider();
	getCollider()->setSize(fPoint(110.f, 140.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));

	createAnimator();
	createAnim(L"Idle_R",		m_pTex,	fPoint(0.f, 0.f),			fPoint(60.f, 127.f),		fPoint(60.f, 0.f),			0.25f,	6);
	createAnim(L"Idle_L",		m_pTex,	fPoint(300.f, 127.f),		fPoint(60.f, 127.f),		fPoint(-60.f, 0.f),			0.25f,	6);

	createAnim(L"Run_R",		m_pTex,	fPoint(360.f, 0.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	12);
	createAnim(L"Run_L",		m_pTex,	fPoint(1262.f, 127.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	12);

	createAnim(L"Jump_R",		m_pTex,	fPoint(1344.f, 0.f),		fPoint(77.f, 127.f),		fPoint(77.f, 0.f),			0.1f,	6);
	createAnim(L"Jump_L",		m_pTex,	fPoint(1729.f, 127.f),		fPoint(77.f, 127.f),		fPoint(-77.f, 0.f),			0.1f,	6);

	createAnim(L"Fall_R",		m_pTex,	fPoint(1806.f, 0.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.2f,	6);
	createAnim(L"Fall_L",		m_pTex,	fPoint(2241.f, 127.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.2f,	6);

	createAnim(L"Land_R",		m_pTex,	fPoint(2328.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.3f,	3);
	createAnim(L"Land_L",		m_pTex,	fPoint(2480.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.3f,	3);

	createAnim(L"Stun_R",		m_pTex,	fPoint(2556.f, 0.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1);
	createAnim(L"Stun_L",		m_pTex,	fPoint(2556.f, 127.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1);

	createAnim(L"Slash1_R",		m_pTex,	fPoint(0.f, 254.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.1f,	5);
	createAnim(L"Slash1_L",		m_pTex,	fPoint(328.f, 381.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.1f,	5);

	createAnim(L"Slash2_R",		m_pTex,	fPoint(410.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.1f,	5);
	createAnim(L"Slash2_L",		m_pTex,	fPoint(882.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.1f,	5);

	createAnim(L"UpSlash_R",	m_pTex,	fPoint(1000.f, 254.f),		fPoint(95.f, 127.f),		fPoint(95.f, 0.f),			0.1f,	5);
	createAnim(L"UpSlash_L",	m_pTex,	fPoint(1380.f, 381.f),		fPoint(95.f, 127.f),		fPoint(-95.f, 0.f),			0.1f,	5);

	createAnim(L"DownSlash_R",	m_pTex,	fPoint(1475.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.2f,	5);
	createAnim(L"DownSlash_L",	m_pTex,	fPoint(1947.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.2f,	5);

	createAnim(L"Fire_R",		m_pTex,	fPoint(2065.f, 254.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.07f,	7);
	createAnim(L"Fire_L",		m_pTex,	fPoint(2587.f, 381.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.07f,	7);

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

// TODO : 현재 애니메이션 준비동작까지 반복돼서 같은 동작 오래 지속하면 부자연스러움
	// 그리고 매 번 첫 프레임부터 시작하게 해야 할듯
void CPlayer::update()
{
	if (KEY_ON('P')) g_bDebug = !g_bDebug;

	fPoint pos = getPos();

	switch (m_eAction)
	{
	case eACT::IDLE:
	{	// idle to run
		if (KEY_HOLD(VK_LEFT))
		{
			m_uiState &= ~(SP_DIR);
			m_eAction = eACT::RUN;
		}

		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiState |= SP_DIR;
			m_eAction = eACT::RUN;
		}
		// idle to jump
		else if (KEY_ON('Z'))
		{
			pos.y--;
			m_eAction = eACT::JUMP;
			m_uiState |= SP_JUMPHOLD;
			m_uiState |= SP_AIR;
		}
		// idle to slash
		else if (KEY_ON('X'))
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

		// idle to focus
		if (KEY_HOLD('A'))
		{
			m_fTimer += fDT;
			
			if (m_fTimer >= 0.5f)
			{
				m_eAction = eACT::FOCUS;
				m_fTimer = 0.f;
			}
		}		
		// idle to fire
		else if (KEY_OFF('A'))
		{
			m_fTimer = 0.f;

			if (m_uiSoul >= P_FIRESOUL)
			{
				m_eAction = eACT::FIRE;
			}
		}

		playAnim(L"Idle");
		break;
	}
	case eACT::RUN:
	{	// TODO 여유되면 애니메이션 시작 프레임 0으로
		if (KEY_HOLD(VK_LEFT))
		{
			m_uiState &= ~(SP_DIR);
			pos.x -= m_fSpdX * fDT;
		}
		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiState |= SP_DIR;
			pos.x += m_fSpdX * fDT;
		}
		else
		{
			m_eAction = eACT::IDLE;
		}

		if (KEY_ON('Z'))
		{
			pos.y--;
			m_eAction = eACT::JUMP;
			m_uiState |= SP_JUMPHOLD;
			m_uiState |= SP_AIR;
		}

		else if (KEY_ON('X'))
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

		else if (KEY_ON('A') /*&& m_uiSoul >= P_FIRESOUL*/)
		{	
			m_eAction = eACT::FIRE;
		}

		playAnim(L"Run");
		break;
	}
	case eACT::JUMP:
	{	
		if (m_uiState & SP_JUMPHOLD)
		{	// Z 누르는 동안은 타이머만 증가(중력 증가 X)
			m_fTimer += fDT;
		}
		else
		{	// 중력 증가
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;
		}

		if (KEY_OFF('Z') || m_fTimer >= 0.5f)
		{	// Z 떼거나 점프 유지 최대시간 지나면
			m_uiState &= ~(SP_JUMPHOLD);
			m_fTimer = 0.f;
		}
		if (m_fSpdY < m_fGravity)
		{
			m_eAction = eACT::FALL;
		}

		if (KEY_HOLD(VK_LEFT))
		{
			m_uiState &= ~(SP_DIR);
			pos.x -= m_fSpdX * fDT;
		}
		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiState |= SP_DIR;
			pos.x += m_fSpdX * fDT;
		}

		if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eAction = eACT::UPSLASH;
			}
			else if (KEY_HOLD(VK_DOWN))
			{
				m_eAction = eACT::DOWNSLASH;
			}
			else
			{
				m_eAction = eACT::SLASH1;
			}
		}

		else if (KEY_ON('A') /*&& m_uiSoul >= P_FIRESOUL*/)
		{
			m_eAction = eACT::FIRE;
		}

		pos.y -= (m_fSpdY - m_fGravity) * fDT;

		playAnim(L"Jump");
		break;
	}
	case eACT::FALL:
	{
		if (KEY_HOLD(VK_LEFT))
		{
			m_uiState &= ~(SP_DIR);
			pos.x -= m_fSpdX * fDT;
		}
		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiState |= SP_DIR;
			pos.x += m_fSpdX * fDT;
		}

		if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eAction = eACT::UPSLASH;
			}
			else if (KEY_HOLD(VK_DOWN))
			{
				m_eAction = eACT::DOWNSLASH;
			}
			else
			{
				m_eAction = eACT::SLASH1;
			}
		}

		else if (KEY_ON('A') /*&& m_uiSoul >= P_FIRESOUL*/)
		{
			m_eAction = eACT::FIRE;
			//m_uiSoul -= P_FIRESOUL;
		}

		if (m_fGravity < P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;

		pos.y -= (m_fSpdY - m_fGravity) * fDT;

		playAnim(L"Fall");
		break;
	}
	case eACT::FIRE:
	{
		if (m_fAttackDelay == 0.f)
		{
			createMissile();
			//m_uiSoul -= P_FIRESOUL;
		}
		
		m_fAttackDelay += fDT;

		if (m_fAttackDelay >= (float)P_FIREDELAY)
		{
			if (m_uiState & SP_AIR)
			{
				m_eAction = eACT::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eAction = eACT::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"Fire");
		break;
	}
	case eACT::SLASH1:
	{
		if (m_fAttackDelay == 0.f)
		{
			firstSlash();
		}

		m_fAttackDelay += fDT;

		if (m_uiState & SP_AIR)
		{	// 공중에서 공격할 때 중력적용
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;

			pos.y -= (m_fSpdY - m_fGravity) * fDT;
		}

		if (m_fAttackDelay > (float)P_ATTDELAY)
		{
			if (m_uiState & SP_AIR)
			{
				m_eAction = eACT::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eAction = eACT::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"Slash1");
		
		break;
	}
	case eACT::SLASH2:
	{
		// TODO SLASH2 되는 조건 확인하기
		break;
	}
	case eACT::UPSLASH:
	{
		if (m_fAttackDelay == 0.f)
		{
			upSlash();
		}

		m_fAttackDelay += fDT;

		if (m_uiState & SP_AIR)
		{	// 중력적용
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;

			pos.y -= (m_fSpdY - m_fGravity) * fDT;
		}

		if (m_fAttackDelay > (float)P_ATTDELAY)
		{
			if (m_uiState & SP_AIR)
			{	// JUMP 상태에서 공격하면 Fall 상태로
				m_eAction = eACT::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eAction = eACT::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"UpSlash");
		break;
	}
	case  eACT::DOWNSLASH:
	{
		if (m_fAttackDelay == 0.f)
		{
			downSlash();
		}

		m_fAttackDelay += fDT;

		if (m_uiState & SP_AIR)
		{	// 공중에서 공격할 때 중력적용
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;

			pos.y -= (m_fSpdY - m_fGravity) * fDT;
		}

		if (m_fAttackDelay > (float)P_ATTDELAY)
		{
			if (m_uiState & SP_AIR)
			{	// JUMP 상태에서 공격하면 fall
				m_eAction = eACT::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eAction = eACT::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"DownSlash");
		break;
	}
	case eACT::FOCUS:
	{	// focus to idle
		if (KEY_OFF('A'))
		{
			m_fTimer = 0.f;
			m_eAction = eACT::IDLE;
		}
		
		m_fTimer += fDT;

		if (m_fTimer/**/)
		{
			// TODO 체력회복
		}	// 소울 소모

		if (m_uiSoul < 0.f)
		{
			m_fTimer = 0.f;
			m_uiSoul = 0.f;
			m_eAction = eACT::IDLE;
		}

		playAnim(L"Focus");
		break;
	}
	}
	
	if (pos.y > 2950.f)
	{
		pos.y = 2950.f;
		m_uiState &= ~(SP_AIR);
		m_eAction = eACT::IDLE;
		m_fGravity = 0.f;
	}

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
		wchar_t bufGrav[255] = {};

		swprintf_s(bufX, L"x = %d", (int)pos.x);
		swprintf_s(bufY, L"y = %d", (int)pos.y);
		swprintf_s(bufGrav, L"grav = %f", m_fGravity);

		pos = rendPos(pos);

		TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 60, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 75, bufY, (int)wcslen(bufY));
		TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 90, bufGrav, (int)wcslen(bufGrav));
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
		{	// 지면과 1픽셀 겹치게 위치
			if (m_eAction == eACT::FALL)
			{	// Fall일 때만 착지
				fPoint pos = getPos();
				pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
					- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
				setPos(pos);
				if (m_uiState & SP_AIR)
					m_uiState &= ~(SP_AIR);
				m_iBottomCnt++;
				m_fGravity = 0.f;
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
		case DIR::BOTTOM:	// 머리 콩
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
				m_fGravity = 0.f;
			}
			break;
		}
		break;
	}
}

void CPlayer::createMissile()
{
	fPoint mPos = getPos();
	float mDir = 1.f;

	CMissile* pMissile = new CMissile;

	if (m_uiState & SP_DIR)
	{
		mPos.x += getSize().x / 2.f;
		mDir = 1.f;
	}
	else
	{
		mPos.x -= getSize().x / 2.f;
		mDir = -1.f;
	}
	pMissile->setPos(fPoint(mPos.x, mPos.y));
	pMissile->setDir(fVec2(mDir, 0.f));
	pMissile->setName(OBJNAME::MISSILE_PLAYER);

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

