#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);

public:
	void update();

private:
	CUI* getTargetUI(CUI* pParentUI);		// ���� ���õ� UI�� �ڽ� UI����� �˻�
};

