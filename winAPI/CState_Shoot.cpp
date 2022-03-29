#include "framework.h"
#include "CState_Shoot.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CAI.h"
#include "CMonster_Fly.h"
#include "CMissile.h"

CState_Shoot::CState_Shoot(eSTATE_MONS state)
	:CState_Mons(state) 
{
	m_fDura = 0.f;
	m_fDelay = 0.f;
}

CState_Shoot::~CState_Shoot()
{
}

void CState_Shoot::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();

	getMonster()->playAnim(L"Shoot");

	if (m_fDelay > 0.f)
	{
		m_fDelay -= fDT;

		if (m_fDelay < 0.f)
		{
			switch (getMonster()->getName())
			{
			case eOBJNAME::MONS_BEE:
			{
				CMissile* pMsl = new CMissile;
				pMsl->setTex(L"Missile_bee", L"texture\\attack\\missile_bee.bmp");
				pMsl->createAnim(L"Missile_bee", pMsl->getTex(),
					fPoint(0.f, 0.f), fPoint(60, 54), fPoint(60, 0.f), 0.25f, 3);
				pMsl->PLAY(L"Missile_bee");

				if (chk & SM_DIR)
				{
					pos.x += 20.f;
				}
				else
				{
					pos.x -= 20.f;
				}
				pos.y -= 10.f;
				pMsl->setPos(pos);
				pMsl->setName(eOBJNAME::MISSILE_MONSTER);
				pMsl->setSize(fPoint(42.f, 42.f));
				pMsl->setDir(fVec2(playerPos - pos));
				pMsl->getCollider()->setSize(fPoint(38.f, 38.f));
				pMsl->getCollider()->setShape(eSHAPE::CIRCLE);
				pMsl->setSpeed(300.f);

				createObj(pMsl, eOBJ::MISSILE_MONSTER);
				break;
			}
			}
		m_fDelay = 0.f;
		}
	}

	m_fDura -= fDT;
	if (m_fDura <= 0.f || info.fDist > M_BE_SHOOT_RNG)
	{
		changeMonsState(getOwner(), eSTATE_MONS::STOP);
	}

	getMonster()->setMonsInfo(info);
}

void CState_Shoot::enter()
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();

	if (pos.x < playerPos.x)
	{
		info.fvDir.x = 1.f;
	}
	else
	{
		info.fvDir.x = -1.f;
	}

	getMonster()->setMonsInfo(info);

	getMonster()->playAnim(L"Shoot");

	m_fDura = info.fDura;
	m_fDelay = info.fDelay;
}

void CState_Shoot::exit()
{
	m_fDura = 0.f;
	m_fDelay = 0.f;
}

void CState_Shoot::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC28);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Shoot";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 95, strInfo, (int)wcslen(strInfo));
}
