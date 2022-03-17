#include "framework.h"
#include "CBoss_Markoth.h"
#include "CShield.h"

CBoss_Markoth::CBoss_Markoth()
{
	m_pTex = loadTex(L"BossTex", L"texture\\boss\\boss_markoth.bmp");

	setPos(fPoint(0.f, 0.f));
	setSize(fPoint(0.f, 0.f));
	setName(eOBJNAME::BOSS);
	
	setHP(20);
	setSpd(200.f);
	setState(SB_NORMAL,true);

	m_ucPhase = 1;
	m_fTimer = 0.f;
	m_fvDir = {};

	createCollider();
	getCollider()->setSize(fPoint(0.f,0.f));
	getCollider()->setShape(eSHAPE::RECT);
	
	createAnimator();
	createAnim(L"st_Normal",	m_pTex, fPoint(0.f, 0.f),		fPoint(280.f, 420.f),		fPoint(280.f, 0.f),		0.2f,	6);

	createAnim(L"st_Middle",	m_pTex, fPoint(0.f, 420.f),		fPoint(300.f, 415.f),		fPoint(300.f, 0.f),		0.25f,	4);

	createAnim(L"st_Skill",		m_pTex, fPoint(0.f, 835.f),		fPoint(448.f, 282.f),		fPoint(448.f, 0.f),		0.3f,	4);

	PLAY(L"st_Normal");

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
// 방패 맞은 편에 생성하는 방법 고민
void CBoss_Markoth::update()
{
	fPoint pos = getPos();

	m_fTimer += fDT;
	if (getHP() <= SB_HPMAX)
	{
		m_ucPhase = 2;
		createShield();
	}

	PLAY(L"st_Normal");

	if (m_fTimer > 10.f && isState(SB_NORMAL))
	{
		PLAY(L"st_Normal");
		setState(SB_MIDDLE, true);
		setState(SB_NORMAL, false);
		m_fTimer = 0.f;
	}

	if (isState(SB_MIDDLE))
	{
		PLAY(L"st_Middle");
		if (m_fTimer > 1.f)
		{
			setState(SB_SKILL, true);
			setState(SB_MIDDLE, false);
			m_fTimer = 0.f;
		}
	}

	if (isState(SB_SKILL))
	{
		PLAY(L"st_Skill");

		if (m_fTimer < 4.f)
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() + 2 * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() + 75 * fDT);
			}
		}
		else
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(m_vecShield[i]->getSpeed() - 2 * fDT);
				m_vecShield[i]->setRadius(m_vecShield[i]->getRadius() - 75 * fDT);
			}
		}

		if (m_fTimer > 8.f)
		{
			for (int i = 0; i < m_vecShield.size(); i++)
			{
				m_vecShield[i]->setfSpeed(2.f);
				m_vecShield[i]->setRadius(250.f);
			}
			m_fTimer = 0;
			setState(SB_NORMAL, true);
			setState(SB_SKILL, false);
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
		wchar_t buffHP[255] = {};

		swprintf_s(buffHP, L"HP = %d", getHP());
		swprintf_s(bufX, L"x = %d", (int)pos.x);
		swprintf_s(bufY, L"y = %d", (int)pos.y);

		pos = rendPos(pos);

		TextOutW(hDC, (int)pos.x + 150, (int)pos.y - 120, buffHP, (int)wcslen(buffHP));
		TextOutW(hDC, (int)pos.x + 150, (int)pos.y - 135, bufX, (int)wcslen(bufX));
		TextOutW(hDC, (int)pos.x + 150, (int)pos.y - 150, bufY, (int)wcslen(bufY));
	}

	componentRender(hDC);
}

void CBoss_Markoth::createSpear()
{
}

void CBoss_Markoth::createShield()
{
	CShield* pShield = new CShield();
	pShield->setPos(getPos() + fPoint(0.f, -250.f));
	pShield->setOwner(this);
	pShield->calculateRad();

	createObj(pShield, eOBJ::SHIELD);

	m_vecShield.push_back(pShield);
}