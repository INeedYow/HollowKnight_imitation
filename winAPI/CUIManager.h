#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

	CUI* m_pFocusUI;

	CUI* getFocusUI();
	CUI* getTargetUI(CUI* pParentUI);		// ���� ���õ� UI�� �ڽ� UI����� �˻�
public:
	void update();

	void setFocusUI(CUI* pUI);
};

