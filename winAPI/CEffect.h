#pragma once
#include "CObject.h"

class CTexture;

struct tEffectInfo
{
	float fTimer;
	float fDura;
};

class CEffect : public CObject
{
	CTexture* m_pTex;

	tEffectInfo m_tInfo;

public:
	CEffect();
	virtual ~CEffect();

	virtual void update();
	virtual void render(HDC hDC);
};