#pragma once
#include "CHUD.h"

class CTexture;

class CHUD_Soul : public CHUD
{
	const UINT SOUL_MAX = 100;
		
	UINT		m_uiSoul;
	UINT		m_uiEmpty;

	fPoint		m_fpOffset;
	CTexture*	m_pSoulTex;

public:
	CHUD_Soul();
	virtual ~CHUD_Soul();

	virtual void update();
	virtual void render(HDC hDC);
};

#define UI_SOUL_POSX		50
#define UI_SOUL_POSY		30

#define UI_SOUL_OFFX		36.f
#define UI_SOUL_OFFY		36.f