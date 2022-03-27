#include "framework.h"
#include "CBoss_Markoth.h"
#include "CShield.h"
#include "CSpear.h"
#include "SelectGDI.h"
#include "CPlayer.h"

#include "CAI.h"
#include "CState_BIdle.h"
#include "CState_BMove.h"
#include "CState_BSpawn.h"
#include "CState_BReady.h"
#include "CState_BSkill.h"

CBoss_Markoth::CBoss_Markoth()
{
	setTex(L"BossTex", L"texture\\boss\\boss_markoth.bmp");

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(190.f, 300.f));
	setName(eOBJNAME::BOSS);
	
	tMonsInfo info = getMonsInfo();
	info.iHP = B_HPMAX;
	info.fSpd = B_SPD;
	setMonsInfo(info);
	
	m_ucPhase = 1;
	m_fTimer = 0.f;
	m_fSkillTimer = (float)B_SKILL_COOL;
	m_fSpawnTimer = 0.f;

	setCheck(SB_TIMER, true);

	createCollider();
	getCollider()->setSize(fPoint(SB_MdSIZEX, SB_MdSIZEY));
	getCollider()->setShape(eSHAPE::RECT);

	createAnimator();
	createAnim(L"st_Normal",	getTex(), fPoint(0.f, 0.f),		fPoint(280.f, 420.f),	fPoint(280.f, 0.f),		0.25f,	6);
	createAnim(L"st_Middle",	getTex(), fPoint(0.f, 420.f),	fPoint(300.f, 415.f),	fPoint(300.f, 0.f),		0.2f,	4);
	createAnim(L"st_Skill",		getTex(), fPoint(0.f, 835.f),	fPoint(448.f, 282.f),	fPoint(448.f, 0.f),		0.2f,	4);

	PLAY(L"st_Normal");

	CAI* pAI = new CAI;
	pAI->addState(new CState_BMove(eSTATE_MONS::MOVE));
	pAI->addState(new CState_BIdle(eSTATE_MONS::IDLE));
	pAI->addState(new CState_BSpawn(eSTATE_MONS::SPAWN));
	pAI->addState(new CState_BReady(eSTATE_MONS::READY));
	pAI->addState(new CState_BSkill(eSTATE_MONS::SKILL));

	pAI->setCurState(eSTATE_MONS::SPAWN);
	setAI(pAI);
}

CBoss_Markoth::~CBoss_Markoth()
{
}

CBoss_Markoth* CBoss_Markoth::clone()
{
	return nullptr;
}

void CBoss_Markoth::update()
{
	CMonster::update();

	fPoint pos = getPos();
	if (pos.x < 330.f)
		pos.x = 330.f;
	else if (pos.x > 2640.f)
		pos.x = 2640.f;
	else if (pos.y > 1350.f)
		pos.y = 1350.f;
	else if (pos.y < 200.f)
		pos.y = 200.f;
	setPos(pos);

	if (!isCheck(SB_TIMER))	return;		// 타이머 적용되는 상태
	
	m_fSkillTimer -= fDT;

	if (getMonsInfo().iHP <= B_HPMAX / 2 && m_ucPhase == 1)
	{	// 2 페이즈
		m_ucPhase++;
		changeMonsState(getAI(), eSTATE_MONS::SPAWN);
		//createSpear();

		for (int i = 0; i < m_vecSpear.size(); i++)
		{	// spear 속도 증가
			m_vecSpear[i]->setSpd(B_SPR_SPD_2P);
		}
	}

	m_fSpawnTimer -= fDT;

	if (m_fSpawnTimer <= 0.f)
	{
		for (int i = 0; i <= m_vecSpear.size(); i++)	// i == size이면 활성할 게 없는 걸로 간주하고 종료
		{
			if (i == m_vecSpear.size())
			{	// 활성화 할 게 없는 경우
				m_fSpawnTimer = 0.f;
				break;
			}

			if (!m_vecSpear[i]->isActive())			// 활성화 되지 않은 spear 찾으면
			{
				m_vecSpear[i]->setActive(true);		// 활성화 시킴
				m_vecSpear[i]->setSpd(m_ucPhase == 1? (float)B_SPR_SPD_1P : (float)B_SPR_SPD_2P);
				m_fSpawnTimer = 1.25f;
				break;
			}
		}
	}
	
	if (m_fSkillTimer < 0.f)
	{	// 스킬
		m_fSkillTimer = 0.f;
		m_fSpawnTimer = 0.f;
		changeMonsState(getAI(), eSTATE_MONS::READY);
	}
}

