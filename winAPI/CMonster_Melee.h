#pragma once
#include "CMonster.h"

class CMonster_Melee : public CMonster
{
	int m_iBottomCnt;

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
};

#define M_BT_SIZEX			100
#define M_BT_SIZEY			120

#define M_BT_HP				120
#define M_BT_SPD			120
#define M_BT_TRACE_RNG		300
#define	M_BT_ATK_RND		60