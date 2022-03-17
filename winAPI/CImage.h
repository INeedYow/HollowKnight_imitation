#pragma once
#include "CObject.h"

class CTexture;

class CImage : public CObject
{
	CTexture* m_pTex;

public:
	CImage();
	virtual ~CImage();

	virtual CObject* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);
};