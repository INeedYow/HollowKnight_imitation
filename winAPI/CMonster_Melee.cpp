#include "framework.h"
#include "CMonster_Melee.h"
#include "CAttack.h"

#include "CAI.h"
#include "CState_Stop.h"
#include "CState_Attack.h"
#include "CState_Patrol.h"
#include "CState_Trace.h"
#include "CPlayer.h"
#include "SelectGDI.h"

CMonster_Melee::CMonster_Melee()
{
	m_iBottomCnt = 0;
	m_fSpdY = 0.f;
}

CMonster_Melee::~CMonster_Melee()
{
}

CMonster_Melee* CMonster_Melee::clone()
{
	return nullptr;
}

//CMonster_Melee* CMonster_Melee::create(eOBJNAME eName, fPoint pos)
//{
//	CMonster_Melee* pMonsMl = nullptr;
//	tMonsInfo info = {};
//	CAI* pAI = nullptr;
//
//	switch (eName)
//	{
//	case eOBJNAME::MONS_BEETLE:
//	{
//		info.iHP = M_BT_HP;
//		info.fSpd = M_BT_SPD;
//		info.fTraceRange = M_BT_TRACE_RNG;
//		info.fAtkRange = M_BT_ATK_RND;
//
//		pMonsMl = new CMonster_Melee;
//		pMonsMl->setPos(pos);	//
//		pMonsMl->setName(eOBJNAME::MONS_BEETLE);	//
//		pMonsMl->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
//		pMonsMl->setMonsInfo(info);
//		pMonsMl->getCollider()->setSize(fPoint((float)M_BT_SIZEX, (float)M_BT_SIZEY));
//		pMonsMl->getCollider()->setOffset(fPoint(0.f, 10.f));
//		pMonsMl->setMonsInfo(info);
//
//		CAI* pAI = new CAI;
//		pAI->addState(new CState_Stop(eSTATE_MONS::STOP));
//		pAI->addState(new CState_Attack(eSTATE_MONS::ATTACK));
//		pAI->addState(new CState_Patrol(eSTATE_MONS::PATROL));
//		pAI->addState(new CState_Trace(eSTATE_MONS::TRACE));
//
//		pAI->setCurState(eSTATE_MONS::STOP);
//		pMonsMl->setAI(pAI);
//
//		pMonsMl->createAnimator();
//		pMonsMl->setTex(L"Mons_BeetleTex", L"texture\\monster\\mons_beetle\\mons_beetle.bmp");
//
//		pMonsMl->createAnim(L"BT_Stop_R", pMonsMl->getTex(),
//			fPoint(0, 0), fPoint(118, 192), fPoint(118, 0), 0.2f, 6);
//		pMonsMl->createAnim(L"BT_Stop_L", pMonsMl->getTex(),
//			fPoint(590, 192), fPoint(118, 192), fPoint(-118, 0), 0.2f, 6);
//
//		pMonsMl->createAnim(L"BT_Move_R", pMonsMl->getTex(),
//			fPoint(708, 0), fPoint(139, 192), fPoint(139, 0), 0.2f, 7);
//		pMonsMl->createAnim(L"BT_Move_L", pMonsMl->getTex(),
//			fPoint(1542, 192), fPoint(139, 192), fPoint(-139, 0), 0.2f, 7);
//
//		pMonsMl->createAnim(L"BT_Turn_R", pMonsMl->getTex(),
//			fPoint(1681, 0), fPoint(104, 192), fPoint(104, 0), 0.35f, 2);
//		pMonsMl->createAnim(L"BT_Turn_L", pMonsMl->getTex(),
//			fPoint(1785, 192), fPoint(104, 192), fPoint(-104, 0), 0.35f, 2);
//
//		pMonsMl->PLAY(L"BT_Stop_L");
//		break;
//	}
//	
//	}
//
//	return pMonsMl;
//
//}

void CMonster_Melee::update()
{
	fPoint playerPos = gameGetPlayer()->getPos();
	tMonsInfo info = getMonsInfo();
	info.fDist = playerPos.x - getPos().x;
	setMonsInfo(info);

	CMonster::update();		// ai, anim update

	yPosUpdate();
	animUpdate();
}

void CMonster_Melee::render(HDC hDC)
{
	getAI()->getCurState()->printInfo(hDC);

	componentRender(hDC);

	if (g_bDebug)
	{
		printInfo(hDC);
	}
}

