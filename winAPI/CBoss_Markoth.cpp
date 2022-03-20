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
	
	setHP(20);
	setSpd(200.f);
	setCheck(SB_NORMAL,true);

	m_ucPhase = 1;
	m_fTimer = 0.f;
	m_fvDir = {};

	createCollider();
	getCollider()->setSize(fPoint(200.f, 310.f));
	getCollider()->setShape(eSHAPE::RECT);
	
	createAnimator();
	createAnim(L"st_Normal",	m_pTex, fPoint(0.f, 0.f),		fPoint(280.f, 420.f),		fPoint(280.f, 0.f),		0.2f,	6);

	createAnim(L"st_Middle",	m_pTex, fPoint(0.f, 420.f),		fPoint(300.f, 415.f),		fPoint(300.f, 0.f),		0.15f,	4);

	createAnim(L"st_Skill",		m_pTex, fPoint(0.f, 835.f),		fPoint(448.f, 282.f),		fPoint(448.f, 0.f),		0.2f,	4);

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
// 방패 방향 전환
void CBoss_Markoth::update()
{
	if (getHP() <= 0)
	{
		// death
		m_ucPhase = 1;
		setHP(20);
	}

	fPoint pos = getPos();
	
	m_fTimer += fDT;

	if (getHP() <= SB_HPMAX / 2 && m_ucPhase == 1)
	{
		m_ucPhase = 2;
		phaseInit();
	}

	
	PLAY(L"st_Normal");

	if (m_fDelay < 0.f)
	{
		createSpear();
		setRandDelay();
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
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() + 0.25f * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() + 130.f * fDT);
			}
		}
		else
		{
			for (int i = 0; i < m_vecShield.size(); i++)
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
		m_fDelay -= fDT;
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
		wchar_t buffHP[255] = {};

		swprintf_s(buffHP, L"HP = %d", getHP());
		swprintf_s(bufX, L"x = %d", (int)pos.x);
		swprintf_s(bufY, L"y = %d", (int)pos.y);

		pos = rendPos(pos);

		TextOutW(hDC, (int)pos.x - 160, (int)pos.y + 120, buffHP, (int)wcslen(buffHP));
		TextOutW(hDC, (int)pos.x - 160, (int)pos.y + 135, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x - 160, (int)pos.y + 150, bufY, (int)wcslen(bufY));
	}

	componentRender(hDC);
}

// TODO 충돌체끼리 방향벡터로 밀어내기
void CBoss_Markoth::collisionEnter(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{	// att도 player, monster 구분해야 
	case eOBJNAME::MISSILE_PLAYER:
		setHP(getHP() - 1);
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
		randDelay += 0.85f;
	}
	m_fDelay = randDelay;
}

// TODO
// 소환된 창이 일정시간 후에 이동하도록 하려면 새로 클래스 만들거나
	// 미사일에 대기시간등 추가로 만들어야(해당 기능 안쓰는 경우 낭비일듯)
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
}

void CBoss_Markoth::createShield()
{
	CShield* pShield = new CShield();
	pShield->setPos(getPos() + fPoint(0.f, -270.f));
	pShield->setOwner(this);
	pShield->calculateRad();
	pShield->setTex(L"Shield_Boss", L"texture\\boss\\boss_shield.bmp");
	pShield->createAnim(L"Shield_rot", pShield->getTex(), 
		fPoint(0.f, 0.f), fPoint(166.f, 308.f), fPoint(166.f, 0.f), 0.3f, 3);
	pShield->getAnimator()->play(L"Shield_rot");

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
	switch (m_ucPhase)
	{
	case 1:
	{
		// TODO
		break;
	}
	case 2:
	{

		break;
	}
	}
	createShield();
}
