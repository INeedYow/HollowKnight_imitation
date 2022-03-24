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

CMonster::CMonster()
{
	setName(eOBJNAME::MONSTER);
	m_pTex = nullptr;
	m_pAI = nullptr;
	m_tInfo = {};
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
		m_pAI->update(m_uiCheck);
	if (nullptr != getAnimator())
		getAnimator()->update();
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
		info.fAtkRange = M_BT_ATK_RND;

		pMonsMl = new CMonster_Melee;
		pMonsMl->setPos(pos);	//
		pMonsMl->setName(eOBJNAME::MONS_BEETLE);	//
		pMonsMl->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
		pMonsMl->setMonsInfo(info);
		pMonsMl->getCollider()->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
		pMonsMl->getCollider()->setOffset(fPoint(0.f, 10.f));

		CAI* pAI = new CAI;
		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
		pAI->addState(new CState_Attack(eSTATE_MONS::ATTACK));
		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
		pAI->addState(new CState_Trace(eSTATE_MONS::TRACE));

		pAI->setCurState(eSTATE_MONS::STOP);
		pMonsMl->setAI(pAI);

		pMonsMl->createAnimator();
		pMonsMl->setTex(L"Mons_BeetleTex", L"texture\\monster\\mons_beetle\\mons_beetle.bmp");
		
		pMonsMl->createAnim(L"BT_Stop_R", pMonsMl->getTex(),
			fPoint(0,0), fPoint(118,192), fPoint(118,0), 0.2f, 6);
		pMonsMl->createAnim(L"BT_Stop_L", pMonsMl->getTex(),
			fPoint(590, 192), fPoint(118, 192), fPoint(-118, 0), 0.2f, 6);

		pMonsMl->createAnim(L"BT_Move_R", pMonsMl->getTex(),
			fPoint(708, 0), fPoint(139, 192), fPoint(139, 0), 0.2f, 7);
		pMonsMl->createAnim(L"BT_Move_L", pMonsMl->getTex(),
			fPoint(1542, 192), fPoint(139, 192), fPoint(-139, 0), 0.2f, 7);

		pMonsMl->createAnim(L"BT_Turn_R", pMonsMl->getTex(),
			fPoint(1681, 0), fPoint(104, 192), fPoint(104, 0), 0.35f, 2);
		pMonsMl->createAnim(L"BT_Turn_L", pMonsMl->getTex(),
			fPoint(1785, 192), fPoint(104, 192), fPoint(-104, 0), 0.35f, 2);

		pMonsMl->PLAY(L"BT_Stop_L");
		break;
	}
	return pMonsMl;
	}

	return nullptr;

}

void CMonster::setAI(CAI* pAI)
{
	m_pAI = pAI;
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

void CMonster::setMonsInfo(const tMonsInfo& info)
{
	m_tInfo = info;

	if (info.iHP <= 0)
		death();
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
