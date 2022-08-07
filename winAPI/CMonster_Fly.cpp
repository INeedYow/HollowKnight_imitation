#include "framework.h"
#include "CMonster_Fly.h"

#include "CAI.h"
#include "CState_Mons.h"
#include "CPlayer.h"
#include "CAttack.h"
#include "SelectGDI.h"

CMonster_Fly::CMonster_Fly()
{
	m_fTurnTimer = 0.f;
}

CMonster_Fly::~CMonster_Fly()
{
}

CMonster_Fly* CMonster_Fly::clone()
{
	return nullptr;
}

void CMonster_Fly::update()
{
	fPoint playerPos = gameGetPlayer()->getPos();
	tMonsInfo info = getMonsInfo();
	fPoint pos = getPos();

	info.fDist = (float)sqrt((pos.x - playerPos.x) * (pos.x - playerPos.x) 
		+ (pos.y - playerPos.y) * (pos.y - playerPos.y));
	setMonsInfo(info);

	CMonster::update();						// ai, anim update

	if (isCheck(SM_DEATH))					// 죽은 경우 이후 업데이트 X
		return;

	if (isCheck(SM_TURN))					// 방향전환 상태
	{
		playAnim(L"Turn");

		m_fTurnTimer -= fDT;

		if (m_fTurnTimer < 0.f)
		{
			setCheck(SM_TURN, false);		// 방향전환 상태 종료
		}
	}

	extraUpdate(); 
}

void CMonster_Fly::extraUpdate()
{
	fPoint pos = getPos();
	tMonsInfo info = getMonsInfo();

	// 방향전환
	if (isCheck(SM_DIR) && info.fvDir.x < 0.f)
	{
		m_fTurnTimer = 0.5f;
		setCheck(SM_TURN, true);

		playAnim(L"Turn");
		info.fvDir.x = -1.f;
		setCheck(SM_DIR, false);
	}
	else if (!isCheck(SM_DIR) && info.fvDir.x > 0.f)
	{
		m_fTurnTimer = 0.5f;
		setCheck(SM_TURN, true);

		playAnim(L"Turn");
		info.fvDir.x = 1.f;
		setCheck(SM_DIR, true);
	}

	setPos(pos);
	setMonsInfo(info);
}

void CMonster_Fly::render(HDC hDC)
{
	if (g_bDebug)
	{
		printInfo(hDC);
		getAI()->getCurState()->printInfo(hDC);
	}
	componentRender(hDC);
}

void CMonster_Fly::collisionEnter(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();
	tMonsInfo info;

	switch (pTarget->getName())
	{
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

	case eOBJNAME::MISSILE_PLAYER:
	{
		if (!isCheck(SM_DEATH))
		{
			tMonsInfo info = getMonsInfo();
			info.iHP -= 2;

			info.fvKnockBackDir.x = 1.f;
			if (gameGetPlayer()->getPos().x > pOther->getPos().x)
				info.fvKnockBackDir.x = -1.f;
			info.fKnockBackSpd = (float)SM_KBSPD_M;
			info.fKnockBackTimer = (float)SM_KBTIME;

			setMonsInfo(info);
		}
		break;
	}

	case eOBJNAME::GROUND:
	{
		if (isTopCollOnly(getCollider(), pOther))
		{	// 위
			fPoint pos = getPos();

			pos.y = pOther->getPos().y - pOther->getSize().y * 0.5f + pOther->getOffset().y
				- getCollider()->getSize().y * 0.5f - getCollider()->getOffset().y + 1;

			setPos(pos);

		}
		else if (isBottomCollOnly(getCollider(), pOther))
		{
			fPoint pos = getPos();

			pos.y = pOther->getPos().y + pOther->getSize().y * 0.5f + pOther->getOffset().y
				+ getCollider()->getSize().y * 0.5f + getCollider()->getOffset().y;

			setPos(pos);
		}
		break;
	}
	case eOBJNAME::WALL:
	{
		if (isLeftColl(getCollider(), pOther))
		{	// 좌
			fPoint pos = getPos();

			pos.x = pOther->getPos().x - pOther->getSize().x * 0.5f + pOther->getOffset().x
				- getCollider()->getSize().x * 0.5f + getCollider()->getOffset().x - 1;

			setPos(pos);
		}
		else
		{	// 우
			fPoint pos = getPos();

			pos.x = pOther->getPos().x + pOther->getSize().x * 0.5f + pOther->getOffset().x
				+ getCollider()->getSize().x * 0.5f + getCollider()->getOffset().x + 1;

			setPos(pos);
		}
	}
	}
}

void CMonster_Fly::collisionKeep(CCollider* pOther)
{
	CObject* pTarget = pOther->getOwner();
	tMonsInfo info;

	switch (pTarget->getName())
	{
	case eOBJNAME::GROUND:
	{
		if (isTopCollOnly(getCollider(), pOther))
		{	// 위
			fPoint pos = getPos();

			pos.y = pOther->getPos().y - pOther->getSize().y * 0.5f + pOther->getOffset().y
				- getCollider()->getSize().y * 0.5f - getCollider()->getOffset().y + 1;

			setPos(pos);

		}
		else if (isBottomCollOnly(getCollider(), pOther))
		{
			fPoint pos = getPos();

			pos.y = pOther->getPos().y + pOther->getSize().y * 0.5f + pOther->getOffset().y
				+ getCollider()->getSize().y * 0.5f + getCollider()->getOffset().y;

			setPos(pos);
		}
		break;
	}
	case eOBJNAME::WALL:
	{
		if (isLeftColl(getCollider(), pOther))
		{	// 좌
			fPoint pos = getPos();

			pos.x = pOther->getPos().x - pOther->getSize().x * 0.5f + pOther->getOffset().x
				- getCollider()->getSize().x * 0.5f + getCollider()->getOffset().x - 1;

			setPos(pos);
		}
		else
		{	// 우
			fPoint pos = getPos();

			pos.x = pOther->getPos().x + pOther->getSize().x * 0.5f + pOther->getOffset().x
				+ getCollider()->getSize().x * 0.5f + getCollider()->getOffset().x + 1;

			setPos(pos);
		}
		break;
	}
	}
}


void CMonster_Fly::death()
{
	changeMonsState(getAI(), eSTATE_MONS::DIE);
}



void CMonster_Fly::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getPos();
	tMonsInfo info = getMonsInfo();
	fPoint playerPos = gameGetPlayer()->getPos();

	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufHP[255] = {};

	swprintf_s(bufX, L"x = %.1f", pos.x);
	swprintf_s(bufY, L"y = %.1f", pos.y);
	swprintf_s(bufHP, L"HP = %d", info.iHP);

	// bufX,Y 출력보다 아래 위치해야 함
	pos = rendPos(pos);

	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 250, bufX, (int)wcslen(bufX));
	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 225, bufY, (int)wcslen(bufY));
	TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 200, bufHP, (int)wcslen(bufHP));

	if (0.f != info.fNoticeRange)
	{
		wchar_t bufDist[255] = {};
		wchar_t bufTRng[255] = {};
		swprintf_s(bufTRng, L"Range = %.1f", info.fNoticeRange);
		swprintf_s(bufDist, L"DistX = %.1f", info.fDist);
		TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 150, bufTRng, (int)wcslen(bufTRng));
		TextOutW(hDC, (int)pos.x + 100, (int)pos.y - 175, bufDist, (int)wcslen(bufDist));
	}
}
