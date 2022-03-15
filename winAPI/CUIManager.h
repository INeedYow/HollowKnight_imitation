#pragma once
class CUIManager
{
	SINGLETON(CUIManager);

public:
	void update();
	void render(HDC hDC);
};

