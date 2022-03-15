#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

public:
	void update();

private:
	CUI* getTargetUI(CUI* pParentUI);		// 현재 선택된 UI의 자식 UI들까지 검사
};

