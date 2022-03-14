#pragma once
#include "CObject.h"

class CTexture;

class CPlayer : public CObject
{
	CTexture*	m_pTex;
	float		m_fSpeed;

	void createMissile();

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* clone();

	virtual void update();
	virtual void render(HDC hDC);
};

