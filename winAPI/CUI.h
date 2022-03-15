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
	CUI(const CUI& other);
	virtual ~CUI();

	virtual CUI* clone() = 0;

	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC hDC);

	void updateChild();
	void finalUpdateChild();
	void rendChild(HDC hDC);

	// ���콺�� ��ȣ�ۿ뿡 üũ�ϰ� �ش� UI�� �Լ� ȣ����
	virtual void mouseOn();
	virtual void mouseLbtnDown();
	virtual void mouseLbtnUp();
	virtual void mouseLbtnClicked();

	fPoint getFinalPos();
	bool isMouseOn();
	bool isCamAffect();
	bool isLbtnDown();

	const vector<CUI*>& getChildUI();
	CUI* getParentUI();

	void addChild(CUI* pUI);

	void mouseOnChk();
};

