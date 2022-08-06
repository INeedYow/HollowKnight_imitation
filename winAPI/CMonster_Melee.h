#pragma once
#include "CMonster.h"

class CMonster_Melee : public CMonster
{
	int		m_iBottomCnt;
	float	m_fTurnTimer;

public:
	CMonster_Melee();
	~CMonster_Melee();

	virtual CMonster_Melee* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);
	void collisionExit(CCollider* pOther);

	virtual void death();

private:
	void extraUpdate();
	void printInfo(HDC hDC);
};

#define M_GRAV				2000
#define M_SPDY_MIN			-700

// beetle
#define M_BT_SIZEX			86
#define M_BT_SIZEY			142
#define M_BT_SIZEX_			180
#define M_BT_SIZEY_			100

#define M_BT_HP				4
#define M_BT_SPD			200
#define M_BT_TRACE_RNG		450

// mush
#define M_MS_SIZEX			110
#define M_MS_SIZEY			100

#define M_MS_HP				3
#define M_MS_SPD			260