void CMonster_Melee::collisionEnter(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();

	switch (pTarget->getName())
	{
	case eOBJNAME::ATTACK:
	{	// attck의 오너가 플레이어일 때
		if (eOBJNAME::PLAYER == ((CAttack*)pTarget)->getOwner()->getName())
		{
			tMonsInfo info = getMonsInfo();
			info.iHP--;
			setMonsInfo(info);
		}
		break;
	}

	case eOBJNAME::MISSILE_PLAYER:
	{
		tMonsInfo info = getMonsInfo();
		info.iHP -= 2;
		setMonsInfo(info);
		break;
	}

	case eOBJNAME::GROUND:
	{
		switch (COLLRRW(getCollider(), pOther))
		{
		case eDIR::TOP:
		{
			fPoint pos = getPos();

			pos.y = pOther->getPos().y - pOther->getSize().y / 2.f + pOther->getOffset().y
				- getCollider()->getSize().y / 2.f - getCollider()->getOffset().y + 1;

			setPos(pos);
			setCheck(SM_FALL, false);
			m_iBottomCnt++;

			break;
		}
		case eDIR::LEFT:
		case eDIR::RIGHT:
		{	// 좌우 벽-> 방향 전환
			tMonsInfo info = getMonsInfo();
			info.fvDir.x *= -1;
			setMonsInfo(info);
			break;
		}
		}
		break;
	}

	}
}

void CMonster_Melee::collisionKeep(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
	{
		fPoint pos1 = getPos();
		fPoint size1 = getSize();
		fPoint pos2 = pOther->getPos();
		fPoint size2 = pOther->getSize();
		float edge = (size2.x  - size1.x) / 2.f;

		if (pos1.x >= pos2.x + edge)
			pos1.x = pos2.x + edge;
		else if (pos1.x <= pos2.x - edge)
			pos1.x = pos2.x - edge;
		
		break;
		setPos(pos1);
	}
	}
}

void CMonster_Melee::collisionExit(CCollider* pOther)
{
	switch (pOther->getOwner()->getName())
	{
	case eOBJNAME::TILE:
	case eOBJNAME::GROUND:
		if (isTopColl(getCollider(), pOther))
		{
			if (--m_iBottomCnt <= 0)
			{
				m_iBottomCnt = 0;
				setCheck(SM_FALL, true);
			}
		}
		break;
	}
}

void CMonster_Melee::death()
{
	changeMonsState(getAI(), eSTATE_MONS::DIE);
}

void CMonster_Melee::yPosUpdate()
{
	fPoint pos = getPos();
	tMonsInfo info = getMonsInfo();
	if (m_iBottomCnt <= 0)
	{
		m_fSpdY -= M_GRAV * fDT;

		if (m_fSpdY < 0.f)
			setCheck(SM_FALL, true);

		if (m_fSpdY < (float)M_SPDY_MIN)
			m_fSpdY = (float)M_SPDY_MIN;

		pos.y -= m_fSpdY * fDT;
	}
	setPos(pos);
	setMonsInfo(info);
}

void CMonster_Melee::animUpdate()
{
}

void CMonster_Melee::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);
	fPoint pos = getPos();
	tMonsInfo info = getMonsInfo();
	fPoint playerPos = gameGetPlayer()->getPos();
	
	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufHP[255] = {};
	wchar_t bufDist[255] = {};
	wchar_t bufTRng[255] = {};
	//wchar_t bufTest[255] = {};

	swprintf_s(bufX, L"x = %.1f", pos.x);
	swprintf_s(bufY, L"y = %.1f", pos.y);
	swprintf_s(bufHP, L"y = %d", info.iHP);
	swprintf_s(bufDist, L"DistX = %.1f", info.fDist);
	swprintf_s(bufTRng, L"TRange = %.1f", info.fTraceRange);
	//swprintf_s(bufTest, L"playerPos = %.1f, \t %.1f", playerPos.x, playerPos.y);
	// bufX,Y 출력보다 아래 위치해야 함
	pos = rendPos(pos);

	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 250, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 225, bufY, (int)wcslen(bufY));
	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 200, bufHP, (int)wcslen(bufHP));
	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 175, bufDist, (int)wcslen(bufDist));
	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 150, bufTRng, (int)wcslen(bufTRng));
	//TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 100, bufTest, (int)wcslen(bufTest));
}
