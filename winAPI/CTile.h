#pragma once
#include "CObject.h"
class CTile : public CObject
{
	CTexture* m_pTex;
	int			m_iIndex;		// index

public:
	const static int SIZE_TILE = 32;		// #define�� ����� �뵵

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

// Ÿ���� ���� 2^n ũ��� ���� ũ��� �����
// �׷��� index�� ��������