#pragma once
#include "CMissile.h"

class CTexture;

class CSpear : public CMissile
{
	float	m_fTheta;		// ����
	UINT	m_uiStep;		// 0 �ڷ� ������ + ���� // 1 ���� // 2 ��� // 3 �߻� // 4 ��Ȱ��

	fVec2	m_fvDir;
	float	m_fSpd;

	bool	m_bActive;

	CTexture* m_pMemTex;

public:
	CSpear();
	~CSpear();

	virtual void update();
	virtual void render(HDC hDC);

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);

	void setSpd(float spd);
	void setActive(bool isOn);
	void setMemTex(const wstring& texName, UINT sizeX, UINT sizeY);

	bool isActive();

private:
	fPoint getRandPos();
};

#define SPR_SIZEX		380
#define SPR_SIZEY		85

#define MEMTEX_SIZE		(UINT)(SPR_SIZEX * 1.5f)		// ȸ���� �ؽ��� ���� ũ�⿩�� ��(x, y�� ��ͺ��� �� ����)