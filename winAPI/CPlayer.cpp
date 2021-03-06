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
#include "CMonster.h"
#include "SelectGDI.h"
#include "CEffect.h"

#pragma region Include_State
#include "CState_Player.h"
#include "CState_Idle.h"
#include "CState_Run.h"
#include "CState_Jump.h"
#include "CState_Fall.h"
#include "CState_Slash.h"
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


CPlayer::CPlayer()
{
	m_pTex = loadTex(L"PlayerTex", L"texture\\player\\player_tex.bmp");
	setName(eOBJNAME::PLAYER);
	setSize(fPoint(P_SIZEX, P_SIZEY));

	m_tInfo = {};
	m_tInfo.uiHP = 5;
	m_tInfo.fSpdX = (float)P_SPDX;
	m_tInfo.fGravity = (float)P_GRAV;
	m_tInfo.fKnockBackSpd = P_KB_SPD;

	m_tPrevInfo = {};
	m_pStatus = nullptr;
	m_uiCheck = 0;

	createCollider();
	getCollider()->setSize(fPoint(44.f, 106.f));
	getCollider()->setOffset(fPoint(0.f, 10.f));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();

#pragma region createAnimation

	createAnim(L"Idle_R",		m_pTex,	fPoint(0.f, 0.f),			fPoint(60.f, 127.f),		fPoint(60.f, 0.f),			0.25f,	6);
	createAnim(L"Idle_L",		m_pTex,	fPoint(300.f, 127.f),		fPoint(60.f, 127.f),		fPoint(-60.f, 0.f),			0.25f,	6);

	createAnim(L"Idle2Run_R",	m_pTex,	fPoint(360.f, 0.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	4, false);
	createAnim(L"Idle2Run_L",	m_pTex,	fPoint(1262.f, 127.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	4, false);

	getAnimator()->findAnimation(L"Idle2Run_R")->setAllOffset(fPoint(0.f, 6.f));
	getAnimator()->findAnimation(L"Idle2Run_L")->setAllOffset(fPoint(0.f, 6.f));

	createAnim(L"Run_R",		m_pTex,	fPoint(688.f, 0.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.2f,	8);
	createAnim(L"Run_L",		m_pTex,	fPoint(934.f, 127.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.2f,	8);

	createAnim(L"Jump_R",		m_pTex,	fPoint(1344.f, 0.f),		fPoint(77.f, 127.f),		fPoint(77.f, 0.f),			0.2f,	6, false);
	createAnim(L"Jump_L",		m_pTex,	fPoint(1729.f, 127.f),		fPoint(77.f, 127.f),		fPoint(-77.f, 0.f),			0.2f,	6, false);

	createAnim(L"Fall_R",		m_pTex,	fPoint(1806.f, 0.f),		fPoint(87.f, 127.f),		fPoint(87.f, 0.f),			0.2f,	6, false);
	createAnim(L"Fall_L",		m_pTex,	fPoint(2241.f, 127.f),		fPoint(87.f, 127.f),		fPoint(-87.f, 0.f),			0.2f,	6, false);

	createAnim(L"Land_R",		m_pTex,	fPoint(2328.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.8f,	1, false);
	createAnim(L"Land_L",		m_pTex,	fPoint(2480.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.8f,	1, false);

	getAnimator()->findAnimation(L"Land_R")->setAllOffset(fPoint(0.f, 8.f));
	getAnimator()->findAnimation(L"Land_L")->setAllOffset(fPoint(0.f, 8.f));

	createAnim(L"Land2Idle_R",	m_pTex,	fPoint(2404.f, 0.f),		fPoint(76.f, 127.f),		fPoint(76.f, 0.f),			0.2f,	2, false);
	createAnim(L"Land2Idle_L",	m_pTex,	fPoint(2404.f, 127.f),		fPoint(76.f, 127.f),		fPoint(-76.f, 0.f),			0.2f,	2, false);

	createAnim(L"Stun_R",		m_pTex,	fPoint(2556.f, 2.f),		fPoint(94.f, 126.f),		fPoint(94.f, 0.f),			0.3f,	1, false);
	createAnim(L"Stun_L",		m_pTex,	fPoint(2556.f, 129.f),		fPoint(94.f, 126.f),		fPoint(94.f, 0.f),			0.3f,	1, false);

	createAnim(L"Slash1_R",		m_pTex,	fPoint(0.f, 254.f),			fPoint(82.f, 127.f),		fPoint(82.f, 0.f),			0.06f,	5, false);
	createAnim(L"Slash1_L",		m_pTex,	fPoint(328.f, 381.f),		fPoint(82.f, 127.f),		fPoint(-82.f, 0.f),			0.06f,	5, false);

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

	pStatus->addState(new CState_Slash(eSTATE_PLAYER::SLASH1));
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
	if (KEY_ON('P')) g_bDebug = !g_bDebug;			// ?????? ????

	if (nullptr != m_pStatus)
		m_pStatus->update(m_uiCheck);

	if (nullptr != getAnimator())
		getAnimator()->update();


	if (m_tInfo.fKnockBackTimer > 0.f && !(m_uiCheck & SP_DEATH))
	{	// ???? ????
		fPoint pos = getPos();

		m_tInfo.fKnockBackTimer -= fDT;

		if (m_tInfo.fKnockBackTimer < 0.f)
		{
			m_tInfo.fKnockBackTimer = 0.f;
		}

		m_tInfo.fvKnockBackDir.normalize();

		pos.x += m_tInfo.fvKnockBackDir.x * m_tInfo.fKnockBackSpd * fDT;

		//if (m_uiCheck & SP_AIR || m_tInfo.fvKnockBackDir.y <= 0.f)
		//{	// ?????? ?????? y ?????? ?????? ???????? // ?????? ?????? ???? ????
		pos.y += m_tInfo.fvKnockBackDir.y * m_tInfo.fKnockBackSpd * fDT;
		//}
		setPos(pos);
	}


	checkUpdate();
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
	{	// ???? ???????? ???? ?????? landTimer ????
		m_tInfo.fLandTimer += fDT;
	}
	else
	{
		m_tInfo.fLandTimer = 0.f;
	}

	if (m_tInfo.fAtkDelay > 0.f)
	{
		m_tInfo.fAtkDelay -= fDT;

		if (m_tInfo.fAtkDelay < 0.f)
			m_tInfo.fAtkDelay = 0.f;
	}
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
	case eOBJNAME::MONS_BEE:
	case eOBJNAME::MONS_MUSH:
	case eOBJNAME::SHIELD:
	case eOBJNAME::BOSS:
	{
		if (!(m_uiCheck & SP_NODMG) && !((CMonster*)pTarget)->isCheck(SM_DEATH))
		{	// ???? ???? ?????? ???????? ???????? ???? ?????? ???? ????
			m_tInfo.fvKnockBackDir = (getPos() - pTarget->getPos());
			m_tInfo.fKnockBackTimer = 0.2f;

			fPoint pos = getPos();

			CEffect* pEff = new CEffect;
			pEff->load(L"Effect_hitCrack", L"texture\\effect\\effect_hitcrack.bmp");
			pEff->setDuration(0.6f);

			pEff->createAnim(L"effect_hitcrack", pEff->getTex(),
				fPoint(0, 0), fPoint(838, 168), fPoint(838, 0), 0.2f, 3, false);

			pEff->setPos(pos);
			pEff->PLAY(L"effect_hitcrack");
			createObj(pEff, eOBJ::EFFECT);

			if (--m_tInfo.uiHP <= 0)
				changeMyState(m_pStatus, eSTATE_PLAYER::DEATH);
			else
				changeMyState(m_pStatus, eSTATE_PLAYER::STUN);
		}
		break;
	}

	case eOBJNAME::WALL:
	{
		fPoint pos = getPos();
		if (pos.x < pOther->getPos().x && m_tPrevInfo.fpPrevPos.x < pos.x)
		{	// ???????? ?????????? ???????? ???? ????
			pos.x = pOther->getPos().x - pOther->getSize().x / 2.f + pOther->getOffset().x
				- getCollider()->getSize().x / 2.f + getCollider()->getOffset().x - 1;
			setPos(pos);
		}

		else if (pos.x > pOther->getPos().x && m_tPrevInfo.fpPrevPos.x > pos.x)
		{	// ?????????? ???????? ???????? ???? ????
			pos.x = pOther->getPos().x + pOther->getSize().x / 2.f + pOther->getOffset().x
				+ getCollider()->getSize().x / 2.f - getCollider()->getOffset().x + 1;
			setPos(pos);
		}

		break;
	}

	case eOBJNAME::GROUND:
	{
		if (isTopCollOnly(getCollider(), pOther))
		{	// ???????? ???? ????
			fPoint pos = getPos();

			pos.y = pOther->getPos().y - pOther->getSize().y / 2.f
				- getCollider()->getSize().y / 2.f - getCollider()->getOffset().y  + 1;
			setPos(pos);

			tPlayerInfo info = getPlayerInfo();
			if (info.iBottomCnt <= 0)
			{
				info.iBottomCnt = 1;
				setPlayerInfo(info);
				m_uiCheck &= ~(SP_AIR);
				m_uiCheck &= ~(SP_GODOWN);
				m_tInfo.fSpdY = 0.f;
			}
		}
		else if (isBottomCollOnly(getCollider(), pOther))
		{	// ??????
			fPoint pos = getPos();

			pos.y = pOther->getPos().y + pOther->getSize().y / 2.f
				+ getCollider()->getSize().y / 2.f + getCollider()->getOffset().y;
			setPos(pos);
		}

		break;
	}
	}
}

void CPlayer::collisionEnter(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();

	switch (pTarget->getName())
	{	//?? ????
	case eOBJNAME::GROUND:
	{
		if (isTopCollOnly(getCollider(), pOther))
		{	// ??
			if (m_uiCheck & SP_GODOWN)
			{	// ???????? ???? ???? ????
				fPoint pos = getPos();

				pos.y = pOther->getPos().y - pOther->getSize().y / 2.f + pOther->getOffset().y
					- getCollider()->getSize().y / 2.f - getCollider()->getOffset().y + 1;

				setPos(pos);

				if (m_tInfo.fLandTimer > P_LAND_TIMER)
				{
					changeMyState(m_pStatus, eSTATE_PLAYER::LAND);
				}
				else
				{
					CSoundManager::getInst()->addSound(L"hero_land_soft", L"sound\\player\\hero_land_soft.wav");
					CSoundManager::getInst()->play(L"hero_land_soft", 0.1f);
					changeMyState(m_pStatus, eSTATE_PLAYER::IDLE);
				}

				m_uiCheck &= ~(SP_AIR);
				m_uiCheck &= ~(SP_GODOWN);
				m_uiCheck &= ~(SP_DASH);
				m_tInfo.iBottomCnt++;
				m_tInfo.fSpdY = 0.f;
			}
		}
		else if (isBottomCollOnly(getCollider(), pOther))
		{	// ????
			m_tInfo.fSpdY = 0;
			fPoint pos = getPos();

			pos.y = pOther->getPos().y + pOther->getSize().y / 2.f + pOther->getOffset().y
				+ getCollider()->getSize().y / 2.f - getCollider()->getOffset().y;

			setPos(pos);
		}
		break;
	}
	case eOBJNAME::WALL:
	{
		fPoint pos = getPos();
		if (pos.x < pOther->getPos().x && m_tPrevInfo.fpPrevPos.x < pos.x)
		{	// ???????? ?????????? ???????? ???? ????
			pos.x = pOther->getPos().x - pOther->getSize().x / 2.f + pOther->getOffset().x
				- getCollider()->getSize().x / 2.f + getCollider()->getOffset().x - 1;
			setPos(pos);
		}
	
		else if (pos.x > pOther->getPos().x && m_tPrevInfo.fpPrevPos.x > pos.x)
		{	// ?????????? ???????? ???????? ???? ????
			pos.x = pOther->getPos().x + pOther->getSize().x / 2.f + pOther->getOffset().x
				+ getCollider()->getSize().x / 2.f - getCollider()->getOffset().x + 1;
			setPos(pos);
		}
		
		break;
	}
	
	case eOBJNAME::MONS_BEETLE:
	case eOBJNAME::MONS_MUSH:
	case eOBJNAME::MONS_BEE:
	case eOBJNAME::BOSS:
	{
		if (((CMonster*)pTarget)->isCheck(SM_DEATH))
		{	// ???????? ???? ???? ???? ????
			break;
		}
	}
	case eOBJNAME::MISSILE_MONSTER:
	case eOBJNAME::SHIELD:
	{
		if (!(m_uiCheck & SP_NODMG))
		{	// ???? ???? ?????? ??????
			m_tInfo.fvKnockBackDir = (getPos() - pTarget->getPos());
			m_tInfo.fKnockBackTimer = 0.2f;

			fPoint pos = getPos();

			CEffect* pEff = new CEffect;
			pEff->load(L"Effect_hitCrack", L"texture\\effect\\effect_hitcrack.bmp");
			pEff->setDuration(0.6f);

			pEff->createAnim(L"effect_hitcrack", pEff->getTex(),
				fPoint(0, 0), fPoint(838, 168), fPoint(838, 0), 0.2f, 3, false);

			pEff->setPos(pos);
			pEff->PLAY(L"effect_hitcrack");
			createObj(pEff, eOBJ::EFFECT);

			if (--m_tInfo.uiHP <= 0)
				changeMyState(m_pStatus, eSTATE_PLAYER::DEATH);
			else
				changeMyState(m_pStatus, eSTATE_PLAYER::STUN);
		}
		break;
	}
	}

}

void CPlayer::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::GROUND:
		if (!isTopCollOnly(getCollider(), pOther))
		{	
			if (--m_tInfo.iBottomCnt <= 0 && m_pStatus->getCurState()->getState() != eSTATE_PLAYER::JUMP)
			{	// ?????? ???? exit???? ?????? fall?? ?????? ???? ?? ??????
				m_tInfo.iBottomCnt = 0;
				m_uiCheck |= SP_AIR;

				if (m_pStatus->getCurState()->getState() != eSTATE_PLAYER::DASH)
					changeMyState(m_pStatus, eSTATE_PLAYER::FALL);
			}
		}
		break;
	}
}

void CPlayer::createMissile()
{
	fPoint mPos = getPos();
	float mDir = 1.f;

	CMissile* pMissile = new CMissile;
	pMissile->setTex(L"Missile_player", L"texture\\attack\\missile_player.bmp");

	CEffect* pEff = new CEffect;
	pEff->load(L"effect_player_firepang", L"texture\\effect\\effect_player_firepang.bmp");

	if (m_uiCheck & SP_DIR)
	{
		mPos.x += getSize().x / 2.f;
		mDir = 1.f;
		pMissile->createAnim(L"Msl_pl", pMissile->getTex(),
			fPoint(0.f, 0.f), fPoint(254.f, 108.f), fPoint(254.f, 0.f), 0.15f, 4, false);

		pEff->createAnim(L"effect_player_firepang", pEff->getTex(),
			fPoint(540, 202), fPoint(270, 202), fPoint(-270, 0), 0.13f, 3, false);
	}
	else
	{
		mPos.x -= getSize().x / 2.f;
		mDir = -1.f;
		pMissile->createAnim(L"Msl_pl", pMissile->getTex(),
			fPoint(762.f, 108.f), fPoint(254.f, 108.f), fPoint(-254.f, 0.f), 0.15f, 4, false);

		pEff->createAnim(L"effect_player_firepang", pEff->getTex(),
			fPoint(0, 0), fPoint(270, 202), fPoint(270, 0), 0.13f, 3, false);
	}
	pMissile->PLAY(L"Msl_pl");
	pMissile->setPos(fPoint(mPos.x, mPos.y));
	pMissile->setSize(fPoint(40.f, 30.f));
	pMissile->getCollider()->setSize(fPoint(100.f, 60.f));
	pMissile->setDir(fVec2(mDir, 0.f));
	pMissile->setName(eOBJNAME::MISSILE_PLAYER);
	pMissile->setSpeed(1300.f);
	
	createObj(pMissile, eOBJ::MISSILE_PLAYER);

	
	pEff->setPos(mPos);
	pEff->setDuration(0.39f);
	pEff->PLAY(L"effect_player_firepang");

	createObj(pEff, eOBJ::EFFECT);
}

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

	// bufX,Y ???????? ???? ???????? ??
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

void CPlayer::updatePrevInfo(tPlayerPrevInfo prevInfo)
{
	m_tPrevInfo = prevInfo;
}

void CPlayer::slash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setTex(L"Player_Slash1", L"texture\\attack\\attack_slash.bmp");
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->getCollider()->setSize(fPoint(PSLASH_WIDTH, PSLASH_HEIGHT));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		mPos.x += PSLASH_OFFSETX;
		pAttack->setDir(eDIR::RIGHT);
		pAttack->createAnim(L"Player_Slash1", pAttack->getTex(),
			fPoint(0.f, 0.f), fPoint(151.f, 129.f), fPoint(151.f, 0.f), 0.1f, 2, false);

	}
	else
	{
		mPos.x -= PSLASH_OFFSETX;
		pAttack->setDir(eDIR::LEFT);
		pAttack->createAnim(L"Player_Slash1", pAttack->getTex(),
			fPoint(151.f, 129.f), fPoint(151.f, 129.f), fPoint(-151.f, 0.f), 0.1f, 2, false);
	}
	
	pAttack->PLAY(L"Player_Slash1");
	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.2f);
	
	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::upSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setTex(L"Player_UpSlash", L"texture\\attack\\attack_upslash.bmp");
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->getCollider()->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		pAttack->createAnim(L"Player_UpSlash", pAttack->getTex(),
			fPoint(0.f, 0.f), fPoint(129.f, 151.f), fPoint(129.f, 0.f), 0.1f, 2, false);
	}
	else
	{
		pAttack->createAnim(L"Player_UpSlash", pAttack->getTex(),
			fPoint(129.f, 151.f), fPoint(129.f, 151.f), fPoint(-129.f, 0.f), 0.1f, 2, false);
	}
	pAttack->PLAY(L"Player_UpSlash");
	pAttack->setDir(eDIR::TOP);

	mPos.y -= PSLASH_OFFSETY;
	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.2f);

	createObj(pAttack, eOBJ::ATTACK);
}

