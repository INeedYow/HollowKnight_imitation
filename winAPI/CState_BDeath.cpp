#include "framework.h"
#include "CState_BDeath.h"
#include "CBoss_Markoth.h"
#include "CSpear.h"
#include "CShield.h"
#include "CEffect_Move.h"
#include "CEffect.h"

#include "SelectGDI.h"

CState_BDeath::CState_BDeath(eSTATE_MONS state)
	:CState_Mons(state) 
{
	m_fDura = 0.f;
	m_fTimer = 0.f;
	m_fSpd = 0.f;
	m_iDegree = 0;
	m_fDecel = 0.f;
}

CState_BDeath::~CState_BDeath()
{
}

void CState_BDeath::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();

	m_fDura -= fDT;
	m_fTimer += fDT;

	if (m_fTimer >= 0.15f && m_fDura > 1.f)
	{
		for (int i = 0; i < 1; i++)
		{
			CEffect_Move* pEff = new CEffect_Move;
			pEff->load(L"dream_big", L"texture\\boss\\dream_big.bmp");
			pEff->setDuration(3.f);
			pEff->setDegree((float)m_iDegree);
			pEff->setSpeed(m_fSpd);
			pEff->setDecel(m_fDecel);

			pEff->createAnim(L"dream_big", pEff->getTex(),
				fPoint(1505, 0), fPoint(125, 125), fPoint(-125, 0), 1.f, 1, false);
			pEff->createAnim(L"dream_disapear", pEff->getTex(),
				fPoint(1505, 0), fPoint(125, 125), fPoint(-125, 0), 0.1f, 13, false);

			pEff->setPos(pos);
			pEff->PLAY(L"dream_big");
			createObj(pEff, eOBJ::EFFECT_BACK);

			m_iDegree	= (int)(rand() % 360);
			m_fSpd		= (float)(rand() % 1800 + 900);
			m_fDecel	= (float)(rand() % 900 + 450);
		}
		for (int i = 0; i < 1; i++)
		{
			CEffect_Move* pEff = new CEffect_Move;
			pEff->load(L"dream_large", L"texture\\boss\\dream_large.bmp");
			pEff->setDuration(3.3f);
			pEff->setDegree((float)m_iDegree);
			pEff->setSpeed(m_fSpd);
			pEff->setDecel(m_fDecel);

			pEff->createAnim(L"dream_large", pEff->getTex(),
				fPoint(4860, 0), fPoint(180, 177), fPoint(-180, 0), 1.f, 1, false);
			pEff->createAnim(L"dream_disapear", pEff->getTex(),
				fPoint(4860, 0), fPoint(180, 177), fPoint(-180, 0), 0.05f, 28, false);

			pEff->setPos(pos);
			pEff->PLAY(L"dream_large");
			createObj(pEff, eOBJ::EFFECT_BACK);

			m_iDegree = (int)(rand() % 360);
			m_fSpd = (float)(rand() % 1800 + 900);
			m_fDecel = (float)(rand() % 900 + 450);
		}
		for (int i = 0; i < 2; i++)
		{
			CEffect_Move* pEff = new CEffect_Move;
			pEff->load(L"dream_mini", L"texture\\boss\\dream_mini.bmp");
			pEff->setDuration(2.8f);
			pEff->setDegree((float)m_iDegree);
			pEff->setSpeed(m_fSpd);
			pEff->setDecel(m_fDecel);

			pEff->createAnim(L"dream_mini", pEff->getTex(),
				fPoint(722, 0), fPoint(60, 60), fPoint(-60, 0), 1.f, 1, false);
			pEff->createAnim(L"dream_disapear", pEff->getTex(),
				fPoint(722, 0), fPoint(60, 60), fPoint(-60, 0), 0.1f, 13, false);

			pEff->setPos(pos);
			pEff->PLAY(L"dream_mini");
			createObj(pEff, eOBJ::EFFECT_BACK);

			m_iDegree	= (int)(rand() % 360);
			m_fSpd		= (float)(rand() % 1800 + 900);
			m_fDecel	= (float)(rand() % 900 + 450);
		}

		m_fTimer = 0.f;
	}


	if (m_fDura < 0.f)
	{
		CEffect* pEff = new CEffect;
		pEff->load(L"effect_burst", L"texture\\boss\\effect_burst.bmp");
		pEff->setDuration(0.4f);
		pEff->setPos(pos);

		pEff->createAnim(L"effect_burst", pEff->getTex(),
			fPoint(0, 0), fPoint(353, 322), fPoint(353, 0), 0.08f, 5, false);

		pEff->PLAY(L"effect_burst");
		createObj(pEff, eOBJ::EFFECT);

		CSoundManager::getInst()->addSound(L"boss_explode_clean", L"sound\\boss\\boss_explode_clean.wav");
		CSoundManager::getInst()->play(L"boss_explode_clean", 0.1f);

		deleteObj(getMonster());
	}
}

void CState_BDeath::enter()
{
	getMonster()->PLAY(L"st_Death");
	getMonster()->setCheck(SB_TIMER, false);
	m_fDura = 4.5f;
	m_fTimer = 0.f;
	m_iDegree = 0;
	m_fSpd = 0.f;

	CSoundManager::getInst()->addSound(L"Markoth_Death", L"sound\\boss\\Markoth_Death.wav");
	CSoundManager::getInst()->play(L"Markoth_Death", 0.1f);

	vector<CSpear*> vecSpr = ((CBoss_Markoth*)getMonster())->getVecSpear();
	{	// 
		for (int i = 0; i < vecSpr.size(); i++)
		{
			vecSpr[i]->setActive(false);
			vecSpr[i]->setPos(fPoint(-444.f, -444.f));
		}
	}

	vector<CShield*> vecShd = ((CBoss_Markoth*)getMonster())->getVecShield();
	{	// 
		for (int i = 0; i < vecShd.size(); i++)
		{
			vecShd[i]->setActive(false);
			vecShd[i]->setPos(fPoint(-444.f, -444.f));
		}
	}
}

void CState_BDeath::exit()
{
}

void CState_BDeath::printInfo(HDC hDC)
{
}
