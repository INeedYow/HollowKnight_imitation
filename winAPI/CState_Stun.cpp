#include "framework.h"
#include "CState_Stun.h"
#include "CStatus.h"
#include "CPlayer.h"
#include "CEffect.h"

CState_Stun::CState_Stun(eSTATE_PLAYER state)
	: CState_Player(state)
{
	m_fvDir = {};
	m_fDura = 0.f;
	m_fSpd = 100.f;
}

CState_Stun::~CState_Stun()
{
}

void CState_Stun::update(UINT& chk)
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
			changeMyState(getOwner(), eSTATE_PLAYER::IDLE);
		}
	}

	m_fvDir = m_fvDir.normalize();

	pos.x += m_fvDir.x * m_fSpd * fDT;

	if (chk & SP_AIR)
	{
		pos.y += m_fvDir.y * m_fSpd * fDT;

		if (info.fSpdY < 0.f)
			chk |= SP_GODOWN;
	}

	getPlayer()->setPos(pos);
	getPlayer()->setPlayerInfo(info);
}

void CState_Stun::enter()
{
	getPlayer()->playAnim(L"Stun");
	getPlayer()->setCheck(SP_STOPANIM, true);
	getPlayer()->setCheck(SP_NODMG, true);
	m_fvDir = getPlayer()->getPlayerInfo().fvKnockBackDir;

	fPoint pos = getPlayer()->getPos();
	tPlayerInfo info = getPlayer()->getPlayerInfo();

	info.fNoDmgTimer = 2.0f + (float)P_STUNDURA;

	getPlayer()->setPlayerInfo(info);

	m_fDura = (float)P_STUNDURA;

	CEffect* pEff = new CEffect;
	pEff->load(L"Effect_stunImpact", L"texture\\effect\\effect_stun_impact.bmp");
	pEff->setDuration(0.42f);

	pEff->createAnim(L"effect_stunimpact", pEff->getTex(),
		fPoint(0, 0), fPoint(308, 270), fPoint(308, 0), 0.06f, 7, false);

	pEff->setPos(pos);
	pEff->PLAY(L"effect_stunimpact");
	createObj(pEff, eOBJ::EFFECT);

	CSoundManager::getInst()->addSound(L"hero_damage", L"sound\\player\\hero_damage.wav");
	CSoundManager::getInst()->play(L"hero_damage", 0.1f);
}

void CState_Stun::exit()
{
	getPlayer()->setCheck(SP_STOPANIM, false);

	m_fDura = 0.f;
	m_fvDir = {};
}

void CState_Stun::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getPlayer()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Stun";
	wchar_t bufDura[255] = {};

	swprintf_s(bufDura, L"dura = %.1f", m_fDura);

	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 150, strInfo, (int)wcslen(strInfo));
	TextOutW(hDC, (int)pos.x - 150, (int)pos.y - 125, bufDura, (int)wcslen(bufDura));
}
