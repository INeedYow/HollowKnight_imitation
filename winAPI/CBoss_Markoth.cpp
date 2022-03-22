#include "framework.h"
#include "CBoss_Markoth.h"
#include "CShield.h"
#include "CSpear.h"
#include "SelectGDI.h"

CBoss_Markoth::CBoss_Markoth()
{
	m_pTex = loadTex(L"BossTex", L"texture\\boss\\boss_markoth.bmp");

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::BOSS);
	
	setHP(SB_HPMAX);
	setSpd(110.f);

	m_fTimer = 0.f;
	m_fSkillTimer = (float)SB_SKILL_COOL;
	m_fSpawnTimer = 4.f;
	m_fvDir = {};

	m_eState = eSTATE_BOSS::SPAWN;

	createCollider();
	getCollider()->setSize(fPoint(SB_MdSIZEX, SB_MdSIZEY));
	getCollider()->setShape(eSHAPE::RECT);
	

	createAnimator();
	createAnim(L"st_Normal",	m_pTex, fPoint(0.f, 0.f),		fPoint(280.f, 420.f),		fPoint(280.f, 0.f),		0.25f,	6);

	createAnim(L"st_Middle",	m_pTex, fPoint(0.f, 420.f),		fPoint(300.f, 415.f),		fPoint(300.f, 0.f),		0.2f,	4);

	createAnim(L"st_Skill",		m_pTex, fPoint(0.f, 835.f),		fPoint(448.f, 282.f),		fPoint(448.f, 0.f),		0.15f,	4);

	PLAY(L"st_Normal");

	//
	m_ucPhase = 1;
	createShield();
}

CBoss_Markoth::~CBoss_Markoth()
{
}

CBoss_Markoth* CBoss_Markoth::clone()
{
	return nullptr;
}


// TODO boss패턴
	// 스킬 쓸때 충돌체 크기 조정

void CBoss_Markoth::update()
{
	fPoint pos = getPos();

	switch (m_eState)
	{
	case eSTATE_BOSS::IDLE:
	{
		m_fSkillTimer -= fDT;
		m_fSpawnTimer -= fDT;

		if (getHP() <= SB_HPMAX / 2 && m_ucPhase == 1)
		{	// 2 페이즈
			m_fTimer = 0.6f;
			m_ucPhase++;
			m_eState = eSTATE_BOSS::SPAWN;
			getCollider()->setSize(fPoint(210.f, 280.f));
		}

		if (m_fSpawnTimer < 0.f)
		{
			createSpear();
		}

		if (m_fSkillTimer < 0.f)
		{	// 스킬 준비단계로
			m_eState = eSTATE_BOSS::READY;
			getCollider()->setSize(fPoint(210.f, 280.f));
			m_fSkillTimer = 0.f;
			m_fSpawnTimer = 0.f;
			m_fTimer = (float)SB_READY_DURA + 1.f;
		}

		PLAY(L"st_Normal");
		break;
	}
	
	case eSTATE_BOSS::MOVE:
	{	// TODO MOVE랑 같은데 움직임만 추가하면 될 듯
		m_eState = eSTATE_BOSS::IDLE;
		getCollider()->setSize(fPoint(SB_NmSIZEX, SB_NmSIZEY));
		break;
	}

	case eSTATE_BOSS::SPAWN:
	{
		m_fTimer -= fDT;

		if (m_fTimer < 0.f)
		{
			spawnShield();
			m_fTimer = 0.f;
			m_eState = eSTATE_BOSS::IDLE;
			getCollider()->setSize(fPoint(SB_NmSIZEX, SB_NmSIZEY));
		}

		PLAY(L"st_Middle");
		break;
	}

	case eSTATE_BOSS::READY:
	{

		m_fTimer -= fDT;

		if (m_fTimer > 1.4f)		// 변수하나 더 두기 싫어서 시간가지고 해봄
		{	// 방패 감속
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() - (float)SB_ACCEL * fDT);
			}
		}
		else if (1.4f >= m_fTimer && m_fTimer > 0.4f)
		{	// 방향 전환
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->toggleRot();
			}

			m_fTimer = 0.4f;
		}
		else if (0.4f >= m_fTimer && m_fTimer > 0.f)
		{	// 방패 가속
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() + (float)SB_ACCEL * fDT);
			}
		}
		else
		{	// 
			m_eState = eSTATE_BOSS::SKILL;
			getCollider()->setSize(fPoint(SB_SkSIZEX, SB_SkSIZEY));
			m_fTimer = (float)SB_SKILL_DURA;
		}

		PLAY(L"st_Middle");
		break;
	}

	case eSTATE_BOSS::SKILL:
	{
		m_fTimer -= fDT;

		if (m_fTimer >= (float)SB_SKILL_DURA / 2.f)
		{	// 방패 2개 이상일 때 1개는 주위에서 돌게
			int i = m_vecShield.size() >= 2 ? 1 : 0;

			for (; i < m_vecShield.size(); i++)
			{	// 범위, 속도 증가
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() + 0.25f * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() + 130.f * fDT);
			}
		}
		else
		{
			int i = m_vecShield.size() >= 2 ? 1 : 0;

			for (; i < m_vecShield.size(); i++)
			{	// 범위, 속도 감소
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() - 0.25f * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() - 130.f * fDT);
			}
		}

		if (m_fTimer < 0.f)
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed((float)SB_SHIELD_SPD);
				m_vecShield[i]->setRadius((float)SB_SHIELD_RAD);
			}

			m_fTimer = 0.8f;
			m_fSkillTimer = (float)SB_SKILL_COOL;
			m_eState = eSTATE_BOSS::SPAWN;
			getCollider()->setSize(fPoint(SB_MdSIZEX, SB_MdSIZEY));
		}
		PLAY(L"st_Skill");
		break;
	}

	case eSTATE_BOSS::DEATH:
	{	// TODO
		setHP(SB_HPMAX);
		m_eState = eSTATE_BOSS::IDLE;
		getCollider()->setSize(fPoint(SB_NmSIZEX, SB_NmSIZEY));
		break;
	}
	}

	//
	//pos.x += getSpd() * m_fvDir.x * fDT;
	//pos.y += getSpd() * m_fvDir.y * fDT;
	
	setPos(pos);
	getAnimator()->update();
}

