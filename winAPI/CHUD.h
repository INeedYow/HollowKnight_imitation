#pragma once
#include "CObject.h"

class CTexture;

class CHUD :  public CObject
{
	CTexture* m_pTex;

public:
	CHUD();
	virtual ~CHUD();

	virtual void update();
	virtual void render(HDC hDC);

	void setTex(const wstring& strKey, const wstring& strPath);
	CTexture* getTex();
};

