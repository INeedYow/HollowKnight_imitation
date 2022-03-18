#pragma once
#include "CButtonUI.h"

class CTexture;

class CButtonUI_Image : public CButtonUI
{
	CTexture* m_pTex;

public:
	CButtonUI_Image();
	virtual ~CButtonUI_Image();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);
};

