#include "framework.h"
#include "CState_BMove.h"
#include "CBoss_Markoth.h"
#include "CMonster.h"
#include "SelectGDI.h"
#include "CPlayer.h"

CState_BMove::CState_BMove(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_ix = 0;
	m_iy = 0;
	m_iX = 0;
	m_iY = 0;

	m_ipDest = {};

	m_fDura = 0.f;
}

CState_BMove::~CState_BMove()
{
}

void CState_BMove::update(UINT& chk)
{
	fPoint pos = getMonster()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();

	m_fDura -= fDT;
	if (m_fDura < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::IDLE);
	}
	if (abs(m_ipDest.x - (int)pos.x) < 5 && 
		abs(m_ipDest.y - (int)pos.y) < 5 )
	{
		changeMonsState(getOwner(), eSTATE_MONS::MOVE);
	}

	pos.x += info.fvDir.x * info.fSpd * fDT;
	pos.y += info.fvDir.y * info.fSpd * fDT;

	getMonster()->setPos(pos);
}

void CState_BMove::enter()
{
	m_fDura = (rand() % 4 + 4) / 2.f;

	// 이동 좌표 랜덤 (플레이어와 보스 좌표로 그려지는 사각형 +알파 중 랜덤설정)
		// 거리가 가까워지면 멀어질 확률이 올라가고 멀어지면 가까워질 확률 올라가게
	fPoint pos = getMonster()->getPos();
	fPoint playerPos = gameGetPlayer()->getPos();
	tMonsInfo info = getMonster()->getMonsInfo();
	
	if (pos.x > playerPos.x)
	{
		m_ix = (int)playerPos.x - SB_AREA_ADDX;
		m_iX = (int)pos.x + SB_AREA_ADDX;
	}
	else
	{
		m_ix = (int)pos.x - SB_AREA_ADDX;
		m_iX = (int)playerPos.x + SB_AREA_ADDX;
	}

	if (pos.y > playerPos.y)
	{
		m_iy = (int)playerPos.y - SB_AREA_ADDY;
		m_iY = (int)pos.y + SB_AREA_ADDY;
	}
	else
	{
		m_iy = (int)pos.y - SB_AREA_ADDY;
		m_iY = (int)playerPos.y + SB_AREA_ADDY;
	}
	
	if (m_ix < SB_AREA_x) m_ix = SB_AREA_x;
	if (m_iX > SB_AREA_X) m_iX = SB_AREA_X;

	if (m_iy < SB_AREA_y) m_iy = SB_AREA_y;
	if (m_iY > SB_AREA_Y) m_iY = SB_AREA_Y;


	m_ipDest.x = rand() % (m_iX - m_ix + 1) + m_ix;

	m_ipDest.y = rand() % (m_iY - m_iy + 1) + m_iy;

	fVec2 vfDir = { m_ipDest.x - pos.x, m_ipDest.y - pos.y };
	
	info.fvDir = vfDir.normalize();

	getMonster()->setMonsInfo(info);

	getMonster()->PLAY(L"st_Normal");
	getMonster()->getCollider()->setSize(fPoint(SB_NmSIZEX, SB_NmSIZEY));
}

void CState_BMove::exit()
{
	m_fDura = 0.f;
}

void CState_BMove::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);
	SelectGDI pen(hDC, ePEN::WHITE);
	SelectGDI brush(hDC, eBRUSH::HOLLOW);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);
	
	fPoint lt = { (float)m_ix, (float)m_iy };
	fPoint rb = { (float)m_iX, (float)m_iY };
	lt = rendPos(lt);
	rb = rendPos(rb);

	fPoint dest;
	dest.x = (float)m_ipDest.x;
	dest.y = (float)m_ipDest.y;
	dest = rendPos(dest);

	LPCWSTR	strState = L"Move";
	wchar_t bufDura[255] = {};

	swprintf_s(bufDura, L"Dura = %.1f", m_fDura);

	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 125, strState, (int)wcslen(strState));
	TextOutW(hDC, (int)pos.x + 180, (int)pos.y + 145, bufDura, (int)wcslen(bufDura));
	
	// 보스 랜덤 이동 범위와 목표지점
	Rectangle(hDC, (int)lt.x, (int)lt.y, (int)rb.x, (int)rb.y);
	Ellipse(hDC, (int)dest.x - 15, (int)dest.y - 15, (int)dest.x + 15, (int)dest.y + 15);

}
