#pragma once
#include "CUI.h"

// 함수포인터
typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CButtonUI : public CUI
{
	BTN_FUNC	m_pFunc;
	DWORD_PTR	m_pParam1;
	DWORD_PTR	m_pParam2;

public:
	CButtonUI();
	~CButtonUI();

	virtual CButtonUI* clone();

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
	virtual void mouseLbtnClicked();

	void setClickedCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2);
};