void CBoss_Markoth::render(HDC hDC)
{
	if (g_bDebug)
	{
		SelectGDI font(hDC, eFONT::COMIC24);

		fPoint pos = getPos();
		fPoint camPos = getCamPos();

		wchar_t bufX[255] = {};
		wchar_t bufY[255] = {};
		wchar_t bufHP[255] = {};
		wchar_t bufCool[255] = {};
		wchar_t bufCool2[255] = {};
		wchar_t buffPhase[255] = {};
		LPCWSTR strState = L"";

		switch (m_eState)
		{
		case eSTATE_BOSS::IDLE:
			strState = L"Idle";
			break;
		case eSTATE_BOSS::MOVE:
			strState = L"Move";
			break;
		case eSTATE_BOSS::SPAWN:
			strState = L"Spawn";
			break;
		case eSTATE_BOSS::READY:
			strState = L"Ready";
			break;
		case eSTATE_BOSS::SKILL:
			strState = L"Skill";
			break;
		case eSTATE_BOSS::DEATH:
			strState = L"Death";
			break;
		}

		swprintf_s(buffPhase, L"Phase = %d", (int)m_ucPhase);
		swprintf_s(bufHP, L"HP = %d", getHP());
		swprintf_s(bufX, L"x = %.1f", pos.x);
		swprintf_s(bufY, L"y = %.1f", pos.y);
		swprintf_s(bufCool, L"cd1 = %.1f", m_fSpawnTimer);
		swprintf_s(bufCool2, L"cd2 = %.1f", m_fSkillTimer);

		pos = rendPos(pos);

		// 보스가 화면 밖으로 나가도 보스 정보는 화면 끝 보스 방향에 출력 되도록 하고 싶었는데 실패 (TODO나중에 다시)
	/*	pos.x = pos.x < camPos.x - WINSIZEX / 2.f ? camPos.x + WINSIZEX : pos.x;
		pos.x = pos.x > camPos.x + WINSIZEX / 2.f ? camPos.x - WINSIZEX : pos.x;

		pos.y = pos.y < camPos.y - WINSIZEY / 2.f ? camPos.y + WINSIZEY : pos.y;
		pos.y = pos.y > camPos.y + WINSIZEY / 2.f ? camPos.y - WINSIZEY : pos.y;*/

		TextOutW(hDC, (int)pos.x - 200, (int)pos.y + 150, strState, (int)wcslen(strState));
		TextOutW(hDC, (int)pos.x - 200, (int)pos.y + 175, buffPhase, (int)wcslen(buffPhase));
		TextOutW(hDC, (int)pos.x - 200, (int)pos.y + 200, bufHP, (int)wcslen(bufHP));
		TextOutW(hDC, (int)pos.x - 100, (int)pos.y + 175, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x - 000, (int)pos.y + 175, bufY, (int)wcslen(bufY));
		TextOutW(hDC, (int)pos.x - 100, (int)pos.y + 200, bufCool, (int)wcslen(bufCool));
		TextOutW(hDC, (int)pos.x - 000, (int)pos.y + 200, bufCool2, (int)wcslen(bufCool2));
	}

	componentRender(hDC);
}

