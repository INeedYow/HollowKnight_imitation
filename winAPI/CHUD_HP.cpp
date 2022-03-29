#include "framework.h"
#include "CHUD_HP.h"
#include "CEffect.h"
#include "CTexture.h"

CHUD_HP::CHUD_HP()
{
	setPos(fPoint(UI_HP_POSX, UI_HP_POSY));

	setTex(L"HUD_HP", L"texture\\UI\\UI_hpMax2.bmp");
	m_uiHP = 0;
	m_uiHPMax = 5;
	//createAnimator();
}

CHUD_HP::~CHUD_HP()
{
}

void CHUD_HP::update()
{
	//if (m_uiHP > gameGetPlayer()->getPlayerInfo().uiHP)
	//{	// 체력 감소 애니메이션 왜 안돼
	//	fPoint mPos = { (float)UI_HP_POSX + HP_SIZE_X / 2.f, (float)UI_HP_POSY + HP_SIZE_Y / 2.f };
	//	mPos.x += (m_uiHP * HP_SIZE_X) ;

	//	CEffect* pEff = new CEffect;
	//	pEff->load(L"effect_dash2t", L"texture\\effect\\effect_dash2t.bmp");
	//	pEff->createAnim(L"effect_dash2t", pEff->getTex(),
	//		fPoint(0, 0), fPoint(48, 87), fPoint(48, 0), 0.1f, 7, false);
	//	pEff->setPos(mPos);
	//	pEff->setDuration(0.7f);
	//	pEff->PLAY(L"effect_dash2t");

	//	createObj(pEff, eOBJ::EFFECT);
	//}
	m_uiHP = gameGetPlayer()->getPlayerInfo().uiHP;

	if (m_uiHP > m_uiHPMax)
		m_uiHP = m_uiHPMax;
}

void CHUD_HP::render(HDC hDC)
{
	UINT intervalX;
	
	// 현재 HP * 사이즈 만큼 체력칸 출력
	intervalX= HP_SIZE_X * m_uiHP;

	TransparentBlt(hDC,
		(int)UI_HP_POSX, 
		(int)UI_HP_POSY,
		(int)(intervalX),
		(int)(HP_SIZE_Y), 
		getTex()->getDC(),
		0, 
		0,			  
		(int)(intervalX),
		(int)(HP_SIZE_Y), 
		RGB(255, 0, 255)
	);
}
