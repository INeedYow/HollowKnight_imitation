#include "framework.h"
#include "CState_Trace.h"
#include "CMonster.h"
#include "CPlayer.h"

// TODO 생성자 재정의 해서 상태 변수값 받으면 어떤가
CState_Trace::CState_Trace(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
	m_iStep = 0;
}

CState_Trace::~CState_Trace()
{
}

void CState_Trace::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	fPoint size = getMonster()->getSize();
	tMonsInfo info = getMonster()->getMonsInfo();

	if (playerPos.y < pos.y - size.y ||
		playerPos.y > pos.y + size.y / 2.f||
		info.fDist > info.fTraceRange)
	{
		m_iStep = 2;
	}

	m_fTimer += fDT;

	switch (m_iStep)
	{
	case 0:
	{
		getMonster()->playAnim(L"BT_TraceEnter");
		if (m_fTimer > 0.9f)
		{
			m_iStep++;
			m_fTimer = 0.f;
		}
		break;
	}
	case 1:
	{
		getMonster()->playAnim(L"BT_Trace");
		if (m_fTimer > 1.6f)
		{
			m_iStep++;
			m_fTimer = 0.f;
		}
		break;
	}
	case 2:
	{
		getMonster()->playAnim(L"BT_TraceExit");
		if (m_fTimer > 0.5f)
		{
			changeMonsState(getOwner(), eSTATE_MONS::STOP);
		}
		break;
	}
	}

	pos.x += info.fvDir.x * info.fSpd * fDT;

	getMonster()->setMonsInfo(info);
	getMonster()->setPos(pos);
}

void CState_Trace::enter()
{
	m_fTimer = 0.f;
	m_iStep = 0;

	tMonsInfo info = getMonster()->getMonsInfo();
	
	info.fvDir.x = -1;
	if (gameGetPlayer()->getPos().x > getMonster()->getPos().x)
		info.fvDir.x = 1;

	getMonster()->setMonsInfo(info);
}

void CState_Trace::exit()
{
	m_fTimer = 0.f;
	m_iStep = 0;
}

void CState_Trace::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Trace";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 65, strInfo, (int)wcslen(strInfo));
}

