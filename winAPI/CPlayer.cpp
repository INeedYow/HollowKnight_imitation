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

#pragma region Include_State
#include "CState.h"
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
#pragma endregion

// test
#include "CTest.h"

CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\player\\player_tex.bmp");
	setName(eOBJNAME::PLAYER);
	setSize(fPoint(P_SIZEX, P_SIZEY));

	m_tInfo = {
		5,
		50,
		0,
		P_SPDX,
		P_SPDY,
		0.f,
		0.f,
		0,
		{},
		//0.f
	};
	m_tPrevInfo = {};

	m_pAI = nullptr;
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

	createAnim(L"Land_R",		m_pTex,	fPoint(2328.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.3f,	3, false);
	createAnim(L"Land_L",		m_pTex,	fPoint(2480.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.3f,	3, false);

	createAnim(L"Stun_R",		m_pTex,	fPoint(2556.f, 0.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1, false);
	createAnim(L"Stun_L",		m_pTex,	fPoint(2556.f, 127.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.3f,	1, false);

	createAnim(L"Slash1_R",		m_pTex,	fPoint(0.f, 254.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	5, false);
	createAnim(L"Slash1_L",		m_pTex,	fPoint(328.f, 381.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	5, false);

	createAnim(L"Slash2_R",		m_pTex,	fPoint(410.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.1f,	5, false);
	createAnim(L"Slash2_L",		m_pTex,	fPoint(882.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.1f,	5, false);

	createAnim(L"UpSlash_R",	m_pTex,	fPoint(1000.f, 254.f),		fPoint(95.f, 127.f),		fPoint(95.f, 0.f),			0.2f,	5, false);
	createAnim(L"UpSlash_L",	m_pTex,	fPoint(1380.f, 381.f),		fPoint(95.f, 127.f),		fPoint(-95.f, 0.f),			0.2f,	5, false);

	createAnim(L"DownSlash_R",	m_pTex,	fPoint(1475.f, 254.f),		fPoint(118.f, 127.f),		fPoint(118.f, 0.f),			0.2f,	5, false);
	createAnim(L"DownSlash_L",	m_pTex,	fPoint(1947.f, 381.f),		fPoint(118.f, 127.f),		fPoint(-118.f, 0.f),		0.2f,	5, false);

	createAnim(L"Fire_R",		m_pTex,	fPoint(2065.f, 254.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.07f,	7, false);
	createAnim(L"Fire_L",		m_pTex,	fPoint(2587.f, 381.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.07f,	7, false);

	createAnim(L"Focus2Idle_R",	m_pTex,	fPoint(0.f, 508.f),			fPoint(64.f, 127.f),		fPoint(64.f, 0.f),			0.2f,	2, false);
	createAnim(L"Focus2Idle_L",	m_pTex,	fPoint(64.f, 635.f),		fPoint(64.f, 127.f),		fPoint(-64.f, 0.f),			0.2f,	2, false);

	createAnim(L"Death_R",		m_pTex,	fPoint(128.f, 508.f),		fPoint(107.f, 127.f),		fPoint(107.f, 0.f),			0.2f,	12, false);
	createAnim(L"Death_L",		m_pTex,	fPoint(1305.f, 635.f),		fPoint(107.f, 127.f),		fPoint(-107.f, 0.f),		0.2f,	12, false);

	createAnim(L"Focus_R",		m_pTex,	fPoint(1412.f, 508.f),		fPoint(94.f, 127.f),		fPoint(94.f, 0.f),			0.2f,	10);
	createAnim(L"Focus_L",		m_pTex,	fPoint(2258.f, 635.f),		fPoint(94.f, 127.f),		fPoint(-94.f, 0.f),			0.2f,	10);

	createAnim(L"Dash_R",		m_pTex,	fPoint(0.f, 762.f),			fPoint(172.f, 127.f),		fPoint(172.f, 0.f),			0.1f,	7, false);
	createAnim(L"Dash_L",		m_pTex,	fPoint(1032.f, 889.f),		fPoint(172.f, 127.f),		fPoint(-172.f, 0.f),		0.1f,	7, false);

	createAnim(L"Dash2Idle_R",	m_pTex,	fPoint(1204.f, 762.f),		fPoint(62.f, 127.f),		fPoint(62.f, 0.f),			0.1f,	4, false);
	createAnim(L"Dash2Idle_L",	m_pTex,	fPoint(1390.f, 889.f),		fPoint(62.f, 127.f),		fPoint(-62.f, 0.f),			0.1f,	4, false);

	createAnim(L"DoubleJump_R",	m_pTex,	fPoint(1452.f, 764.f),		fPoint(116.f, 129.f),		fPoint(116.f, 0.f),			0.2f,	8, false);
	createAnim(L"DoubleJump_L",	m_pTex,	fPoint(2264.f, 893.f),		fPoint(116.f, 129.f),		fPoint(-116.f, 0.f),		0.2f,	8, false);

	createAnim(L"Hang_R",		m_pTex, fPoint(2380.f, 764.f),		fPoint(75.f, 124.f),		fPoint(75.f, 0.f),			0.3f,	4, false);
	createAnim(L"Hang_L",		m_pTex, fPoint(2605.f, 892.f),		fPoint(75.f, 124.f),		fPoint(-75.f, 0.f),			0.3f,	4, false);


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

CPlayer* CPlayer::createNormal(fPoint pos)
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;
	pPlayer->setPos(pos);

	CAI* pAI = new CAI;
#pragma region AddState
	pAI->addState(new CState_Idle(eSTATE_PLAYER::IDLE));
	pAI->addState(new CState_Run(eSTATE_PLAYER::RUN));
	pAI->addState(new CState_Jump(eSTATE_PLAYER::JUMP));
	pAI->addState(new CState_Doublejump(eSTATE_PLAYER::DOUBLEJUMP));
	pAI->addState(new CState_Fall(eSTATE_PLAYER::FALL));

	pAI->addState(new CState_Dash(eSTATE_PLAYER::DASH));
	pAI->addState(new CState_Dash2Idle(eSTATE_PLAYER::DASH2IDLE));

	pAI->addState(new CState_Slash1(eSTATE_PLAYER::SLASH1));
	pAI->addState(new CState_Slash2(eSTATE_PLAYER::SLASH2));
	pAI->addState(new CState_Upslash(eSTATE_PLAYER::UPSLASH));
	pAI->addState(new CState_Downslash(eSTATE_PLAYER::DOWNSLASH));

	pAI->addState(new CState_Fire(eSTATE_PLAYER::FIRE));
	pAI->addState(new CState_Focus(eSTATE_PLAYER::FOCUS));

	pAI->addState(new CState_Stun(eSTATE_PLAYER::STUN));
	pAI->addState(new CState_Death(eSTATE_PLAYER::DEATH));

	pAI->setCurState(eSTATE_PLAYER::IDLE);
	pPlayer->setAI(pAI);
#pragma endregion
	return pPlayer;
}


// 좌우 이동시 fSpdX에 -1 곱해서 하면 상황별로 애니메이션 하기 편할듯
void CPlayer::playAnim(const wstring& keyWord)
{
	wstring strKey = keyWord;

	if (m_uiCheck & SP_DIR)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
#pragma region error
	//if (strKey == L"\0" && SP_STOPANIM)
	//{
	//	fPoint pos = getPos();

	//	if (m_tPrevInfo.uiPrevHP < m_tInfo.uiHP)
	//		strKey = L"Stun";
	//	else
	//	{
	//		if (m_tPrevInfo.fpPrevPos == pos)
	//			strKey = L"Idle";
	//		else
	//			strKey = L"Run";

	//		if (m_tPrevInfo.fpPrevPos.y > pos.y)
	//			strKey = L"Jump";
	//		else if (m_tPrevInfo.fpPrevPos.y < pos.y)
	//			strKey = L"Fall";

	//		// 이렇게 할 거면 키입력으로 하는 거랑 다를 게 없는 듯
	//		//if (m_uiCheck & SP_SLASH1)
	//		//	strKey = L"Slash1";
	//		//else if (m_uiCheck & SP_SLASH2)
	//		//	strKey = L"Slash2";
	//		//else if (m_uiCheck & SP_UPSLASH)
	//		//	strKey = L"UpSlash";
	//		//else if (m_uiCheck & SP_DOWNSLASH)
	//		//	strKey = L"DownSlash";
	//		//else if (m_uiCheck & SP_FIRE)
	//		//	strKey = L"Fire";
	//		//else if (m_uiCheck & SP_FOCUS)
	//	}
	//}
	//addDirAndPlay(strKey);
#pragma endregion
}

//void CPlayer::addDirAndPlay(const wstring& keyWord)
//{
//	wstring strKey = keyWord;
//
//	if (m_uiCheck & SP_DIR)
//		strKey += L"_R";
//	else
//		strKey += L"_L";
//
//	PLAY(strKey);
//}

// TODO : 현재 애니메이션 준비동작까지 반복돼서 같은 동작 오래 지속하면 부자연스러움
	// 애니메이션 반복 여부 설정
// TODO : 한 번씩 키 씹히는 것 같은데
void CPlayer::update()
{
	if (KEY_ON('P')) g_bDebug = !g_bDebug;

	////////////////////////////
	// 임시 // 회전테스트
	// T Y U I 
	// G H J
	//if (KEY_ON('Q'))
	//{
	//	createRotTester();
	//}
	 // 임시 // 타일 없어서

	/*fPoint pos = getPos();
	if (pos.y > 1518.f)
	{
		pos.y = 1518.f;
		m_uiCheck &= ~(SP_AIR);
		m_uiCheck &= ~(SP_GODOWN);
		m_uiCheck &= ~(SP_DBJUMP);
		m_tInfo.fGravity = 0.f;
	}
	setPos(pos);*/

	/////////////////////////

	//playAnim();					// 
	if (nullptr != m_pAI)
		m_pAI->update(m_uiCheck);
	if (nullptr != getAnimator())
		getAnimator()->update();

	checkUpdate();
	
	//renewPrevInfo(getPos());			// anim 출력 후 이전 상황 갱신
}

void CPlayer::render(HDC hDC)
{
	if (g_bDebug)
		printInfo(hDC);

	componentRender(hDC);
	
}

void CPlayer::setAI(CAI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
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

void CPlayer::collisionKeep(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();

	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::MISSILE_MONSTER:
	case eOBJNAME::SHIELD:
	case eOBJNAME::BOSS:
	{
		if (!(m_uiCheck & SP_NODMG))
		{
			m_tInfo.fvKnockBackDir = (getPos() - pTarget->getPos());

			if (--m_tInfo.uiHP <= 0)
				changeAIState(m_pAI, eSTATE_PLAYER::DEATH);
			else
				changeAIState(m_pAI, eSTATE_PLAYER::STUN);
		}
		break;
	}
	case eOBJNAME::ATTACK:
	{
		// 이렇게 많이 타고 들어가도 되나 // attack도 몬스터 플레이어 나눠야 하나
		// ((CAttack*)pOther->getOwner())->getOwner()->getName()
		
		break;
	}

	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::LEFT:
		{	// TODO state::hang
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (pOther->getOffset().x - pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			break;
		}
		case eDIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (pOther->getOffset().x + pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			break;
		}
		break;
		}
	}
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	//벽 충돌
	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::TOP:
		{
			if (m_uiCheck & SP_GODOWN)
			{
				fPoint pos = getPos();
				pos.y = pOther->getPos().y - getCollider()->getOffset().y + pOther->getOffset().y
					- (pOther->getSize().y + getCollider()->getSize().y) / 2 + 1;
				setPos(pos);
				if (m_uiCheck & SP_AIR)
					m_uiCheck &= ~(SP_AIR);
				m_uiCheck &= ~(SP_DBJUMP);
				m_tInfo.iBottomCnt++;
			}
			break;
		}
		case eDIR::LEFT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				- pOther->getSize().x - getCollider()->getSize().x) / 2;
			setPos(pos);
			//m_tInfo.fSpdX = 0.f;
			break;
		}
		case eDIR::RIGHT:
		{
			fPoint pos = getPos();
			pos.x = pOther->getPos().x + (getCollider()->getOffset().x + pOther->getOffset().x
				+ pOther->getSize().x + getCollider()->getSize().x) / 2;
			setPos(pos);
			//m_tInfo.fSpdX = 0.f;
			break;
		}
		case eDIR::BOTTOM:	// 머리 콩
		{
			//m_tInfo.fSpdY = 0.f;
			fPoint pos = getPos();
			pos.y = pOther->getPos().y + (getCollider()->getOffset().y + pOther->getOffset().y
				+ pOther->getSize().y + getCollider()->getSize().y) / 2;
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
		switch (COLLRR(getCollider(), pOther))
		{
		case eDIR::TOP:
			if (--m_tInfo.iBottomCnt <= 0)
			{
				changeAIState(m_pAI, eSTATE_PLAYER::FALL);
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

	pMissile->setTex(L"Missile_player", L"texture\\missile\\missile_player.bmp");
	
	if (m_uiCheck & SP_DIR)
	{
		mPos.x += getSize().x / 2.f;
		mDir = 1.f;
		pMissile->createAnim(L"Missile_player_R", pMissile->getTex(),
			fPoint(0.f, 0.f), fPoint(254.f, 108.f), fPoint(254.f, 0.f), 0.15f, 4, false);
		pMissile->PLAY(L"Missile_player_R");
	}
	else
	{
		mPos.x -= getSize().x / 2.f;
		mDir = -1.f;
		pMissile->createAnim(L"Missile_player_L", pMissile->getTex(),
			fPoint(762.f, 108.f), fPoint(254.f, 108.f), fPoint(-254.f, 0.f), 0.15f, 4, false);
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

//void CPlayer::renewPrevInfo(fPoint pos)
//{
//	m_tPrevInfo.fpPrevPos = pos;
//	m_tPrevInfo.uiPrevHP = m_tInfo.uiHP;
//}

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
	m_pAI->getCurState()->printInfo(hDC);

	fPoint pos = getPos();

	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufGrav[255] = {};

	wchar_t bufHP[255] = {};
	wchar_t bufSoul[255] = {};
	wchar_t bufBot[255] = {};

	swprintf_s(bufX, L"x = %d", (int)pos.x);
	swprintf_s(bufY, L"y = %d", (int)pos.y);
	swprintf_s(bufGrav, L"grav = %.2f", m_tInfo.fGravity);

	swprintf_s(bufHP, L"HP = %d", (int)m_tInfo.uiHP);
	swprintf_s(bufSoul, L"Soul = %d", (int)m_tInfo.uiSoul);
	swprintf_s(bufBot, L"BottomCnt = %d", (int)m_tInfo.iBottomCnt);


	pos = rendPos(pos);

	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 75, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 90, bufY, (int)wcslen(bufY));
	TextOutW(hDC, (int)pos.x - 20, (int)pos.y + 105, bufGrav, (int)wcslen(bufGrav));

	TextOutW(hDC, (int)pos.x - 140, (int)pos.y + 75, bufHP, (int)wcslen(bufHP));
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y + 90, bufSoul, (int)wcslen(bufSoul));
	TextOutW(hDC, (int)pos.x - 140, (int)pos.y + 105, bufBot, (int)wcslen(bufBot));


	if (m_uiCheck & SP_NODMG)
	{
		wchar_t bufNoDmg[255] = {};
		swprintf_s(bufNoDmg, L"NoDmg %.2f", m_tInfo.fNoDmgTimer);
		TextOutW(hDC, (int)pos.x - 140, (int)pos.y - 75, bufNoDmg, (int)wcslen(bufNoDmg));
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

	// 
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