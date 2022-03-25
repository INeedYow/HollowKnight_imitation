#pragma once
#include "CMonster.h"

class CMonster_Melee : public CMonster
{
	float m_fSpdY;
	int m_iBottomCnt;

public:
	CMonster_Melee();
	~CMonster_Melee();

	virtual CMonster_Melee* clone();

	//static CMonster_Melee* create(eOBJNAME eName, fPoint pos);

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);
	void collisionExit(CCollider* pOther);

	virtual void death();

private:
	void yPosUpdate();
	void printInfo(HDC hDC);
};

#define M_GRAV				2000
#define M_SPDY_MIN			-700

#define M_BT_SIZEX			80
#define M_BT_SIZEY			120

#define M_BT_HP				4
#define M_BT_SPD			200
#define M_BT_TRACE_RNG		450