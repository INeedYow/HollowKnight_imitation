#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CStatus.h"

#include "CAI.h"
#include "CMonster_Melee.h"
#include "CMonster_Fly.h"
#include "CState_Stop.h"
#include "CState_Shoot.h"
#include "CState_Patrol.h"
#include "CState_Trace.h"
#include "CState_Die.h"

#include "CAnimation.h"
#include "CAnimator.h"

CMonster::CMonster()
{
	setName(eOBJNAME::MONSTER);
	m_pTex = nullptr;
	m_pAI = nullptr;
	m_tInfo = {};
	m_tInfo.fKnockBackTimer = (float)SM_KBTIME;
	m_tInfo.fKnockBackSpd = 0.f;

	m_uiCheck = 0;

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::update()
{
	if (nullptr != m_pAI)
	{
		if (!(m_uiCheck & SM_TURN))					// 
			m_pAI->update(m_uiCheck);

		else if (m_uiCheck & SM_DEATH)
			m_pAI->update(m_uiCheck);
	}
	if (nullptr != getAnimator())
		getAnimator()->update();

	if (m_tInfo.fKnockBackTimer > 0.f && !(m_uiCheck & SM_DEATH))
	{
		fPoint pos = getPos();
		m_tInfo.fvKnockBackDir.normalize();

		pos.x += m_tInfo.fvKnockBackDir.x * m_tInfo.fKnockBackSpd * fDT;
		pos.y += m_tInfo.fvKnockBackDir.y * m_tInfo.fKnockBackSpd * fDT;

		setPos(pos);

		m_tInfo.fKnockBackTimer -= fDT;
		if (m_tInfo.fKnockBackTimer < 0.f)
			m_tInfo.fKnockBackTimer = 0.f;
	}
}

void CMonster::setAI(CAI* pAI)
{
	m_pAI = pAI;
	m_pAI->m_pOwner = this;
}

void CMonster::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
}

const tMonsInfo& CMonster::getMonsInfo()
{
	return m_tInfo;
}

CTexture* CMonster::getTex()
{
	return m_pTex;
}

CAI* CMonster::getAI()
{
	return m_pAI;
}

void CMonster::setMonsInfo(const tMonsInfo& info)
{
	m_tInfo = info;

	if (info.iHP <= 0 && !(m_uiCheck & SM_DEATH))
	{
		death();
		m_uiCheck |= SM_DEATH;
	}
}

void CMonster::setCheck(UINT chk, bool isOn)
{
	if (isOn)
		m_uiCheck |= chk;
	else
		m_uiCheck &= ~(chk);
}

bool CMonster::isCheck(UINT chk)
{
	return m_uiCheck & chk;
}

void CMonster::playAnim(const wstring& keyWord)
{
	wstring strKey;

	switch (getName())
	{
	case eOBJNAME::MONS_BEETLE:
		strKey = L"BT_";
		break;

	case eOBJNAME::MONS_MUSH:
		strKey = L"MS_";
		break;
	case eOBJNAME::MONS_BEE:
		strKey = L"BE_";
		break;
	}
	strKey += keyWord;

	if (m_tInfo.fvDir.x > 0.f)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
}

