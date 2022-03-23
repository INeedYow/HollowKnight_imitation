#include "framework.h"
#include "CState_Stop.h"
#include "CMonster.h"

#include "SelectGDI.h"

CState_Stop::CState_Stop(eSTATE_MONS state)
	:CState_Mons(state)
{
	m_fTimer = 0.f;
}

CState_Stop::~CState_Stop()
{
}

void CState_Stop::update(UINT& chk)
{
	tMonsInfo info = getMonster()->getMonsInfo();
	fPoint pos = getMonster()->getPos();
	fPoint size = getMonster()->getSize();
	// 상태끼리 변화는 되도록 상태내에서 처리하는게 유지 관리 하기 편할 것 같긴 한데
	// 아무래도 여러 상태에서 중복으로 처리할 경우 그냥 해당 obj update()에서 하는 게
	if (chk & SM_TRACE)
	{
		if (pos.y - size.y / 2.f < getMyPos().y &&
			getMyPos().y < pos.y + size.y / 2.f)
		{
			if (info.fDist < info.fTraceRange)
			{
				changeMonsState(getOwner(), eSTATE_MONS::TRACE);
			}
		}
	}
	m_fTimer -= fDT;

	if (m_fTimer < 0.f)
	{
		changeMonsState(getOwner(), eSTATE_MONS::PATROL);
	}
}

void CState_Stop::enter()
{
	m_fTimer = 2.5f;
}

void CState_Stop::exit()
{
	m_fTimer = 0.f;
}

void CState_Stop::printInfo(HDC hDC)
{
	SelectGDI font(hDC, eFONT::COMIC24);

	fPoint pos = getMonster()->getPos();
	pos = rendPos(pos);

	LPCWSTR	strInfo = L"Stop";
	TextOutW(hDC, (int)pos.x + 0, (int)pos.y - 125, strInfo, (int)wcslen(strInfo));
}
