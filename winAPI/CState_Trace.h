#pragma once
#include "CState_Mons.h"
class CState_Trace : public CState_Mons
{
	float	m_fTimer;
	int		m_iStep;
public:
	CState_Trace(eSTATE_MONS state);
	~CState_Trace();

	virtual void update(UINT& chk);
	virtual void enter();
	virtual void exit();
	virtual void printInfo(HDC hDC);
};

