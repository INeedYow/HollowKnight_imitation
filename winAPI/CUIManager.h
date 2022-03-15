#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

	CUI* m_pFocusUI;

	CUI* getFocusUI();
	CUI* getTargetUI(CUI* pParentUI);		// 현재 선택된 UI의 자식 UI들까지 검사
public:
	void update();

	void setFocusUI(CUI* pUI);
};

