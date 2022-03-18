#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CMissile.h"
#include "CAttack.h"
#include "CAI.h"
// test
#include "CTest.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\player\\texPlayer.bmp");
	setName(eOBJNAME::PLAYER);
	setSize(fPoint(P_SIZEX, P_SIZEY));

	m_eState = eSTATE_PLAYER::IDLE;
	m_uiCheck = 0;

	m_fSpdX = P_SPDX;
	m_fSpdY = P_SPDY;
	m_fGravity = P_GRAV;
	m_iBottomCnt = 0;

	m_fTimer = 0.f;
	m_fAttackDelay = 0.f;

	m_uiHP = 5;
	m_uiSoul = 100.f;
	m_uiZio = 0;

	m_pAI = nullptr;

	createCollider();
	getCollider()->setSize(fPoint(110.f, 140.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));

	createAnimator();

#pragma region Animation

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

	createAnim(L"Slash2_R",		m_pTex,	fPoint(410.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.1f,	5);
	createAnim(L"Slash2_L",		m_pTex,	fPoint(882.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.1f,	5);

	createAnim(L"UpSlash_R",	m_pTex,	fPoint(1000.f, 254.f),		fPoint(95.f, 127.f),		fPoint(95.f, 0.f),			0.2f,	5);
	createAnim(L"UpSlash_L",	m_pTex,	fPoint(1380.f, 381.f),		fPoint(95.f, 127.f),		fPoint(-95.f, 0.f),			0.2f,	5);

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

#pragma endregion

	PLAY(L"Idle_R");
}

CPlayer::~CPlayer()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

void CPlayer::playAnim(const wstring& commonName)
{
	wstring strKey = commonName;

	if (m_uiCheck & SP_DIR)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
}

// TODO : 현재 애니메이션 준비동작까지 반복돼서 같은 동작 오래 지속하면 부자연스러움
	// 애니메이션 반복 여부 설정
// TODO : 한 번씩 키 씹히는 것 같은데
void CPlayer::update()
{
	if (KEY_ON('P')) g_bDebug = !g_bDebug;

	if (nullptr != getAnimator())
		getAnimator()->update();

	if (nullptr != m_pAI)
		m_pAI->update();

	fPoint pos = getPos();

	switch (m_eState)
	{
	case eSTATE_PLAYER::IDLE:
	{	// idle to run
		if (KEY_HOLD(VK_LEFT))
		{
			m_uiCheck &= ~(SP_DIR);
			m_eState = eSTATE_PLAYER::RUN;
		}

		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiCheck |= SP_DIR;
			m_eState = eSTATE_PLAYER::RUN;
		}
		// idle to jump
		else if (KEY_ON('Z'))
		{
			pos.y--;
			m_eState = eSTATE_PLAYER::JUMP;
			m_uiCheck |= SP_JUMPHOLD;
			m_uiCheck |= SP_AIR;
		}
		// idle to slash
		else if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eState = eSTATE_PLAYER::UPSLASH;
			}
			else
			{
				m_eState = eSTATE_PLAYER::SLASH1;
			}
		}

		// idle to focus
		if (KEY_HOLD('A'))
		{
			m_fTimer += fDT;
			
			if (m_fTimer >= 0.5f)
			{
				m_eState = eSTATE_PLAYER::FOCUS;
				m_fTimer = 0.f;
			}
		}		
		// idle to fire
		else if (KEY_OFF('A'))
		{
			m_fTimer = 0.f;

			if (m_uiSoul >= P_FIRESOUL)
			{
				m_eState = eSTATE_PLAYER::FIRE;
			}
		}

		playAnim(L"Idle");
		break;
	}
	case eSTATE_PLAYER::RUN:
	{	// TODO 여유되면 애니메이션 시작 프레임 0으로
		if (KEY_HOLD(VK_LEFT))
		{
			m_uiCheck &= ~(SP_DIR);
			pos.x -= m_fSpdX * fDT;
		}
		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiCheck |= SP_DIR;
			pos.x += m_fSpdX * fDT;
		}
		else
		{
			m_eState = eSTATE_PLAYER::IDLE;
		}

		if (KEY_ON('Z'))
		{
			pos.y--;
			m_eState = eSTATE_PLAYER::JUMP;
			m_uiCheck |= SP_JUMPHOLD;
			m_uiCheck |= SP_AIR;
		}

		else if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eState = eSTATE_PLAYER::UPSLASH;
			}
			else
			{
				m_eState = eSTATE_PLAYER::SLASH1;
			}
		}

		else if (KEY_ON('A') /*&& m_uiSoul >= P_FIRESOUL*/)
		{	
			m_eState = eSTATE_PLAYER::FIRE;
		}

		playAnim(L"Run");
		break;
	}
	case eSTATE_PLAYER::JUMP:
	{	
		if (m_uiCheck & SP_JUMPHOLD)
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
			m_uiCheck &= ~(SP_JUMPHOLD);
			m_fTimer = 0.f;
		}
		if (m_fSpdY < m_fGravity)
		{
			m_eState = eSTATE_PLAYER::FALL;
		}

		if (KEY_HOLD(VK_LEFT))
		{
			m_uiCheck &= ~(SP_DIR);
			pos.x -= m_fSpdX * fDT;
		}
		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiCheck |= SP_DIR;
			pos.x += m_fSpdX * fDT;
		}

		if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eState = eSTATE_PLAYER::UPSLASH;
			}
			else if (KEY_HOLD(VK_DOWN))
			{
				m_eState = eSTATE_PLAYER::DOWNSLASH;
			}
			else
			{
				m_eState = eSTATE_PLAYER::SLASH1;
			}
		}

		else if (KEY_ON('A') /*&& m_uiSoul >= P_FIRESOUL*/)
		{
			m_eState = eSTATE_PLAYER::FIRE;
		}

		pos.y -= (m_fSpdY - m_fGravity) * fDT;

		playAnim(L"Jump");
		break;
	}
	case eSTATE_PLAYER::FALL:
	{
		if (KEY_HOLD(VK_LEFT))
		{
			m_uiCheck &= ~(SP_DIR);
			pos.x -= m_fSpdX * fDT;
		}
		else if (KEY_HOLD(VK_RIGHT))
		{
			m_uiCheck |= SP_DIR;
			pos.x += m_fSpdX * fDT;
		}

		if (KEY_ON('X'))
		{
			if (KEY_HOLD(VK_UP))
			{
				m_eState = eSTATE_PLAYER::UPSLASH;
			}
			else if (KEY_HOLD(VK_DOWN))
			{
				m_eState = eSTATE_PLAYER::DOWNSLASH;
			}
			else
			{
				m_eState = eSTATE_PLAYER::SLASH1;
			}
		}

		else if (KEY_ON('A') /*&& m_uiSoul >= P_FIRESOUL*/)
		{
			m_eState = eSTATE_PLAYER::FIRE;
			//m_uiSoul -= P_FIRESOUL;
		}

		if (m_fGravity < P_GRAVMAX)
			m_fGravity += P_GRAV * fDT;

		pos.y -= (m_fSpdY - m_fGravity) * fDT;

		playAnim(L"Fall");
		break;
	}
	case eSTATE_PLAYER::FIRE:
	{
		if (m_fAttackDelay == 0.f)
		{
			createMissile();
			//m_uiSoul -= P_FIRESOUL;
		}
		
		m_fAttackDelay += fDT;

		if (m_fAttackDelay >= (float)P_FIREDELAY)
		{
			if (m_uiCheck & SP_AIR)
			{
				m_eState = eSTATE_PLAYER::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eState = eSTATE_PLAYER::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"Fire");
		break;
	}
	case eSTATE_PLAYER::SLASH1:
	{
		if (m_fAttackDelay == 0.f)
		{
			firstSlash();
		}

		m_fAttackDelay += fDT;

		if (m_uiCheck & SP_AIR)
		{	// 공중에서 공격할 때 중력적용
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;

			pos.y -= (m_fSpdY - m_fGravity) * fDT;
		}

		if (m_fAttackDelay > (float)P_ATTDELAY)
		{
			if (m_uiCheck & SP_AIR)
			{
				m_eState = eSTATE_PLAYER::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eState = eSTATE_PLAYER::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"Slash1");
		
		break;
	}
	case eSTATE_PLAYER::SLASH2:
	{
		// TODO SLASH2 되는 조건 확인하기
		break;
	}
	case eSTATE_PLAYER::UPSLASH:
	{
		if (m_fAttackDelay == 0.f)
		{
			upSlash();
		}

		m_fAttackDelay += fDT;

		if (m_uiCheck & SP_AIR)
		{	// 중력적용
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;

			pos.y -= (m_fSpdY - m_fGravity) * fDT;
		}

		if (m_fAttackDelay > (float)P_ATTDELAY)
		{
			if (m_uiCheck & SP_AIR)
			{	// JUMP 상태에서 공격하면 Fall 상태로
				m_eState = eSTATE_PLAYER::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eState = eSTATE_PLAYER::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"UpSlash");
		break;
	}
	case  eSTATE_PLAYER::DOWNSLASH:
	{
		if (m_fAttackDelay == 0.f)
		{
			downSlash();
		}

		m_fAttackDelay += fDT;

		if (m_uiCheck & SP_AIR)
		{	// 공중에서 공격할 때 중력적용
			if (m_fGravity < P_GRAVMAX)
				m_fGravity += P_GRAV * fDT;

			pos.y -= (m_fSpdY - m_fGravity) * fDT;
		}

		if (m_fAttackDelay > (float)P_ATTDELAY)
		{
			if (m_uiCheck & SP_AIR)
			{	// JUMP 상태에서 공격하면 fall
				m_eState = eSTATE_PLAYER::FALL;
				m_fAttackDelay = 0.f;
			}
			else
			{
				m_eState = eSTATE_PLAYER::IDLE;
				m_fAttackDelay = 0.f;
			}
		}
		playAnim(L"DownSlash");
		break;
	}
	case eSTATE_PLAYER::FOCUS:
	{	// focus to idle
		if (KEY_OFF('A'))
		{
			m_fTimer = 0.f;
			m_eState = eSTATE_PLAYER::IDLE;
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
			m_eState = eSTATE_PLAYER::IDLE;
		}

		playAnim(L"Focus");
		break;
	}
	}
	
	// 회전테스트
	if (KEY_ON('Q'))
	{
		createRotTester();
	}

	if (pos.y > 1519.f)
	{
		pos.y = 1519.f;
		m_uiCheck &= ~(SP_AIR);
		m_eState = eSTATE_PLAYER::IDLE;
		m_fGravity = 0.f;
	}

	setPos(pos);

	if (nullptr != getAnimator())
		getAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
}

void CPlayer::render(HDC hDC)
{
	if (g_bDebug)
	{
		printInfo(hDC);
	}

	componentRender(hDC);
	
}

void CPlayer::setAI(CAI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CPlayer::collisionKeep(CCollider* pOther)
{
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	//벽 충돌
	case eOBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::TOP:
		{	// 지면과 1픽셀 겹치게 위치
			if (m_eState == eSTATE_PLAYER::FALL)
			{	// Fall일 때만 착지
				fPoint pos = getPos();
				pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
					- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
				setPos(pos);
				if (m_uiCheck & SP_AIR)
					m_uiCheck &= ~(SP_AIR);
				m_iBottomCnt++;
				m_fGravity = 0.f;
			}
			break;
		}
		case eDIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				- pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpdX = 0.f;
			break;
		}
		case eDIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				+ pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			m_fSpdX = 0.f;
			break;
		}
		case eDIR::BOTTOM:	// 머리 콩
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
	case eOBJNAME::TILE:
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::TOP:
			if (--m_iBottomCnt <= 0)
			{
				m_uiCheck |= SP_AIR;
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

	if (m_uiCheck & SP_DIR)
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
	pMissile->setSize(fPoint(30.f, 30.f));
	pMissile->getCollider()->setSize(fPoint(30.f, 30.f));
	pMissile->setDir(fVec2(mDir, 0.f));
	pMissile->setName(eOBJNAME::MISSILE_PLAYER);
	pMissile->setSpeed(400.f);

	createObj(pMissile, eOBJ::MISSILE_PLAYER);
}

/////////////////////////////////////// test
void CPlayer::createRotTester()
{	
	fPoint mPos = getPos();

	CTest* pTest = new CTest;

	if (m_uiCheck & SP_DIR)
	{
		pTest->setDir(fPoint(1.f, 0.f));
		mPos.x = -100.f;
		pTest->setRot(true);
	}
	else
	{
		pTest->setDir(fPoint(-1.f, 0.f));
		mPos.x = 100.f;
		pTest->setRot(false);
	}
	pTest->setOwner(this);
	//pTest->setPos(fPoint(mPos.x, mPos.y));
	pTest->setOffset(fPoint(mPos.x, 0.f));
	pTest->setName(eOBJNAME::TEST);

	createObj(pTest, eOBJ::TEST);
}
///////////////////////////////////////////////

void CPlayer::printInfo(HDC hDC)
{
	fPoint pos = getPos();


	LPCWSTR	szAct = L"";
	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufGrav[255] = {};

	switch (m_eState)
	{
	case eSTATE_PLAYER::IDLE:
		szAct = L"Idle";
		break;
	case eSTATE_PLAYER::RUN:
		szAct = L"Run";
		break;
	case eSTATE_PLAYER::JUMP:
		szAct = L"Jump";
		break;
	case eSTATE_PLAYER::FALL:
		szAct = L"Fall";
		break;
	case eSTATE_PLAYER::SLASH1:
		szAct = L"Slash1";
		break;
	case eSTATE_PLAYER::SLASH2:
		szAct = L"SLASH2";
		break;
	case eSTATE_PLAYER::UPSLASH:
		szAct = L"UpSlash";
		break;
	case eSTATE_PLAYER::DOWNSLASH:
		szAct = L"DownSlash";
		break;
	case eSTATE_PLAYER::HANG:
		szAct = L"Hang";
		break;
	case eSTATE_PLAYER::FIRE:
		szAct = L"Fire";
		break;
	case eSTATE_PLAYER::FOCUS:
		szAct = L"Focus";
		break;
	case eSTATE_PLAYER::STUN:
		szAct = L"Stun";
		break;
	default:
		break;
	}

	swprintf_s(bufX, L"x = %d", (int)pos.x);
	swprintf_s(bufY, L"y = %d", (int)pos.y);
	swprintf_s(bufGrav, L"grav = %f", m_fGravity);

	pos = rendPos(pos);

	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 60, szAct, (int)wcslen(szAct));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 75, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 90, bufY, (int)wcslen(bufY));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 105, bufGrav, (int)wcslen(bufGrav));

}

// Slash들 합쳐도 될듯
void CPlayer::firstSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->getCollider()->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEX));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		mPos.x += PSLASH_OFFSETX;
		pAttack->setDir(eDIR::RIGHT);
	}
	else
	{
		mPos.x -= PSLASH_OFFSETX;
		pAttack->setDir(eDIR::LEFT);
	}

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);
	
	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::secondSlash()
{
}

void CPlayer::upSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->getCollider()->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->setOwner(this);

	mPos.y -= PSLASH_OFFSETY;
	pAttack->setDir(eDIR::TOP);

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);

	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::downSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->getCollider()->setSize(fPoint(PSLASH_SIZEX, PSLASH_SIZEY));
	pAttack->setOwner(this);

	mPos.y += PSLASH_OFFSETY;
	pAttack->setDir(eDIR::BOTTOM);

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);

	createObj(pAttack, eOBJ::ATTACK);
}

