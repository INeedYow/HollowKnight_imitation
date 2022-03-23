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
	// ���³��� ��ȭ�� �ǵ��� ���³����� ó���ϴ°� ���� ���� �ϱ� ���� �� ���� �ѵ�
	// �ƹ����� ���� ���¿��� �ߺ����� ó���� ��� �׳� �ش� obj update()���� �ϴ� ��
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
