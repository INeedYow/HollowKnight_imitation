#include "framework.h"
#include "CHUD_Soul.h"
#include "CEffect.h"
#include "CTexture.h"

CHUD_Soul::CHUD_Soul()
{
	setPos(fPoint(UI_SOUL_POSX, UI_SOUL_POSY));

	setTex(L"HUD_Frame", L"texture\\UI\\UI_hp_frame2.bmp");
	m_pSoulTex = loadTex(L"HUD_SOUL", L"texture\\UI\\UI_soul_full2.bmp");
	m_fpOffset = { UI_SOUL_OFFX, UI_SOUL_OFFY };

	m_uiSoul = 0;
	m_uiEmpty = 100;
}

CHUD_Soul::~CHUD_Soul()
{
}

void CHUD_Soul::update()
{
	if (m_uiSoul != gameGetPlayer()->getPlayerInfo().uiSoul)
	{
		m_uiSoul = gameGetPlayer()->getPlayerInfo().uiSoul;
		m_uiEmpty = (UINT)((SOUL_MAX - m_uiSoul) / (float)SOUL_MAX * m_pSoulTex->getBmpHeight());
	}
}

void CHUD_Soul::render(HDC hDC)
{
	// frame
	TransparentBlt(hDC,
		(int)UI_SOUL_POSX,
		(int)UI_SOUL_POSY,
		(int)(getTex()->getBmpWidth()),
		(int)(getTex()->getBmpHeight()),
		getTex()->getDC(),
		0, 0,
		(int)(getTex()->getBmpWidth()),
		(int)(getTex()->getBmpHeight()),
		RGB(255, 0, 255)
	);
	fPoint pos = { UI_SOUL_POSX + m_fpOffset.x, UI_SOUL_POSY + m_fpOffset.y };

	// soul
	TransparentBlt(hDC,
		(int)pos.x,
		(int)(pos.y + m_uiEmpty),
		(int)(m_pSoulTex->getBmpWidth()),
		(int)(m_pSoulTex->getBmpHeight() - m_uiEmpty),
		m_pSoulTex->getDC(),
		0, 
		(int)(m_uiEmpty),
		(int)(m_pSoulTex->getBmpWidth()),
		(int)(m_pSoulTex->getBmpHeight() - m_uiEmpty),
		RGB(255, 0, 255)
	);
}
