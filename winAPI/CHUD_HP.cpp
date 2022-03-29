#include "framework.h"
#include "CHUD_HP.h"
#include "CEffect.h"
#include "CTexture.h"

CHUD_HP::CHUD_HP()
{
	setPos(fPoint(UI_HP_POSX, UI_HP_POSY));
	setSize(fPoint((float)HP_SIZE_X, (float)HP_SIZE_Y));

	setTex(L"Player_Tex", L"texture\\UI\\UI_hpMax2.bmp");

	//createAnimator();
}

CHUD_HP::~CHUD_HP()
{
}

void CHUD_HP::update()
{
}

void CHUD_HP::render(HDC hDC)
{
	UINT hp = gameGetPlayer()->getPlayerInfo().uiHP;

	TransparentBlt(hDC,
		(int)UI_HP_POSX, 
		(int)UI_HP_POSY,
		(int)(HP_SIZE_X * hp),
		(int)(HP_SIZE_Y), 
		getTex()->getDC(),
		0, 0,			  
		(int)(HP_SIZE_X * hp),
		(int)(HP_SIZE_Y), 
		RGB(255, 0, 255)
	);
}
