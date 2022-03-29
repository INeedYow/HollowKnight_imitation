#pragma once
#include "CHUD.h"
class CHUD_HP :  public CHUD
{
	const UINT HP_SIZE_X = 48;
	const UINT HP_SIZE_Y = 87;

public:
	CHUD_HP();
	virtual ~CHUD_HP();

	virtual void update();
	virtual void render(HDC hDC);
};


#define UI_HP_POSX		100
#define UI_HP_POSY		60

