#include "framework.h"
#include "CState_Dash.h"
#include "CState_Player.h"
#include "CPlayer.h"
#include "CEffect.h"

CState_Dash::CState_Dash(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fDura = 0.f;
	m_fSpd = 0.f;
	m_fDecel = 0.f;
}

CState_Dash::~CState_Dash()
{
}

// TODO dash 연속사용 제어?
void CState_Dash::update(UINT& chk)
{
	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	m_fDura -= fDT;

	if (m_fDura < 0.f)
	{
		if (chk & SP_AIR)
		{
			changeMyState(getOwner(), eSTATE_PLAYER::FALL);
		}
		else
		{
			changeMyState(getOwner(), eSTATE_PLAYER::DASH2IDLE);
		}
	}
	else if (m_fDura < 0.1f)
	{
		m_fDecel += 6000 * fDT;

		if (m_fDecel > m_fSpd)
			m_fDecel = m_fSpd;
	}

	if (chk & SP_DIR)
	{
		pos.x += (m_fSpd - m_fDecel)  * fDT;
	}
	else
	{
		pos.x -= (m_fSpd - m_fDecel) * fDT;
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Dash::enter()
{
	getPlayer()->playAnim(L"Dash");
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_DASH, true);
	getPlayer()->setCheck(SP_NODMG, true);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fNoDmgTimer += 0.5f;
	getPlayer()->setPlayerInfo(info);

	//////////////////////////////////////////////

	fPoint pos = getPlayer()->getPos();

	CEffect* pEff = new CEffect;
	pEff->load(L"Effect_dash", L"texture\\effect\\effect_dash.bmp");
	pEff->setFollow(getPlayer());
	pEff->setDuration(0.2f);
	if (getPlayer()->isCheck(SP_DIR))
	{
		pEff->createAnim(L"effect_dash", pEff->getTex(),
			fPoint(289, 0), fPoint(289, 146), fPoint(289, 0), 0.05f, 4, false);
		pos.x -= 40.f;
		
	}
	else
	{
		pEff->createAnim(L"effect_dash", pEff->getTex(),
			fPoint(867, 146), fPoint(289, 146), fPoint(-289, 0), 0.05f, 4, false);
		pos.x += 40.f;
	}
	pEff->setPos(pos);
	pEff->PLAY(L"effect_dash");
	createObj(pEff, eOBJ::EFFECT);
	
	CSoundManager::getInst()->addSound(L"hero_shade_dash_1", L"sound\\player\\hero_shade_dash_1.wav");
	CSoundManager::getInst()->play(L"hero_shade_dash_1", 0.1f);

	m_fDura = 0.35f;
	m_fSpd = 1350.f;
	m_fDecel = 0.f;
}

void CState_Dash::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);

	tPlayerInfo info = getPlayer()->getPlayerInfo();
	info.fSpdY = 0.f;
	getPlayer()->setPlayerInfo(info);

	m_fDecel = 0.f;
	m_fDura = 0.f;
}

void CState_Dash::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Dash";
	wchar_t bufDura[255] = {};
	wchar_t bufSpd[255] = {};

	swprintf_s(bufDura, L"Dura = %.1f", m_fDura);
	swprintf_s(bufSpd, L"Accel = %.1f", (m_fSpd - m_fDecel));

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDura, (int)wcslen(bufDura));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 100, bufSpd, (int)wcslen(bufSpd));
}