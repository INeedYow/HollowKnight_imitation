#pragma once
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR, DWORD_PTR);

class CTriggerBox : public CObject
{
	BTN_FUNC	m_pFunc;
	DWORD_PTR	m_pParam1;
	DWORD_PTR	m_pParam2;
	DWORD_PTR	m_pParam3;
public:
	CTriggerBox();
	virtual ~CTriggerBox();

	virtual void update();
	virtual void render(HDC hDC);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

	void setCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2, DWORD_PTR param3);
};