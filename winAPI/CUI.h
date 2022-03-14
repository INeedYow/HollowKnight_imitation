#pragma once
#include "CObject.h"
class CUI : public CObject
{
	vector<CUI*> m_vecChildUI;		// °èÃþ ±¸Á¶
	CUI* m_pParentUI;

	fPoint m_fpFinalPos;

public:
	CUI();
	virtual ~CUI();

	virtual CUI* clone();

	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC hDC);

	void updateChild();
	void finalUpdateChild();
	void rendChild(HDC hDC);

	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
	virtual void mouseLbtnClicked();

	fPoint getFinalPos();
	CUI* getParent();

	void addChild(CUI* pUI);
};

