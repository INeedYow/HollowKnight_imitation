#pragma once
#include "CHUD.h"

class CTexture;

class CHUD_Soul : public CHUD
{
	const UINT SOUL_MAX = 100;
		
	CTexture*	m_pSoulTex;
	fPoint		m_fpOffset;

public:
	CHUD_Soul();
	virtual ~CHUD_Soul();

	virtual void update();
	virtual void render(HDC hDC);
};

#define UI_SOUL_POSX		50
#define UI_SOUL_POSY		30

#define UI_SOUL_OFFX		40.f
#define UI_SOUL_OFFY		48.f