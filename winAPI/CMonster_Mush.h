#pragma once
#include "CMonster.h"
class CMonster_Mush : public CMonster
{
	float	m_fTimer;

public:
	CMonster_Mush();
	virtual ~CMonster_Mush();

	virtual CMonster_Mush* clone();

	virtual void update();
	virtual void render(HDC hDC);
};

// TODO 몬스터 패턴 분석