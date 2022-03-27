#pragma once
#include "CImage.h"

// TODO �Լ�������
class CWarp : public CImage
{
	bool	m_bActive;
	fPoint	m_fpImgOffset;

public:
	CWarp();
	virtual ~CWarp();

	virtual void update();
	virtual void render(HDC hDC);

	void setImageOffset(fPoint imgOffset);

	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);
};