void CMonster::create(eOBJNAME eName, fPoint pos)
{
	CMonster* pMon = nullptr;
	tMonsInfo info = {};
	CAI* pAI = nullptr;

	switch (eName)
	{
	case eOBJNAME::MONS_BEETLE:
	{
		info.iHP = M_BT_HP;
		info.fSpdX = M_BT_SPD;
		info.fSpdY = 0.f;
		info.fNoticeRange = M_BT_TRACE_RNG;

		pMon = new CMonster_Melee;
		pMon->setPos(pos);	//
		pMon->setName(eOBJNAME::MONS_BEETLE);	//
		pMon->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
		pMon->getCollider()->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
		pMon->getCollider()->setOffset(fPoint(0.f, 10.f));
		pMon->setMonsInfo(info);
		pMon->setCheck(SM_TRACE, true);
		pMon->setCheck(SM_SHOOT, false);

		pAI = new CAI;
		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
		pAI->addState(new CState_Trace(eSTATE_MONS::TRACE));
		pAI->addState(new CState_Die(eSTATE_MONS::DIE));

		pAI->setCurState(eSTATE_MONS::STOP);
		pMon->setAI(pAI);

		pMon->createAnimator();
		pMon->setTex(L"Mons_BeetleTex", L"texture\\monster\\mons_beetle\\mons_beetle.bmp");

		pMon->createAnim(L"BT_Stop_R", pMon->getTex(),
			fPoint(0, 0), fPoint(118, 192), fPoint(118, 0), 0.2f, 6);
		pMon->createAnim(L"BT_Stop_L", pMon->getTex(),
			fPoint(590, 192), fPoint(118, 192), fPoint(-118, 0), 0.2f, 6);

		pMon->createAnim(L"BT_Patrol_R", pMon->getTex(),
			fPoint(708, 0), fPoint(139, 192), fPoint(139, 0), 0.2f, 7);
		pMon->createAnim(L"BT_Patrol_L", pMon->getTex(),
			fPoint(1542, 192), fPoint(139, 192), fPoint(-139, 0), 0.2f, 7);

		pMon->createAnim(L"BT_Turn_R", pMon->getTex(),
			fPoint(1681, 0), fPoint(104, 192), fPoint(104, 0), 0.25f, 2, false);
		pMon->createAnim(L"BT_Turn_L", pMon->getTex(),
			fPoint(1785, 192), fPoint(104, 192), fPoint(-104, 0), 0.25f, 2, false);

		pMon->createAnim(L"BT_TraceEnter_R", pMon->getTex(),
			fPoint(0, 384), fPoint(171, 190), fPoint(171, 0), 0.18f, 5, false);
		pMon->createAnim(L"BT_TraceEnter_L", pMon->getTex(),
			fPoint(684, 576), fPoint(171, 190), fPoint(-171, 0), 0.18f, 5, false);

		pMon->createAnim(L"BT_Trace_R", pMon->getTex(),
			fPoint(855, 394), fPoint(199, 180), fPoint(199, 0), 0.4f, 4);
		pMon->createAnim(L"BT_Trace_L", pMon->getTex(),
			fPoint(1452, 586), fPoint(199, 180), fPoint(-199, 0), 0.4f, 4);

		pMon->createAnim(L"BT_TraceExit_R", pMon->getTex(),
			fPoint(1649, 394), fPoint(132, 183), fPoint(132, 0), 0.36f, 1);
		pMon->createAnim(L"BT_TraceExit_L", pMon->getTex(),
			fPoint(1649, 586), fPoint(132, 183), fPoint(-132, 0), 0.36f, 1);

		pMon->createAnim(L"BT_Die_R", pMon->getTex(),
			fPoint(0, 770), fPoint(190, 136), fPoint(190, 0), 0.2f, 9, false);

		pMon->getAnimator()->findAnimation(L"BT_Die_R")->setAllOffset(fPoint(0.f, 30.f));

		pMon->createAnim(L"BT_Die_L", pMon->getTex(),
			fPoint(1520, 906), fPoint(190, 136), fPoint(-190, 0), 0.2f, 9, false);

		pMon->getAnimator()->findAnimation(L"BT_Die_L")->setAllOffset(fPoint(0.f, 30.f));

		pMon->PLAY(L"BT_Stop_L");
		break;
	}

	case eOBJNAME::MONS_MUSH:
	{
		info.iHP = M_MS_HP;
		info.fSpdX = M_MS_SPD;
		info.fSpdY = 0.f;

		pMon = new CMonster_Melee;
		pMon->setPos(pos);	//
		pMon->setName(eOBJNAME::MONS_MUSH);	//
		pMon->setSize(fPoint((float)M_MS_SIZEX, (float)M_MS_SIZEY));
		pMon->getCollider()->setSize(fPoint((float)M_MS_SIZEX, (float)M_MS_SIZEY));
		pMon->getCollider()->setOffset(fPoint(0.f, 10.f));
		pMon->setMonsInfo(info);
		pMon->setCheck(SM_TRACE, false);
		pMon->setCheck(SM_SHOOT, false);

		pAI = new CAI;
		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
		pAI->addState(new CState_Die(eSTATE_MONS::DIE));

		pAI->setCurState(eSTATE_MONS::STOP);
		pMon->setAI(pAI);

		pMon->createAnimator();
		pMon->setTex(L"Mons_MushTex", L"texture\\monster\\mons_mush\\mons_mush.bmp");

		pMon->createAnim(L"MS_Stop_R", pMon->getTex(),
			fPoint(125, 0), fPoint(125, 112), fPoint(125, 0), 0.5f, 1);
		pMon->createAnim(L"MS_Stop_L", pMon->getTex(),
			fPoint(250, 112), fPoint(125, 112), fPoint(-125, 0), 0.5f, 1);

		pMon->createAnim(L"MS_Patrol_R", pMon->getTex(),
			fPoint(0, 0), fPoint(125, 112), fPoint(125, 0), 0.25f, 4);
		pMon->createAnim(L"MS_Patrol_L", pMon->getTex(),
			fPoint(375, 112), fPoint(125, 112), fPoint(-125, 0), 0.25f, 4);

		pMon->createAnim(L"MS_Turn_R", pMon->getTex(),
			fPoint(500, 0), fPoint(123, 107), fPoint(123, 0), 0.25f, 2, false);
		pMon->createAnim(L"MS_Turn_L", pMon->getTex(),
			fPoint(623, 107), fPoint(123, 107), fPoint(-123, 0), 0.25f, 2, false);

		pMon->createAnim(L"MS_Die_R", pMon->getTex(),
			fPoint(0, 219), fPoint(151, 112), fPoint(151, 0), 0.35f, 3, false);
		pMon->createAnim(L"MS_Die_L", pMon->getTex(),
			fPoint(302, 331), fPoint(151, 112), fPoint(-151, 0), 0.35f, 3, false);

		pMon->PLAY(L"MS_Stop_L");
		break;
	}
	case eOBJNAME::MONS_BEE:
	{
		info.iHP = M_BE_HP;
		info.fSpdX = M_BE_SPD;
		info.fSpdY = M_BE_SPD;
		info.fDelay = M_BE_SHOOT_DELAY;
		info.fDura = M_BE_SHOOT_DURA;
		info.fAtkRange = M_BE_SHOOT_RNG;

		pMon = new CMonster_Fly;
		pMon->setPos(pos);	//
		pMon->setName(eOBJNAME::MONS_BEE);	//
		pMon->setSize(fPoint((float)M_BE_SIZEX, (float)M_BE_SIZEY));
		pMon->getCollider()->setSize(fPoint((float)M_BE_SIZEX, (float)M_BE_SIZEY));
		pMon->getCollider()->setOffset(fPoint(0.f, 4.f));
		pMon->setMonsInfo(info);
		pMon->setCheck(SM_TRACE, false);
		pMon->setCheck(SM_SHOOT, true);

		pAI = new CAI;
		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
		pAI->addState(new CState_Shoot(eSTATE_MONS::SHOOT));
		pAI->addState(new CState_Die(eSTATE_MONS::DIE));

		pAI->setCurState(eSTATE_MONS::STOP);
		pMon->setAI(pAI);

		pMon->createAnimator();
		pMon->setTex(L"Mons_BeeTex", L"texture\\monster\\mons_bee\\mons_bee.bmp");

		pMon->createAnim(L"BE_Stop_R", pMon->getTex(),
			fPoint(0, 0), fPoint(142, 122), fPoint(142, 0), 0.2f, 6);
		pMon->createAnim(L"BE_Stop_L", pMon->getTex(),
			fPoint(710, 122), fPoint(142, 122), fPoint(-142, 0), 0.2f, 6);

		pMon->createAnim(L"BE_Patrol_R", pMon->getTex(),
			fPoint(0, 0), fPoint(142, 122), fPoint(142, 0), 0.2f, 6);
		pMon->createAnim(L"BE_Patrol_L", pMon->getTex(),
			fPoint(710, 122), fPoint(142, 122), fPoint(-142, 0), 0.2f, 6);

		pMon->createAnim(L"BE_Turn_R", pMon->getTex(),
			fPoint(852, 0), fPoint(160, 122), fPoint(160, 0), 0.25f, 2, false);
		pMon->createAnim(L"BE_Turn_L", pMon->getTex(),
			fPoint(1012, 122), fPoint(160, 122), fPoint(-160, 0), 0.25f, 2, false);

		pMon->createAnim(L"BE_Die_R", pMon->getTex(),
			fPoint(0, 244), fPoint(151, 133), fPoint(151, 0), 0.2f, 6, false);
		pMon->createAnim(L"BE_Die_L", pMon->getTex(),
			fPoint(755, 377), fPoint(151, 133), fPoint(-151, 0), 0.2f, 6, false);

		pMon->createAnim(L"BE_Shoot_R", pMon->getTex(),
			fPoint(0, 521), fPoint(154, 117), fPoint(154, 0), 0.2f, 12, false);
		pMon->createAnim(L"BE_Shoot_L", pMon->getTex(),
			fPoint(1694, 638), fPoint(154, 117), fPoint(-154, 0), 0.2f, 12, false);

		pMon->PLAY(L"BE_Patrol_L");
		break;
	}
	}
	createObj(pMon, eOBJ::MONSTER);
}