void CBoss_Markoth::render(HDC hDC)
{
	if (g_bDebug)
	{
		getAI()->getCurState()->printInfo(hDC);

		SelectGDI font(hDC, eFONT::COMIC24);

		fPoint pos = getPos();
		fPoint camPos = getCamPos();

		wchar_t bufX[255] = {};
		wchar_t bufY[255] = {};
		wchar_t bufHP[255] = {};
		wchar_t bufCool[255] = {};
		wchar_t bufCool2[255] = {};
		wchar_t buffPhase[255] = {};

		swprintf_s(buffPhase, L"Phase = %d", (int)m_ucPhase);
		swprintf_s(bufHP, L"HP = %d", getMonsInfo().iHP);
		swprintf_s(bufX, L"x = %.1f", pos.x);
		swprintf_s(bufY, L"y = %.1f", pos.y);
		swprintf_s(bufCool, L"cd1 = %.1f", m_fSpawnTimer);
		swprintf_s(bufCool2, L"cd2 = %.1f", m_fSkillTimer);

		pos = rendPos(pos);

		TextOutW(hDC, (int)pos.x - 200, (int)pos.y + 175, buffPhase, (int)wcslen(buffPhase));
		TextOutW(hDC, (int)pos.x - 200, (int)pos.y + 200, bufHP, (int)wcslen(bufHP));
		TextOutW(hDC, (int)pos.x - 100, (int)pos.y + 175, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x - 000, (int)pos.y + 175, bufY, (int)wcslen(bufY));
		TextOutW(hDC, (int)pos.x - 100, (int)pos.y + 200, bufCool, (int)wcslen(bufCool));
		TextOutW(hDC, (int)pos.x - 000, (int)pos.y + 200, bufCool2, (int)wcslen(bufCool2));
	}

	componentRender(hDC);
}

void CBoss_Markoth::collisionEnter(CCollider* pOther)
{
	tMonsInfo info;

	switch (pOther->getOwner()->getName())
	{	// att도 player, monster 구분해야 
	case eOBJNAME::MISSILE_PLAYER:
		if (!isCheck(SM_DEATH))
		{
			info = getMonsInfo();

			info.iHP -= 2;

			info.fvKnockBackDir.x = 1.f;
			if (((CMissile*)pOther->getOwner())->getDir().x < 0.f)		// 미사일 방향에 따른 넉백방향
				info.fvKnockBackDir.x = -1.f;
			info.fKnockBackSpd = (float)SM_KBSPD_M;
			info.fKnockBackTimer = (float)SM_KBTIME;

			m_fTimer = (float)B_DMG_DELAY;
			setMonsInfo(info);
			break;
		}

	case eOBJNAME::ATTACK:
	{
		info = getMonsInfo();

		info.iHP -= 1;

		info.fvKnockBackDir = getPos() - gameGetPlayer()->getPos();
		info.fKnockBackSpd = (float)SM_KBSPD_L;
		info.fKnockBackTimer = (float)SM_KBTIME;

		setMonsInfo(info); 
	}
		break;
	}
}

void CBoss_Markoth::collisionKeep(CCollider* pOther)
{
	tMonsInfo info;

	switch (pOther->getOwner()->getName())
	{	// att도 player, monster 구분해야 
	case eOBJNAME::MISSILE_PLAYER:
	{
		m_fTimer -= fDT;

		if (!isCheck(SM_DEATH) && m_fTimer < 0.f)
		{
			info = getMonsInfo();

			info.iHP -= 1;	// 다단히트 시 1 감소

			info.fvKnockBackDir.x = 1.f;
			if (((CMissile*)pOther->getOwner())->getDir().x < 0.f)		// 미사일 방향에 따른 넉백방향
				info.fvKnockBackDir.x = -1.f;
			info.fvKnockBackDir.y = 0.f;
			info.fKnockBackSpd = (float)SM_KBSPD_M;
			info.fKnockBackTimer = (float)SM_KBTIME;

			setMonsInfo(info);

			m_fTimer = (float)B_DMG_DELAY;
			break;
		}
	}
	}
}

