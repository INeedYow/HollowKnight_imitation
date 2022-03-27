#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CStatus.h"

#include "CAI.h"
#include "CMonster_Melee.h"
#include "CState_Stop.h"
#include "CState_Attack.h"
#include "CState_Patrol.h"
#include "CState_Trace.h"
#include "CState_Die.h"

#include "CAnimation.h"
#include "CAnimator.h"

void CMonster::printInfo(HDC hDC)
{
}

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

// TODO 방향전환할 때 죽으면 turn anim 재생됨
void CMonster::update()
{
	if (nullptr != m_pAI && !(m_uiCheck & SM_TURN))		// 방향전환 중일 때 
		m_pAI->update(m_uiCheck);
	if (nullptr != getAnimator())
		getAnimator()->update();

	if (m_tInfo.fKnockBackTimer > 0.f)
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

	}
	strKey += keyWord;

	if (m_tInfo.fvDir.x > 0.f)
		strKey += L"_R";
	else
		strKey += L"_L";

	PLAY(strKey);
}

CMonster* CMonster::create(eOBJNAME eName, fPoint pos)
{
	CMonster_Melee* pMonsMl = nullptr;
	tMonsInfo info = {};
	CAI* pAI = nullptr;

	switch (eName)
	{
	case eOBJNAME::MONS_BEETLE:
	{
		info.iHP = M_BT_HP;
		info.fSpd = M_BT_SPD;
		info.fTraceRange = M_BT_TRACE_RNG;

		pMonsMl = new CMonster_Melee;
		pMonsMl->setPos(pos);	//
		pMonsMl->setName(eOBJNAME::MONS_BEETLE);	//
		pMonsMl->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
		pMonsMl->getCollider()->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
		pMonsMl->getCollider()->setOffset(fPoint(0.f, 10.f));
		pMonsMl->setMonsInfo(info);
		pMonsMl->setCheck(SM_TRACE, true);

		CAI* pAI = new CAI;
		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
		pAI->addState(new CState_Trace(eSTATE_MONS::TRACE));
		pAI->addState(new CState_Die(eSTATE_MONS::DIE));

		pAI->setCurState(eSTATE_MONS::STOP);
		pMonsMl->setAI(pAI);

		pMonsMl->createAnimator();
		pMonsMl->setTex(L"Mons_BeetleTex", L"texture\\monster\\mons_beetle\\mons_beetle.bmp");

		pMonsMl->createAnim(L"BT_Stop_R", pMonsMl->getTex(),
			fPoint(0, 0), fPoint(118, 192), fPoint(118, 0), 0.2f, 6);
		pMonsMl->createAnim(L"BT_Stop_L", pMonsMl->getTex(),
			fPoint(590, 192), fPoint(118, 192), fPoint(-118, 0), 0.2f, 6);

		pMonsMl->createAnim(L"BT_Patrol_R", pMonsMl->getTex(),
			fPoint(708, 0), fPoint(139, 192), fPoint(139, 0), 0.2f, 7);
		pMonsMl->createAnim(L"BT_Patrol_L", pMonsMl->getTex(),
			fPoint(1542, 192), fPoint(139, 192), fPoint(-139, 0), 0.2f, 7);

		pMonsMl->createAnim(L"BT_Turn_R", pMonsMl->getTex(),
			fPoint(1681, 0), fPoint(104, 192), fPoint(104, 0), 0.25f, 2, false);
		pMonsMl->createAnim(L"BT_Turn_L", pMonsMl->getTex(),
			fPoint(1785, 192), fPoint(104, 192), fPoint(-104, 0), 0.25f, 2, false);

		pMonsMl->createAnim(L"BT_TraceEnter_R", pMonsMl->getTex(),
			fPoint(0, 384), fPoint(171, 190), fPoint(171, 0), 0.18f, 5, false);
		pMonsMl->createAnim(L"BT_TraceEnter_L", pMonsMl->getTex(),
			fPoint(684, 576), fPoint(171, 190), fPoint(-171, 0), 0.18f, 5, false);

		pMonsMl->createAnim(L"BT_Trace_R", pMonsMl->getTex(),
			fPoint(855, 394), fPoint(199, 180), fPoint(199, 0), 0.4f, 4);
		pMonsMl->createAnim(L"BT_Trace_L", pMonsMl->getTex(),
			fPoint(1452, 586), fPoint(199, 180), fPoint(-199, 0), 0.4f, 4);

		pMonsMl->createAnim(L"BT_TraceExit_R", pMonsMl->getTex(),
			fPoint(1649, 394), fPoint(132, 183), fPoint(132, 0), 0.36f, 1);
		pMonsMl->createAnim(L"BT_TraceExit_L", pMonsMl->getTex(),
			fPoint(1649, 586), fPoint(132, 183), fPoint(-132, 0), 0.36f, 1);

		pMonsMl->createAnim(L"BT_Die_R", pMonsMl->getTex(),
			fPoint(0, 770), fPoint(190, 136), fPoint(190, 0), 0.22f, 9, false);
		pMonsMl->createAnim(L"BT_Die_L", pMonsMl->getTex(),
			fPoint(1520, 906), fPoint(190, 136), fPoint(-190, 0), 0.22f, 9, false);

		pMonsMl->PLAY(L"BT_Stop_L");
		break;
	}

	case eOBJNAME::MONS_MUSH:
	{
		info.iHP = M_MS_HP;
		info.fSpd = M_MS_SPD;

		pMonsMl = new CMonster_Melee;
		pMonsMl->setPos(pos);	//
		pMonsMl->setName(eOBJNAME::MONS_MUSH);	//
		pMonsMl->setSize(fPoint((float)M_MS_SIZEX, (float)M_MS_SIZEY));
		pMonsMl->getCollider()->setSize(fPoint((float)M_MS_SIZEX, (float)M_MS_SIZEY));
		pMonsMl->getCollider()->setOffset(fPoint(0.f, 10.f));
		pMonsMl->setMonsInfo(info);
		pMonsMl->setCheck(SM_TRACE, false);

		CAI* pAI = new CAI;
		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
		pAI->addState(new CState_Die(eSTATE_MONS::DIE));

		pAI->setCurState(eSTATE_MONS::STOP);
		pMonsMl->setAI(pAI);

		pMonsMl->createAnimator();
		pMonsMl->setTex(L"Mons_MushTex", L"texture\\monster\\mons_mush\\mons_mush.bmp");

		pMonsMl->createAnim(L"MS_Stop_R", pMonsMl->getTex(),
			fPoint(125, 0), fPoint(125, 112), fPoint(125, 0), 0.5f, 1);
		pMonsMl->createAnim(L"MS_Stop_L", pMonsMl->getTex(),
			fPoint(250, 112), fPoint(125, 112), fPoint(-125, 0), 0.5f, 1);

		pMonsMl->createAnim(L"MS_Patrol_R", pMonsMl->getTex(),
			fPoint(0, 0), fPoint(125, 112), fPoint(125, 0), 0.25f, 4);
		pMonsMl->createAnim(L"MS_Patrol_L", pMonsMl->getTex(),
			fPoint(375, 112), fPoint(125, 112), fPoint(-125, 0), 0.25f, 4);

		pMonsMl->createAnim(L"MS_Turn_R", pMonsMl->getTex(),
			fPoint(500, 0), fPoint(123, 107), fPoint(123, 0), 0.25f, 2, false);
		pMonsMl->createAnim(L"MS_Turn_L", pMonsMl->getTex(),
			fPoint(623, 107), fPoint(123, 107), fPoint(-123, 0), 0.25f, 2, false);

		pMonsMl->createAnim(L"MS_Die_R", pMonsMl->getTex(),
			fPoint(0, 219), fPoint(151, 112), fPoint(151, 0), 0.5f, 3, false);
		pMonsMl->createAnim(L"MS_Die_L", pMonsMl->getTex(),
			fPoint(302, 331), fPoint(151, 112), fPoint(-151, 0), 0.5f, 3, false);

		pMonsMl->PLAY(L"MS_Stop_L");
		break;
	}

	}
	return pMonsMl;
}