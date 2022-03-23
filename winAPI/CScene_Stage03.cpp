#include "framework.h"
#include "CScene_Stage03.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CBoss_Markoth.h"

#define STG03_SIZEX 3000
#define STG03_SIZEY 1689

CScene_Stage03::CScene_Stage03()
{
}

CScene_Stage03::~CScene_Stage03()
{
}

void CScene_Stage03::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_04);
}

void CScene_Stage03::enter()
{
	camFadeIn(0.5f);

	CObject* pPlayer = CPlayer::createNormal(fPoint(260.f, 1340.f));
	addObject(pPlayer, eOBJ::PLAYER);

	CBoss_Markoth* pBoss = new CBoss_Markoth;
	pBoss->setPos(fPoint(2270.f, 1040.f));
	pBoss->getCollider()->setSize(fPoint(200.f, 310.f));
	pBoss->getCollider()->setOffset(fPoint(0.f, 20.f));
	addObject(pBoss, eOBJ::BOSS);

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage3", L"texture\\background\\stage3_a.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	/*CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage3", L"texture\\background\\stage3_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);*/

	// ground
	CGround* pGrd1 = CGround::create(0, 1416, STG03_SIZEX, STG03_SIZEY);
	addObject(pGrd1, eOBJ::GROUND);

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::BOSS);

	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::ATTACK, eOBJ::BOSS);
	checkGrp(eOBJ::ATTACK, eOBJ::MONSTER);

	//
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	camSetArea(0.f, 0.f, STG03_SIZEX, STG03_SIZEY);
}

void CScene_Stage03::exit()
{
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
