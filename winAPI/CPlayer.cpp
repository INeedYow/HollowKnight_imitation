#include "framework.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CMissile.h"
#include "CAttack.h"
#include "CStatus.h"
#include "SelectGDI.h"
#include "CMonster.h"

#pragma region Include_State
#include "CState_Player.h"
#include "CState_Idle.h"
#include "CState_Run.h"
#include "CState_Jump.h"
#include "CState_Fall.h"
#include "CState_Slash1.h"
#include "CState_Slash2.h"
#include "CState_Upslash.h"
#include "CState_Downslash.h"
#include "CState_Fire.h"
#include "CState_Focus.h"
#include "CState_Stun.h"
#include "CState_Death.h"
#include "CState_Dash.h"
#include "CState_Dash2Idle.h"
#include "CState_Doublejump.h"
#include "CState_Land.h"
#pragma endregion

// test
#include "CTest.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\player\\player_tex.bmp");
	setName(eOBJNAME::PLAYER);
	setSize(fPoint(P_SIZEX, P_SIZEY));

	m_tInfo = {};
	m_tInfo.uiHP = 5;
	m_tInfo.fSpdX = (float)P_SPDX;
	m_tInfo.fGravity = (float)P_GRAV;

	m_tPrevInfo = {};
	m_pStatus = nullptr;
	m_uiCheck = 0;

	createCollider();
	getCollider()->setSize(fPoint(50.f, 108.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();

#pragma region createAnimation

	createAnim(L"Idle_R",		m_pTex,	fPoint(0.f, 0.f),			fPoint(60.f, 127.f),		fPoint(60.f, 0.f),			0.25f,	6);
	createAnim(L"Idle_L",		m_pTex,	fPoint(300.f, 127.f),		fPoint(60.f, 127.f),		fPoint(-60.f, 0.f),			0.25f,	6);

	createAnim(L"Run_R",		m_pTex,	fPoint(360.f, 0.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	12);
	createAnim(L"Run_L",		m_pTex,	fPoint(1262.f, 127.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	12);

	createAnim(L"Jump_R",		m_pTex,	fPoint(1344.f, 0.f),		fPoint(77.f, 127.f),		fPoint(77.f, 0.f),			0.2f,	6, false);
	createAnim(L"Jump_L",		m_pTex,	fPoint(1729.f, 127.f),		fPoint(77.f, 127.f),		fPoint(-77.f, 0.f),			0.2f,	6, false);

	createAnim(L"Fall_R",		m_pTex,	fPoint(1806.f, 0.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.2f,	6, false);
	createAnim(L"Fall_L",		m_pTex,	fPoint(2241.f, 127.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.2f,	6, false);

	createAnim(L"Land_R",		m_pTex,	fPoint(2328.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.8f,	1, false);
	createAnim(L"Land_L",		m_pTex,	fPoint(2480.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.8f,	1, false);

	createAnim(L"Land2Idle_R",	m_pTex,	fPoint(2404.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.2f,	2, false);
	createAnim(L"Land2Idle_L",	m_pTex,	fPoint(2404.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.2f,	2, false);

	createAnim(L"Stun_R",		m_pTex,	fPoint(2556.f, 2.f),		fPoint(94.f, 126.f),		fPoint(94.f, 0.f),			0.3f,	1, false);
	createAnim(L"Stun_L",		m_pTex,	fPoint(2556.f, 129.f),		fPoint(94.f, 126.f),		fPoint(94.f, 0.f),			0.3f,	1, false);

	createAnim(L"Slash1_R",		m_pTex,	fPoint(0.f, 254.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.06f,	5, false);
	createAnim(L"Slash1_L",		m_pTex,	fPoint(328.f, 381.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.06f,	5, false);

	createAnim(L"Slash2_R",		m_pTex,	fPoint(410.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.06f,	5, false);
	createAnim(L"Slash2_L",		m_pTex,	fPoint(882.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.06f,	5, false);

	createAnim(L"UpSlash_R",	m_pTex,	fPoint(1000.f, 254.f),		fPoint(95.f, 127.f),		fPoint(95.f, 0.f),			0.2f,	5, false);
	createAnim(L"UpSlash_L",	m_pTex,	fPoint(1380.f, 381.f),		fPoint(95.f, 127.f),		fPoint(-95.f, 0.f),			0.2f,	5, false);

	createAnim(L"DownSlash_R",	m_pTex,	fPoint(1475.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.2f,	5, false);
	createAnim(L"DownSlash_L",	m_pTex,	fPoint(1947.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.2f,	5, false);

	createAnim(L"Fire_R",		m_pTex,	fPoint(2065.f, 254.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.06f,	7, false);
	createAnim(L"Fire_L",		m_pTex,	fPoint(2587.f, 381.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.06f,	7, false);

	createAnim(L"Focus2Idle_R",	m_pTex,	fPoint(0.f, 508.f),			fPoint(64.f, 127.f),		fPoint(64.f, 0.f),			0.2f,	2, false);
	createAnim(L"Focus2Idle_L",	m_pTex,	fPoint(64.f, 635.f),		fPoint(64.f, 127.f),		fPoint(-64.f, 0.f),			0.2f,	2, false);

	createAnim(L"Death_R",		m_pTex,	fPoint(128.f, 508.f),		fPoint(107.f, 127.f),		fPoint(107.f, 0.f),			0.2f,	12, false);
	createAnim(L"Death_L",		m_pTex,	fPoint(1305.f, 635.f),		fPoint(107.f, 127.f),		fPoint(-107.f, 0.f),		0.2f,	12, false);

	createAnim(L"Focus_R",		m_pTex,	fPoint(1412.f, 513.f),		fPoint(94.f, 122.f),		fPoint(94.f, 0.f),			0.2f,	10);
	createAnim(L"Focus_L",		m_pTex,	fPoint(2258.f, 640.f),		fPoint(94.f, 122.f),		fPoint(-94.f, 0.f),			0.2f,	10);

	createAnim(L"Dash_R",		m_pTex,	fPoint(0.f, 762.f),			fPoint(172.f, 127.f),		fPoint(172.f, 0.f),			0.1f,	7, false);
	createAnim(L"Dash_L",		m_pTex,	fPoint(1032.f, 889.f),		fPoint(172.f, 127.f),		fPoint(-172.f, 0.f),		0.1f,	7, false);

	createAnim(L"Dash2Idle_R",	m_pTex,	fPoint(1204.f, 762.f),		fPoint(62.f, 127.f),		fPoint(62.f, 0.f),			0.1f,	4, false);
	createAnim(L"Dash2Idle_L",	m_pTex,	fPoint(1390.f, 889.f),		fPoint(62.f, 127.f),		fPoint(-62.f, 0.f),			0.1f,	4, false);

	createAnim(L"DoubleJump_R",	m_pTex,	fPoint(1452.f, 764.f),		fPoint(116.f, 129.f),		fPoint(116.f, 0.f),			0.2f,	8, false);
	createAnim(L"DoubleJump_L",	m_pTex,	fPoint(2264.f, 893.f),		fPoint(116.f, 129.f),		fPoint(-116.f, 0.f),		0.2f,	8, false);

	createAnim(L"Hang_R",		m_pTex, fPoint(2380.f, 764.f),		fPoint(75.f, 124.f),		fPoint(75.f, 0.f),			0.3f,	4, false);
	createAnim(L"Hang_L",		m_pTex, fPoint(2605.f, 892.f),		fPoint(75.f, 124.f),		fPoint(-75.f, 0.f),			0.3f,	4, false);


#pragma endregion

	PLAY(L"Idle_L");
}

CPlayer::~CPlayer()
{
	if (nullptr != m_pStatus)
		delete m_pStatus;
}

CPlayer* CPlayer::clone()
{
	return new CPlayer(*this);
}

CPlayer* CPlayer::createNormal(fPoint pos)
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;
	pPlayer->setPos(pos);

	CStatus* pStatus = new CStatus;
#pragma region AddState
	pStatus->addState(new CState_Idle(eSTATE_PLAYER::IDLE));
	pStatus->addState(new CState_Run(eSTATE_PLAYER::RUN));
	pStatus->addState(new CState_Jump(eSTATE_PLAYER::JUMP));
	pStatus->addState(new CState_Doublejump(eSTATE_PLAYER::DOUBLEJUMP));
	pStatus->addState(new CState_Fall(eSTATE_PLAYER::FALL));
	pStatus->addState(new CState_Land(eSTATE_PLAYER::LAND));

	pStatus->addState(new CState_Dash(eSTATE_PLAYER::DASH));
	pStatus->addState(new CState_Dash2Idle(eSTATE_PLAYER::DASH2IDLE));

	pStatus->addState(new CState_Slash1(eSTATE_PLAYER::SLASH1));
	pStatus->addState(new CState_Slash2(eSTATE_PLAYER::SLASH2));
	pStatus->addState(new CState_Upslash(eSTATE_PLAYER::UPSLASH));
	pStatus->addState(new CState_Downslash(eSTATE_PLAYER::DOWNSLASH));

	pStatus->addState(new CState_Fire(eSTATE_PLAYER::FIRE));
	pStatus->addState(new CState_Focus(eSTATE_PLAYER::FOCUS));

	pStatus->addState(new CState_Stun(eSTATE_PLAYER::STUN));
	pStatus->addState(new CState_Death(eSTATE_PLAYER::DEATH));

	pStatus->setCurState(eSTATE_PLAYER::FALL);
	pPlayer->setStatus(pStatus);
	
#pragma endregion
	// 
	pPlayer->setCheck(SP_AIR, true);
	pPlayer->setCheck(SP_GODOWN, true);
	pPlayer->setCheck(SP_DBJUMP, true);

	return pPlayer;
}


void CPlayer::playAnim(const wstring& keyWord)
{
	wstring strKey = keyWord;

	if (m_uiCheck & SP_DIR)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
}

void CPlayer::update()
{
	if (KEY_ON('P')) g_bDebug = !g_bDebug;

	if (g_bDebug && KEY_ON('O')) 
		setPos(mousePos());

	////////////////////////////
	// 회전테스트
	// T Y U I 
	// G H J
	//if (KEY_ON('Q'))
	//{
	//	createRotTester();
	//}

	if (nullptr != m_pStatus)
		m_pStatus->update(m_uiCheck);
	if (nullptr != getAnimator())
		getAnimator()->update();

	checkUpdate();	
}

void CPlayer::render(HDC hDC)
{
	if (g_bDebug)
		printInfo(hDC);

	componentRender(hDC);
	
}

void CPlayer::setStatus(CStatus* pStatus)
{
	m_pStatus = pStatus;
	m_pStatus->m_pOwner = this;
}

void CPlayer::setPlayerInfo(const tPlayerInfo& info)
{
	m_tInfo = info;
}

const tPlayerInfo& CPlayer::getPlayerInfo()
{
	return m_tInfo;
}

void CPlayer::setCheck(UINT chk, bool isOn)
{
	if (isOn)
		m_uiCheck |= chk;
	else
		m_uiCheck &= ~(chk);
}

bool CPlayer::isCheck(UINT chk)
{
	return m_uiCheck & chk;
}

UINT CPlayer::getCheck()
{
	return m_uiCheck;
}

CStatus* CPlayer::getAI()
{
	return m_pStatus;
}

void CPlayer::collisionKeep(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();

	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::MISSILE_MONSTER:
	case eOBJNAME::MONS_BEETLE:
	case eOBJNAME::MONS_MUSH:
	case eOBJNAME::SHIELD:
	case eOBJNAME::BOSS:
	{
		if (!(m_uiCheck & SP_NODMG) && !((CMonster*)pOther->getOwner())->isCheck(SM_DEATH))
		{	// 내가 무적 상태가 아니면서 몬스터가 죽은 상태가 아닌 경우
			m_tInfo.fvKnockBackDir = (getPos() - pTarget->getPos());

			if (--m_tInfo.uiHP <= 0)
				changeMyState(m_pStatus, eSTATE_PLAYER::DEATH);
			else
				changeMyState(m_pStatus, eSTATE_PLAYER::STUN);
		}
		break;
	}
	case eOBJNAME::ATTACK:
	{
		// ((CAttack*)pOther->getOwner())->getOwner()->getName()

		break;
	}

	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
		//switch (COLLGRD(pOther))
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::LEFT:
		{	// TODO state::hang
			fPoint pos = getPos();

			pos.x = pOther->getPos().x - pOther->getSize().x / 2.f + pOther->getOffset().x
				- getCollider()->getSize().x / 2.f - getCollider()->getOffset().x;
			setPos(pos);
			break;
		}
		case eDIR::RIGHT:
		{
			fPoint pos = getPos();

			pos.x = pOther->getPos().x + pOther->getSize().x / 2.f + pOther->getOffset().x
				+ getCollider()->getSize().x / 2.f + getCollider()->getOffset().x;
			setPos(pos);
			break;
		}
		case eDIR::TOP:
		{	// ground와 위쪽 충돌 진행 중인데 y값 증가하면(내려가면) 고정
			fPoint pos = getPos();
			if (pos.y > m_tPrevInfo.fpPrevPos.y)
			{
				pos.y = pOther->getPos().y - pOther->getSize().y / 2.f + pOther->getOffset().y
					- getCollider()->getSize().y / 2.f - getCollider()->getOffset().y + 1;
			}
			break;
		}
		}
	}
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	//벽 충돌
	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
		//switch (COLLGRD(pOther))
		switch (COLLRRW(getCollider(), pOther))
		{
		case eDIR::TOP:
		{
			if (m_uiCheck & SP_GODOWN)
			{	// 떨어지고 있던 경우 착지
				fPoint pos = getPos();

				pos.y = pOther->getPos().y - pOther->getSize().y / 2.f + pOther->getOffset().y 
					- getCollider()->getSize().y / 2.f - getCollider()->getOffset().y + 1;

				setPos(pos);
				
				if (m_tInfo.fLandTimer > P_LAND_TIMER)
					changeMyState(m_pStatus, eSTATE_PLAYER::LAND);

				if (m_uiCheck & SP_AIR)			// air를 fall exit에서 끄면 공중 동작 후 fall상태로 전환하기 힘듦
					m_uiCheck &= ~(SP_AIR);
				m_uiCheck &= ~(SP_GODOWN);
				m_tInfo.iBottomCnt++;
				m_tInfo.fSpdY = 0.f;
			}
			break;
		}
		case eDIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x - pOther->getSize().x / 2.f + pOther->getOffset().x
				- getCollider()->getSize().x / 2.f + getCollider()->getOffset().x - 1;
			setPos(pos);
			break;
		}
		case eDIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + pOther->getSize().x / 2.f + pOther->getOffset().x
				+ getCollider()->getSize().x / 2.f - getCollider()->getOffset().x + 1;
			setPos(pos);
			break;
		}
		case eDIR::BOTTOM:	// 머리 콩
		{	// 올라가는 속도 0으로
			m_tInfo.fSpdY = 0;	
			fPoint pos = getPos();

			pos.y = pOther->getPos().y + pOther->getSize().y / 2.f + pOther->getOffset().y
				+ getCollider()->getSize().y / 2.f - getCollider()->getOffset().y;

			setPos(pos);
			break;
		}
		}
		break;
	}
}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
		if (isTopColl(getCollider(), pOther))
		{	// 충돌 해제 할 때도 이전 좌표 있으면 되겠네
			if (--m_tInfo.iBottomCnt <= 0 && m_pStatus->getCurState()->getState() != eSTATE_PLAYER::JUMP)
			{	// 점프할 때도 exit에서 강제로 fall로 바꿔서 점프 안 됐었음
				m_tInfo.iBottomCnt = 0;
				changeMyState(m_pStatus, eSTATE_PLAYER::FALL);
			}
		}
		break;
	}
}

// == COLLGRD
eDIR CPlayer::collDirVersusGround(CCollider* pOther)
{	// enter에서만 해야할듯 바닥에 서서 좌우 이동하면 좌우 충돌 판정이 나는 듯함
	fPoint a = getPos();
	fPoint b = m_tPrevInfo.fpPrevPos;

	fVec2 myDir = getPos() - m_tPrevInfo.fpPrevPos;

	if (myDir.x * myDir.y == 0.f)	// x,y 중 최대 한쪽으로만 이동한 경우
	{
		if (myDir.x > 0.f) return eDIR::LEFT;		// 내 이동 방향이 오른쪽이면 왼쪽에서 충돌
		if (myDir.x < 0.f) return eDIR::RIGHT;			// 방향 왼쪽 : 오른쪽 충돌

		if (myDir.y > 0.f) return eDIR::TOP;			//
		if (myDir.y < 0.f) return eDIR::BOTTOM;			//

	}
	else
	{
		fPoint size1 = getSize();
		fPoint offSize = getCollider()->getOffset();
		fPoint pos2 = pOther->getPos();
		fPoint size2 = pOther->getSize();

		if (m_tPrevInfo.fpPrevPos.y < pos2.y - (size1.y + size2.y) / 2.f + offSize.y)
		{	// 이전 y 좌표가 위쪽이면
			return eDIR::TOP;
		}
		if (m_tPrevInfo.fpPrevPos.y > pos2.y + (size1.y + size2.y) / 2.f + offSize.y)
		{	// 이전 y 좌표가 아래쪽이면
			return eDIR::BOTTOM;
		}
		if (m_tPrevInfo.fpPrevPos.x < pos2.x - (size1.x + size2.x) / 2.f + offSize.x)
		{	// 이전 x 좌표가 왼쪽이면
			return eDIR::LEFT;
		}
		if (m_tPrevInfo.fpPrevPos.x > pos2.x + (size1.x + size2.x) / 2.f + offSize.x)
		{	// 이전 x 좌표가 오른쪽이면
			return eDIR::RIGHT;
		}
	}
	return eDIR::END;
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

		pMissile->PLAY(L"Missile_player_R");
	}
	else
	{
		mPos.x -= getSize().x / 2.f;
		mDir = -1.f;

		pMissile->PLAY(L"Missile_player_L");
	}
	pMissile->setPos(fPoint(mPos.x, mPos.y));
	pMissile->setSize(fPoint(40.f, 30.f));
	pMissile->getCollider()->setSize(fPoint(100.f, 60.f));
	pMissile->setDir(fVec2(mDir, 0.f));
	pMissile->setName(eOBJNAME::MISSILE_PLAYER);
	pMissile->setSpeed(1000.f);
	
	createObj(pMissile, eOBJ::MISSILE_PLAYER);
}

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
	m_pStatus->getCurState()->printInfo(hDC);

	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getPos();

	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufHP[255] = {};
	wchar_t bufSoul[255] = {};
	wchar_t bufBot[255] = {};

	swprintf_s(bufX, L"x = %.1f", pos.x);
	swprintf_s(bufY, L"y = %.1f", pos.y);
	swprintf_s(bufHP, L"HP = %d", m_tInfo.uiHP);
	swprintf_s(bufSoul, L"SOUL = %d", m_tInfo.uiSoul);
	swprintf_s(bufBot, L"BottomCnt = %d", (int)m_tInfo.iBottomCnt);

	// bufX,Y 출력보다 아래 위치해야 함
	fPoint rendPos = rendPos(pos);

	TextOutW(hDC, (int)rendPos.x + 100, (int)rendPos.y - 165, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)rendPos.x + 100, (int)rendPos.y - 140, bufY, (int)wcslen(bufY));
	TextOutW(hDC, (int)rendPos.x + 100, (int)rendPos.y - 115, bufHP, (int)wcslen(bufHP));
	TextOutW(hDC, (int)rendPos.x + 100, (int)rendPos.y - 90, bufSoul, (int)wcslen(bufSoul));
	TextOutW(hDC, (int)rendPos.x + 100, (int)rendPos.y - 65, bufBot, (int)wcslen(bufBot));

	if (m_uiCheck & SP_NODMG)
	{
		wchar_t bufNoDmg[255] = {};
		swprintf_s(bufNoDmg, L"NoDmg %.1f", m_tInfo.fNoDmgTimer);
		TextOutW(hDC, (int)rendPos.x + 100, (int)rendPos.y - 40, bufNoDmg, (int)wcslen(bufNoDmg));
	}
}

void CPlayer::checkUpdate()
{
	if (m_uiCheck & SP_NODMG)
	{
		m_tInfo.fNoDmgTimer -= fDT;

		if (m_tInfo.fNoDmgTimer <= 0.f)
		{
			m_tInfo.fNoDmgTimer = 0.f;
			m_uiCheck &= ~(SP_NODMG);
		}
	}

	if (m_tInfo.fSpdY == P_SPDY_MIN)
	{	// 최대 속력으로 낙하 중이면 landTimer 증가
		m_tInfo.fLandTimer += fDT;
	}
	else
	{
		m_tInfo.fLandTimer = 0.f;
	}
}

void CPlayer::updatePrevInfo(tPlayerPrevInfo prevInfo)
{
	m_tPrevInfo = prevInfo;
}

// Slash들 합쳐도 될듯
void CPlayer::firstSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_WIDTH, PSLASH_HEIGHT));
	pAttack->getCollider()->setSize(fPoint(PSLASH_WIDTH, PSLASH_HEIGHT));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		mPos.x += PSLASH_OFFSETX;
		pAttack->setDir(eDIR::RIGHT);
		
		pAttack->PLAY(L"Slash_player_R");
	}
	else
	{
		mPos.x -= PSLASH_OFFSETX;
		pAttack->setDir(eDIR::LEFT);
		
		pAttack->PLAY(L"Slash_player_L");
	}

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.25f);
	
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
	pAttack->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->getCollider()->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		pAttack->PLAY(L"UpSlash_player_R");
	}
	else
	{
		pAttack->PLAY(L"UpSlash_player_L");
	}

	mPos.y -= PSLASH_OFFSETY;
	pAttack->setDir(eDIR::TOP);

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.25f);

	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::downSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->getCollider()->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		pAttack->PLAY(L"DownSlash_player_R");
	}
	else
	{
		pAttack->PLAY(L"DownSlash_player_L");
	}

	mPos.y += PSLASH_OFFSETY;
	pAttack->setDir(eDIR::BOTTOM);

	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.5f);

	createObj(pAttack, eOBJ::ATTACK);
}