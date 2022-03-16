#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

private:
	CUI* m_pFocusUI;

public:
	void update();

	void setFocusUI(CUI* pUI);

private:
	CUI* getTargetUI(CUI* pParentUI);		// ���� ���õ� UI�� �ڽ� UI����� �˻�
	CUI* getFocusUI();
};

