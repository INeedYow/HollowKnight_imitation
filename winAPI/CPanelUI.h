#pragma once
#include "CUI.h"
class CPanelUI : public CUI
{

	fPoint m_fpDragStart;

public:
	CPanelUI();
	~CPanelUI();

	virtual CPanelUI* clone();

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
};

