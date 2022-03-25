#include "framework.h"
#include "CScene_Stage04.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CBoss_Markoth.h"

#define STG04_SIZEX		3000
#define STG04_SIZEY		1689

CScene_Stage04::CScene_Stage04()
{
}

CScene_Stage04::~CScene_Stage04()
{
}

void CScene_Stage04::update()
{
	// TODO
}

void CScene_Stage04::enter()
{
	camFadeOut(0.5f);
	camFadeIn(0.6f);

	// Player Ãß°¡
	CPlayer* pPlayer = CPlayer::createNormal(fPoint(20.f, 1610.f));
	addObject(pPlayer, eOBJ::PLAYER);
	CGameManager::getInst()->registPlayer(pPlayer);

	CBoss_Markoth* pBoss = new CBoss_Markoth;
	pBoss->setPos(fPoint(1270.f, 1270.f));
	pBoss->getCollider()->setSize(fPoint(200.f, 310.f));
	pBoss->getCollider()->setOffset(fPoint(0.f, 20.f));
	addObject(pBoss, eOBJ::BOSS);

	CBackGround* pBGBack = new CBackGround;
	pBGBack->load(L"BG_stage1B", L"texture\\background\\bossroom_sample.bmp");
	pBGBack->setPos(fPoint(0.f, 0.f));
	pBGBack->setSize(fPoint(3000.f, 1689.f));
	addObject(pBGBack, eOBJ::BACKGROUND);

	//CFrontGround* pBGFront = new CFrontGround;
	//pBGFront->load(L"BG_stage1F", L"texture\\background\\bossStage_back.bmp");
	//pBGFront->setPos(fPoint(0.f, 0.f));
	//pBGFront->setSize(fPoint(3000.f, 1689.f));
	//addObject(pBGFront, eOBJ::FRONTGROUND);

	CGround* pGrd1 = new CGround;
	pGrd1->setPos(fPoint(1800.f, 1889.f));
	pGrd1->getCollider()->setSize(fPoint(4000.f, 400.f));
	addObject(pGrd1, eOBJ::GROUND);

	CGround* pGrd2 = new CGround;
	pGrd2->setPos(fPoint(700.f, 1280.f));
	pGrd2->getCollider()->setSize(fPoint(150.f, 160.f));
	addObject(pGrd2, eOBJ::GROUND);

	CGround* pGrd3 = new CGround;
	pGrd3->setPos(fPoint(300.f, 1480.f));
	pGrd3->getCollider()->setSize(fPoint(170.f, 160.f));
	addObject(pGrd3, eOBJ::GROUND);

	CGround* pGrd4 = new CGround;
	pGrd4->setPos(fPoint(1000.f, 1440.f));
	pGrd4->getCollider()->setSize(fPoint(200.f, 160.f));
	addObject(pGrd4, eOBJ::GROUND);

	CGround* pGrd5 = new CGround;
	pGrd5->setPos(fPoint(1630.f, 1420.f));
	pGrd5->getCollider()->setSize(fPoint(240.f, 160.f));
	addObject(pGrd5, eOBJ::GROUND);

	g_bDebug = true;

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::BOSS);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::SHIELD);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::BOSS);

	checkGrp(eOBJ::ATTACK, eOBJ::BOSS);

	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	camSetArea(0.f, 0.f, STG04_SIZEX, STG04_SIZEY);
}

void CScene_Stage04::exit()
{
	CGameManager::getInst()->savePlayerInfo();

	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
