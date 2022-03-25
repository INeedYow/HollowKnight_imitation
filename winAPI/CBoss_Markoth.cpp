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
	m_fSpawnTimer = 4.f;

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

	pAI->setCurState(eSTATE_MONS::IDLE);
	setAI(pAI);

	//
	createShield();
	createSpear();
}

CBoss_Markoth::~CBoss_Markoth()
{
}

CBoss_Markoth* CBoss_Markoth::clone()
{
	return nullptr;
}

// TODO 상태 정보 출력, 콜라이더 크기, chk 수정, player update 수정
void CBoss_Markoth::update()
{
	CMonster::update();

	if (isCheck(SB_TIMER))			// 타이머 적용되는 상태
	{
		m_fSkillTimer -= fDT;
		m_fSpawnTimer -= fDT;


		if (getMonsInfo().iHP <= B_HPMAX / 2 && m_ucPhase == 1)
		{	// 2 페이즈
			m_ucPhase++;
			changeMonsState(getAI(), eSTATE_MONS::SPAWN);
			createSpear();
		}

		if (m_fSkillTimer < 0.f)
		{	// 스킬 준비단계로
			m_fSkillTimer = 0.f;
			m_fSpawnTimer = 0.f;
			changeMonsState(getAI(), eSTATE_MONS::READY);
		}
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

void CBoss_Markoth::collisionExit(CCollider* pOther)
{
}
//
//void CBoss_Markoth::setRandDelay()
//{
//	float randDelay = (float)(rand() % 3);
//
//	switch ((int)randDelay)
//	{
//	case 0:
//		randDelay += 0.1f;
//	case 1:
//		randDelay += 0.1f;
//	case 2:
//	{
//		if (1 == m_ucPhase)
//			randDelay += 2.4f;
//		else
//			randDelay += 1.6f;
//		break;
//	}
//	}
//	m_fSpawnTimer = randDelay;
//}

// TODO
// 계속 소환하게 하지말고 미리 소환해두고 그걸 계속 쓰는 방식으로 바꿔보기
//void CBoss_Markoth::createSpear()
//{
//	fPoint pos = randSpearPos();
//
//	CSpear* pSpear = new CSpear;
//	pSpear->setPos(pos);
//	pSpear->setName(eOBJNAME::MISSILE_MONSTER);
//	pSpear->setSpd((float)B_SPR_SPD_1P);
//	pSpear->getCollider()->setSize(fPoint(60.f, 60.f));
//	pSpear->setTex(L"Spear_Boss", L"texture\\boss\\boss_spear.bmp");
//	pSpear->createAnim(L"Spear_normal", pSpear->getTex(), 
//		fPoint(0.f, 0.f), fPoint(400.f, 91.f), fPoint(0.f, 0.f), 1.f, 1, false);
//	pSpear->getAnimator()->play(L"Spear_normal");
//
//	createObj(pSpear, eOBJ::MISSILE_MONSTER);
//
//	m_vecSpear.push_back(pSpear);
//	//setRandDelay();
//}

void CBoss_Markoth::createShield(float theta)
{
	CShield* pShield = new CShield();
	pShield->setOwner(this);
	pShield->setRadius((float)B_SHD_RAD);
	pShield->setTex(L"Shield_Boss", L"texture\\boss\\boss_shield.bmp");
	pShield->createAnim(L"Shield_rot", pShield->getTex(), 
		fPoint(0.f, 0.f), fPoint(166.f, 308.f), fPoint(166.f, 0.f), 0.3f, 3);
	pShield->getAnimator()->play(L"Shield_rot");
	pShield->setTheta((float)(theta + m_vecShield.size() * PI));			// 반대 방향에서 생성..

	createObj(pShield, eOBJ::SHIELD);

	m_vecShield.push_back(pShield);
}

void CBoss_Markoth::createSpear()
{
	CSpear* pSpear = new CSpear;
	pSpear->setSpd(B_SPR_SPD_1P);
	pSpear->getCollider()->setSize(fPoint(60.f, 60.f));
	pSpear->setTex(L"Spear_Boss", L"texture\\boss\\boss_spear.bmp");
	m_vecSpear.push_back(pSpear);
	createObj(pSpear, eOBJ::MISSILE_MONSTER);
}

// 카메라 안에서 랜덤 위치에 생성
//fPoint CBoss_Markoth::randSpearPos()
//{
//	fPoint pos = CCameraManager::getInst()->getFocus();
//	iPoint maxArea = { (int)(WINSIZEX / 2) ,(int)(WINSIZEY / 2)};
//	iPoint minArea = { (int)(WINSIZEX / 4) ,(int)(WINSIZEY / 4)};
//	iPoint randPos;
//	int random;
//	
//	randPos.x = rand() % (maxArea.x - minArea.x + 1) + minArea.x;
//	randPos.y = rand() % (maxArea.y - minArea.y + 1) + minArea.y;
//
//	random = rand() % 2;
//	if (random)
//		pos.x -= randPos.x;
//	else
//		pos.x += randPos.x;
//
//	random = rand() % 2;
//	if (random)
//		pos.y -= randPos.y;
//	else
//		pos.y += randPos.y;
//
//	return pos;
//}

void CBoss_Markoth::setSkillCooldown(float cd)
{
	m_fSkillTimer = cd;
}

vector<CShield*>& CBoss_Markoth::getVecShield()
{
	return m_vecShield;
}

void CBoss_Markoth::spawnShield()
{
	float theta = m_vecShield[0]->getTheta();

	for (int i = 0; i < m_vecShield.size(); i++)
	{	// 방패 제거
		deleteObj(m_vecShield[i]);
	}
	m_vecShield.clear();

	switch (m_ucPhase)
	{	// 방패 생성
	case 2:
		createShield(theta);
	case 1:
		createShield(theta);
		break;
	}
}

void CBoss_Markoth::death()
{
	// TODO
}
