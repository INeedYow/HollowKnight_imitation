#include "framework.h"
#include "CHUD_Soul.h"
#include "CEffect.h"
#include "CTexture.h"

CHUD_Soul::CHUD_Soul()
{
	setPos(fPoint(UI_SOUL_POSX, UI_SOUL_POSY));

	setTex(L"HUD_Frame", L"texture\\UI\\UI_hp_frame.bmp");
	m_pSoulTex = loadTex(L"HUD_SOUL", L"texture\\UI\\UI_soul_full.bmp");
	m_fpOffset = { UI_SOUL_OFFX, UI_SOUL_OFFY };
}

CHUD_Soul::~CHUD_Soul()
{
}

void CHUD_Soul::update()
{
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
	UINT height = SOUL_MAX - gameGetPlayer()->getPlayerInfo().uiSoul / SOUL_MAX;
	
	// soul
	TransparentBlt(hDC,
		(int)UI_SOUL_POSX,
		(int)pos.y,
		(int)(m_pSoulTex->getBmpWidth()),
		(int)(getTex()->getBmpHeight() - gameGetPlayer()->getPlayerInfo().uiSoul / SOUL_MAX),
		m_pSoulTex->getDC(),
		0, 
		(int)(gameGetPlayer()->getPlayerInfo().uiSoul / SOUL_MAX),
		(int)(m_pSoulTex->getBmpWidth()),
		(int)(m_pSoulTex->getBmpHeight() - gameGetPlayer()->getPlayerInfo().uiSoul / SOUL_MAX),
		RGB(255, 0, 255)
	);
}
