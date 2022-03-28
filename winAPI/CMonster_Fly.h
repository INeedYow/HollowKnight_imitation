#pragma once
#include "CMonster.h"
class CMonster_Fly :    public CMonster
{
	float	m_fSpdY;
	float	m_fTurnTimer;

public:
	CMonster_Fly();
	~CMonster_Fly();

	virtual CMonster_Fly* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);

	virtual void death();

private:
	void extraUpdate();
	void printInfo(HDC hDC);
};

// bee
#define M_BE_SIZEX			120
#define M_BE_SIZEY			80

#define M_BE_HP				2
#define M_BE_SPD			240
#define M_BE_ATT_RNG		500