void CPlayer::downSlash()
{
	fPoint mPos = getPos();

	CAttack* pAttack = new CAttack;
	pAttack->setTex(L"Player_DownSlash", L"texture\\attack\\attack_downslash.bmp");
	pAttack->setName(eOBJNAME::ATTACK);
	pAttack->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->getCollider()->setSize(fPoint(PSLASH_HEIGHT, PSLASH_WIDTH));
	pAttack->setOwner(this);

	if (m_uiCheck & SP_DIR)
	{
		pAttack->createAnim(L"Player_DownSlash", pAttack->getTex(),
			fPoint(0.f, 0.f), fPoint(129.f, 151.f), fPoint(129.f, 0.f), 0.1f, 2, false);
	}
	else
	{
		pAttack->createAnim(L"Player_DownSlash", pAttack->getTex(),
			fPoint(129.f, 151.f), fPoint(129.f, 151.f), fPoint(-129.f, 0.f), 0.1f, 2, false);
	}

	pAttack->PLAY(L"Player_DownSlash");
	pAttack->setDir(eDIR::BOTTOM);

	mPos.y += PSLASH_OFFSETY;
	pAttack->setPos(fPoint(mPos.x, mPos.y));
	pAttack->setDura(0.2f);

	createObj(pAttack, eOBJ::ATTACK);
}