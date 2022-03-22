#pragma once
#include "CObject.h"

class CAI;

class CMonster : public CObject
{
private:
	UINT	m_uiCheck;

	int		m_iHP;
	float	m_fSpd;

	CAI*	m_pAI;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* clone() = 0;

	virtual void update() = 0;
	virtual void render(HDC hDC) = 0;

	void collisionEnter(CCollider* pOther){}
	void collisionKeep(CCollider* pOther){}
	void collisionExit(CCollider* pOther){}

	void setCheck(UINT chk, bool isOn);
	void setHP(int hp);
	void setSpd(float spd);

	bool isCheck(UINT chk);
	int getHP();
	float getSpd();
};

#define SM_DIR		0x01
#define SM_AIR		0x02
