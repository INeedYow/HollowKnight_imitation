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
	CUI* getTargetUI(CUI* pParentUI);		// 현재 선택된 UI의 자식 UI들까지 검사
	CUI* getFocusUI();
};

