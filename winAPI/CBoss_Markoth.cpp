#include "framework.h"
#include "CBoss_Markoth.h"
#include "CShield.h"
#include "CSpear.h"

CBoss_Markoth::CBoss_Markoth()
{
	m_pTex = loadTex(L"BossTex", L"texture\\boss\\boss_markoth.bmp");

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::BOSS);
	
	setHP(SB_HPMAX);
	setSpd(200.f);
	setCheck(SB_NORMAL,true);

	m_ucPhase = 0;
	m_fTimer = 0.f;
	m_fvDir = {};

	createCollider();
	getCollider()->setSize(fPoint(200.f, 310.f));
	getCollider()->setShape(eSHAPE::RECT);
	

	createAnimator();
	createAnim(L"st_Normal",	m_pTex, fPoint(0.f, 0.f),		fPoint(280.f, 420.f),		fPoint(280.f, 0.f),		0.25f,	6);

	createAnim(L"st_Middle",	m_pTex, fPoint(0.f, 420.f),		fPoint(300.f, 415.f),		fPoint(300.f, 0.f),		0.15f,	4);

	createAnim(L"st_Skill",		m_pTex, fPoint(0.f, 835.f),		fPoint(448.f, 282.f),		fPoint(448.f, 0.f),		0.25f,	4);

	PLAY(L"st_Normal");

	phaseInit();
}

CBoss_Markoth::~CBoss_Markoth()
{
}

CBoss_Markoth* CBoss_Markoth::clone()
{
	return nullptr;
}


// TODO boss패턴
// 방패 맞은 편에 생성하는 방법 고민
// 방패 방향에 대한 변수 있어야 방패들이 같은 방향으로 돌도록 할 수 있을듯
// 어차피 한 번 스킬쓰고 나면 새로 생성하게 할거니까 생성할 때 통일되면 될듯

// 스킬 쓸때 충돌체 크기 조정

void CBoss_Markoth::update()
{
	fPoint pos = getPos();
	
	m_fTimer += fDT;

	if (m_fDelay < 0.f)
	{
		createSpear();
	}
	
	if (m_fTimer > 12.f && isCheck(SB_NORMAL))
	{
		setCheck(SB_MIDDLE, true);
		setCheck(SB_NORMAL, false);
		m_fTimer = 0.f;
	}

	else if (isCheck(SB_MIDDLE))
	{
		PLAY(L"st_Middle");
		if (m_fTimer > 0.6f)
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->toggleRot();
			}
			setCheck(SB_SKILL, true);
			setCheck(SB_MIDDLE, false);
			m_fTimer = 0.f;
		}
	}

	else if (isCheck(SB_SKILL))
	{
		PLAY(L"st_Skill");

		
		if (m_fTimer < 4.f)
		{	// 방패 2개 이상일 때 1개는 주위에서 돌게
			int i = m_vecShield.size() >= 2 ? 1 : 0;

			for (; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() + 0.25f * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() + 130.f * fDT);
			}
		}
		else
		{
			int i = m_vecShield.size() >= 2 ? 1 : 0;

			for (; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() - 0.25f * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() - 130.f * fDT);
			}
		}

		if (m_fTimer > 8.f)
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(2.5f);
				m_vecShield[i]->setRadius(270.f);
				m_vecShield[i]->toggleRot();
			}
			m_fTimer = 0;
			setCheck(SB_NORMAL, true);
			setCheck(SB_SKILL, false);
		}
	}

	else
	{
		PLAY(L"st_Normal");
		m_fDelay -= fDT;
		
		if (getHP() <= 0)
		{	// death
			setHP(SB_HPMAX);
		}

		else if (getHP() <= SB_HPMAX / 2 && m_ucPhase == 1)
		{
			phaseInit();
		}
	}

	pos.x += getSpd() * m_fvDir.x * fDT;
	pos.y += getSpd() * m_fvDir.y * fDT;
	
	setPos(pos);
	getAnimator()->update();
}

