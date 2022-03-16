#pragma once
#include "CObject.h"

class CTexture;

class CBackGround : public CObject
{
	CTexture*	m_pTex;
	bool		m_bMove;

public:
	CBackGround();
	virtual ~CBackGround();

	virtual CBackGround* clone();
	virtual void update();
	virtual void render(HDC hDC);

	void setMove(bool isMove);
	void load(const wstring& strKey, const wstring& strPath);
};

