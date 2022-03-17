#pragma once
#include "CObject.h"

class CObject;

class CAttack : public CObject
{
	eDIR	m_eDir;
	float	m_fDura;
	UINT	m_uiDmg;

	CObject* m_pOwner;

public:
	CAttack();
	virtual ~CAttack();
	virtual CAttack* clone();

	virtual void update();
	virtual void render(HDC hDC);
	
	void setDir(eDIR dir);
	void setDura(float dura);
	void setDmg(UINT dmg);
	void setOwner(CObject* pOwner);

	CObject* getOwner();

	void collisionEnter(CCollider* pOther);
};