#pragma once
#include "CObject.h"
class CUI : public CObject
{
	friend class CUIManager;

	vector<CUI*> m_vecChildUI;		// ���� ����
	CUI* m_pParentUI;

	fPoint m_fpFinalPos;			// �ڽ� UI�� ��� �θ� ��ġ�� �����

	bool	m_bCamAffect;
	bool	m_bMouseOn;
	bool	m_bLbtnDown;

public:
	CUI(bool bCamAff);
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
	bool isMouseOn();
	bool getCamAffect();

	void addChild(CUI* pUI);

	void mouseOnChk();
};

