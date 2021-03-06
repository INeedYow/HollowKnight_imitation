#pragma once
#include "CObject.h"
class CTile : public CObject
{
	CTexture* m_pTex;
	int			m_iIndex;		// index

public:
	const static int SIZE_TILE = 32;		// #define과 비슷한 용도

	CTile();
	virtual ~CTile();
	virtual CTile* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void setTexture(CTexture* pTex);
	void setImageIndex(UINT idx);

	virtual void save(FILE* pFile);
	virtual void load(FILE* pFile);
};

// 타일은 보통 2^n 크기로 같은 크기로 사용함
// 그래서 index로 관리가능