#pragma once
#include "CImage.h"

//typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class CWarp : public CImage
{
	bool	m_bActive;
	fPoint	m_fpImgOffset;

	eSCENE	m_eDestScn;

public:
	CWarp();
	virtual ~CWarp();

	virtual void update();
	virtual void render(HDC hDC);

	void setDestScene(eSCENE eScn);
	void setImageOffset(fPoint imgOffset);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);

};