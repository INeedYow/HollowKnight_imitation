#pragma once
#include "CObject.h"


class CMonster : public CObject
{
private:
	UINT	m_uiState;

	UINT	m_uiHP;
	float	m_fSpd;

public:
	CMonster();
	~CMonster();
	virtual CMonster* clone() = 0;

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;

	void collisionEnter(CCollider* pOther){}
	void collisionKeep(CCollider* pOther){}
	void collisionExit(CCollider* pOther){}

	void setState(UINT state, bool isOn);
	void setHP(UINT hp);
	void setSpd(float spd);

	bool isState(UINT state);
	UINT getHP();
	float getSpd();
};

#define SM_DIR		0x01
#define SM_AIR		0x02



// boss

#define SB_HPMAX	20

#define SB_NORMAL	0x1000
#define SB_MIDDLE	0x2000
#define SB_SKILL	0x4000

#define SB_TOGGLE	0x0100