#pragma once
#include "CMissile.h"

class CTexture;

class CSpear : public CMissile
{
	float	m_fTheta;		// 각도
	UINT	m_uiStep;		// 0 뒤로 움직임 + 조준 // 1 조준 // 2 대기 // 3 발사 // 4 재활용

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