// TODO 충돌체끼리 방향벡터로 밀어내기
void CBoss_Markoth::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	// att도 player, monster 구분해야 
	case eOBJNAME::MISSILE_PLAYER:
		setHP(getHP() - 2);
		break;

	case eOBJNAME::ATTACK:
		setHP(getHP() - 1);
		break;
	}
}

void CBoss_Markoth::collisionKeep(CCollider* pOther)
{
}

void CBoss_Markoth::collisionExit(CCollider* pOther)
{
}

void CBoss_Markoth::setRandDelay()
{
	float randDelay = (float)(rand() % 3);

	switch ((int)randDelay)
	{
	case 0:
		randDelay += 0.1f;
	case 1:
		randDelay += 0.1f;
	case 2:
	{
		if (1 == m_ucPhase)
			randDelay += 2.4f;
		else
			randDelay += 1.6f;
		break;
	}
	}
	m_fSpawnTimer = randDelay;
}

// TODO
// 플레이어 좌표로 날아오게 하려면 플레이어 좌표 받아올 수 있어야
	// 임시로 카메라 중심으로 날아가도록 (이렇게 해도 될듯?)
void CBoss_Markoth::createSpear()
{
	fPoint pos = randSpearPos();
	fPoint camPos = getCamPos();

	CSpear* pSpear = new CSpear;
	pSpear->setPos(pos);
	pSpear->setName(eOBJNAME::MISSILE_MONSTER);
	pSpear->setMaxSpd((float)SB_SPEAR_SPD);
	pSpear->getCollider()->setSize(fPoint(60.f, 60.f));
	pSpear->setTex(L"Spear_Boss", L"texture\\boss\\boss_spear.bmp");
	pSpear->createAnim(L"Spear_normal", pSpear->getTex(), 
		fPoint(0.f, 0.f), fPoint(240.f, 55.f), fPoint(240.f, 0.f), 0.7f, 1, false);
	pSpear->getAnimator()->play(L"Spear_normal");

	createObj(pSpear, eOBJ::MISSILE_MONSTER);

	setRandDelay();
}

void CBoss_Markoth::createShield(float theta)
{
	CShield* pShield = new CShield();
	pShield->setOwner(this);
	pShield->setRadius((float)SB_SHIELD_RAD);
	pShield->setTex(L"Shield_Boss", L"texture\\boss\\boss_shield.bmp");
	pShield->createAnim(L"Shield_rot", pShield->getTex(), 
		fPoint(0.f, 0.f), fPoint(166.f, 308.f), fPoint(166.f, 0.f), 0.3f, 3);
	pShield->getAnimator()->play(L"Shield_rot");
	pShield->setTheta((float)(theta + m_vecShield.size() * PI));			// 반대 방향에서 생성..

	createObj(pShield, eOBJ::SHIELD);

	m_vecShield.push_back(pShield);
}

// 카메라 안에서 랜덤 위치에 생성
fPoint CBoss_Markoth::randSpearPos()
{
	fPoint pos = CCameraManager::getInst()->getFocus();
	iPoint maxArea = { (int)(WINSIZEX / 2) ,(int)(WINSIZEY / 2)};
	iPoint minArea = { (int)(WINSIZEX / 4) ,(int)(WINSIZEY / 4)};
	iPoint randPos;
	int random;
	
	randPos.x = rand() % (maxArea.x - minArea.x + 1) + minArea.x;
	randPos.y = rand() % (maxArea.y - minArea.y + 1) + minArea.y;

	random = rand() % 2;
	if (random)
		pos.x -= randPos.x;
	else
		pos.x += randPos.x;

	random = rand() % 2;
	if (random)
		pos.y -= randPos.y;
	else
		pos.y += randPos.y;

	return pos;
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