// 테스트 중 원본 보관
//void CBoss_Markoth::createShield(float theta)
//{
//	CShield* pShield = new CShield();
//	pShield->setOwner(this);
//	pShield->setRadius((float)B_SHD_RAD);
//	pShield->setfSpeed((float)B_SHD_SPD);
//	pShield->setTex(L"Shield_Boss", L"texture\\boss\\boss_shield.bmp");
//	pShield->createAnim(L"Shield_rot", pShield->getTex(), 
//		fPoint(0.f, 0.f), fPoint(166.f, 308.f), fPoint(166.f, 0.f), 0.1f, 3);
//	pShield->getAnimator()->play(L"Shield_rot");
//	pShield->setTheta((float)(theta + m_vecShield.size() * PI));			// 반대 방향에서 생성..
//
//	createObj(pShield, eOBJ::SHIELD);
//
//	m_vecShield.push_back(pShield);
//}

// 테스트 용
// MemTex 이름이 같으면 에러
void CBoss_Markoth::createShield(float theta, bool rightRot)
{
	CShield* pShield = new CShield();
	pShield->setOwner(this);
	pShield->setRadius((float)B_SHD_RAD);
	pShield->setfSpeed((float)B_SHD_SPD);
	pShield->setTex(L"Shield_Boss", L"texture\\boss\\boss_shield.bmp");
	pShield->setTheta(theta);
	pShield->setRot(rightRot);

	pShield->getCollider()->setSize(fPoint(90.f, 250.f));

	pShield->getAnimator()->createMemTex(addStrIDNumber(L"Shield"), SHD_MEMTEX_SIZE, SHD_MEMTEX_SIZE);
	pShield->createAnim(L"Shield_rot", pShield->getTex(),
				fPoint(0.f, 0.f), fPoint(166.f, 308.f), fPoint(166.f, 0.f), 0.2f, 3);
	pShield->getAnimator()->play(L"Shield_rot");

	m_vecShield.push_back(pShield);

	createObj(pShield, eOBJ::SHIELD);
}

void CBoss_Markoth::createSpear()
{
	CSpear* pSpear = new CSpear;
	pSpear->setSpd(B_SPR_SPD_1P);
	pSpear->setTex(L"Spear_Boss", L"texture\\boss\\boss_spear.bmp");

	pSpear->getCollider()->setSize(fPoint(276.f, 34.f));

	pSpear->getAnimator()->createMemTex(addStrIDNumber(L"Spear"), SPR_MEMTEX_SIZE, SPR_MEMTEX_SIZE);
	pSpear->createAnim(L"Spear_1", pSpear->getTex(),
		fPoint(0.f, 0.f), fPoint(380.f, 85.f), fPoint(380.f, 0.f), 0.5f, 1, false);
	pSpear->getAnimator()->play(L"Spear_1");

	m_vecSpear.push_back(pSpear);

	createObj(pSpear, eOBJ::MISSILE_MONSTER);
}

void CBoss_Markoth::setSkillCooldown(float cd)
{
	m_fSkillTimer = cd;
}

void CBoss_Markoth::setSpawnTimer(float time)
{
	m_fSpawnTimer = time;
}

vector<CShield*>& CBoss_Markoth::getVecShield()
{
	return m_vecShield;
}

vector<CSpear*>& CBoss_Markoth::getVecSpear()
{
	return m_vecSpear;
}

void CBoss_Markoth::spawnShield()
{
	switch (m_ucPhase)
	{
	case 1:
	{
		createShield();
		break;
	}
	case 2:
	{	// 방패 0개 (처음 init)
		float theta = m_vecShield[0]->getTheta();
		bool isRight = m_vecShield[0]->isRotRight();
		createShield((float)(theta + PI), isRight);
		break;
	}
	}
}

void CBoss_Markoth::death()
{
	// TODO
}
