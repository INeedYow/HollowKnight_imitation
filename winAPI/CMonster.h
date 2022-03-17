#pragma once
#include "CObject.h"


class CMonster : public CObject
{
private:
	fPoint	m_fpCenterPos;
	float	m_fSpeed;
	float	m_fDistance;
	bool	m_bUpDir;

public:
	CMonster();
	~CMonster();
	virtual CMonster* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void setCenterPos(fPoint point);

	void collisionEnter(CCollider* pOther);
};

#define SM_DIR		0x01
#define SM_AIR		0x02