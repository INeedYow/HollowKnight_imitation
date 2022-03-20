#pragma once
#include "CObject.h"

class CTexture;

class CFrontGround : public CObject
{
	CTexture* m_pTex;

public:
	CFrontGround();
	virtual ~CFrontGround();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);

};

