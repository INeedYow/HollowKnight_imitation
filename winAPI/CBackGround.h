#pragma once
#include "CObject.h"

class CTexture;

class CBackGround : public CObject
{
	CTexture*	m_pTex;

public:
	CBackGround();
	virtual ~CBackGround();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);
};