void CBoss_Markoth::render(HDC hDC)
{
	if (g_bDebug)
	{
		fPoint pos = getPos();

		wchar_t bufX[255] = {};
		wchar_t bufY[255] = {};
		wchar_t bufHP[255] = {};
		wchar_t bufCool[255] = {};
		wchar_t buffPhase[255] = {};

		swprintf_s(buffPhase, L"Phase = %d", (int)m_ucPhase);
		swprintf_s(bufHP, L"HP = %d", getHP());
		swprintf_s(bufX, L"x = %d", (int)pos.x);
		swprintf_s(bufY, L"y = %d", (int)pos.y);
		swprintf_s(bufCool, L"cd = %.2f", m_fDelay);

		pos = rendPos(pos);

		TextOutW(hDC, (int)pos.x - 180, (int)pos.y + 105, buffPhase, (int)wcslen(buffPhase));
		TextOutW(hDC, (int)pos.x - 180, (int)pos.y + 120, bufHP, (int)wcslen(bufHP));
		TextOutW(hDC, (int)pos.x - 180, (int)pos.y + 135, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x - 180, (int)pos.y + 150, bufY, (int)wcslen(bufY));
		TextOutW(hDC, (int)pos.x - 180, (int)pos.y + 165, bufCool, (int)wcslen(bufCool));
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
	float randDelay = (float)(rand() % 4);

	switch ((int)randDelay)
	{
	case 0:
		randDelay += 0.05f;
	case 1:
		randDelay += 0.05f;
	case 2:
		randDelay += 0.05f;
	case 3:
	{
		if (1 == m_ucPhase)
			randDelay += 1.4f;
		else
			randDelay += 0.7f;
		break;
	}
	}
	m_fDelay = randDelay;
}

// TODO
// 플레이어 좌표로 날아오게 하려면 플레이어 좌표 받아올 수 있어야
	// 임시로 카메라 중심으로 날아가도록 (이렇게 해도 될듯?)
// 플레이어 너무 근처에서 생성 되지 않도록
void CBoss_Markoth::createSpear()
{
	fPoint pos = randSpearPos();
	fPoint camPos = getCamPos();

	CSpear* pSpear = new CSpear;
	pSpear->setPos(pos);
	pSpear->setName(eOBJNAME::MISSILE_MONSTER);
	pSpear->setMaxSpd(250.f);
	pSpear->getCollider()->setSize(fPoint(50.f, 50.f));
	pSpear->setTex(L"Spear_Boss", L"texture\\boss\\boss_spear.bmp");
	pSpear->createAnim(L"Spear_normal", pSpear->getTex(), 
		fPoint(0.f, 0.f), fPoint(362.f, 83.f), fPoint(362.f, 0.f), 0.7f, 1);
	pSpear->getAnimator()->play(L"Spear_normal");

	createObj(pSpear, eOBJ::MISSILE_MONSTER);

	setRandDelay();
}

void CBoss_Markoth::createShield()
{
	CShield* pShield = new CShield();
	pShield->setPos(getPos() + fPoint(0.f, 270.f));
	pShield->setOwner(this);
	pShield->calculateRad();
	pShield->setTex(L"Shield_Boss", L"texture\\boss\\boss_shield.bmp");
	pShield->createAnim(L"Shield_rot", pShield->getTex(), 
		fPoint(0.f, 0.f), fPoint(166.f, 308.f), fPoint(166.f, 0.f), 0.3f, 3);
	pShield->getAnimator()->play(L"Shield_rot");
	pShield->setTheta((float)(m_vecShield.size() * PI));			// 반대 방향에서 생성

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

void CBoss_Markoth::phaseInit()
{
	// TODO 모션
	for (int i = 0; i < m_vecShield.size(); i++)
	{
		deleteObj(m_vecShield[i]);
	}
	m_vecShield.clear();

	m_ucPhase++;

	switch (m_ucPhase)
	{
	case 3:
		m_ucPhase = 2;
		break;
	case 2:
		createShield();
	case 1:
		createShield();
	}
}
