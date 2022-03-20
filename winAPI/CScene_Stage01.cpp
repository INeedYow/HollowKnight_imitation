#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CBoss_Markoth.h"

CScene_Stage01::CScene_Stage01()
{

}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);
}

void CScene_Stage01::enter()
{
	camFadeOut(0.6f);
	camFadeIn(0.6f);

	// Player 추가
	CObject* pPlayer = CPlayer::createNormal(fPoint(200.f, 1500.f));
	pPlayer->setPos(fPoint(20.f, 1500.f));
	addObject(pPlayer, eOBJ::PLAYER);

	//// Monster 추가
	//CMonster* pMonster = new CMonster;
	//pMonster->setPos(fPoint(1100, 350));
	//addObject(pMonster, eOBJ::MONSTER);

	CBoss_Markoth* pBoss = new CBoss_Markoth;
	pBoss->setPos(fPoint(1200.f, 1270.f));
	pBoss->setSize(fPoint(300.f, 400.f));
	pBoss->getCollider()->setSize(fPoint(200.f, 310.f));
	pBoss->getCollider()->setOffset(fPoint(0.f, 20.f));
	addObject(pBoss, eOBJ::BOSS);

	CBackGround* pBGBack = new CBackGround;
	pBGBack->load(L"BG_stage1B", L"texture\\background\\stage1_back.bmp");
	pBGBack->setPos(fPoint(0.f, 0.f));
	pBGBack->setSize(fPoint(991.f, 1518.f));
	addObject(pBGBack, eOBJ::BACKGROUND);

	/*CBackGround* pBGFront = new CBackGround;
	pBGFront->setName(OBJNAME::BACKGROUND);
	pBGFront->setMove(false);
	pBGFront->load(L"BG_stage1F", L"texture\\background\\stage1_front.bmp");
	addObject(pBGFront, OBJ::BACKGROUND);*/

	CGround* pGrd = new CGround;
	pGrd->setPos(fPoint(0.f, 1700.f));
	pGrd->getCollider()->setSize(fPoint(3000.f, 200.f));
	addObject(pGrd, eOBJ::GROUND);

	CGround* pGrd2 = new CGround;
	pGrd2->setPos(fPoint(200.f, 1520.f));
	pGrd2->getCollider()->setSize(fPoint(100.f, 100.f));
	addObject(pGrd2, eOBJ::GROUND);

	CGround* pGrd3 = new CGround;
	pGrd3->setPos(fPoint(-50.f, 1020.f));
	pGrd3->getCollider()->setSize(fPoint(50.f, 500.f));
	addObject(pGrd3, eOBJ::GROUND);

	CGround* pGrd4 = new CGround;
	pGrd4->setPos(fPoint(400.f, 1400.f));
	pGrd4->getCollider()->setSize(fPoint(200.f, 100.f));
	addObject(pGrd4, eOBJ::GROUND);

	g_bDebug = true;

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::BOSS);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::SHIELD);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	//checkGrp(eOBJ::PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	//checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::BOSS);

	checkGrp(eOBJ::ATTACK, eOBJ::BOSS);

	//camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();
	resetGrp();
}
