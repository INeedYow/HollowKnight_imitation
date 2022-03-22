#include "framework.h"
#include "CScene_Stage02.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CBoss_Markoth.h"

#define STG02_SIZEX 3840
#define STG02_SIZEY 2160

CScene_Stage02::CScene_Stage02()
{
}

CScene_Stage02::~CScene_Stage02()
{
}

void CScene_Stage02::update()
{
	CScene::update();

	fPoint camPos = getCamPos();

	if (KEY_ON(VK_ESCAPE))
			changeScn(eSCENE::TITLE);

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_03);
}

void CScene_Stage02::enter()
{
	camFadeIn(0.8f);

	CObject* pPlayer = CPlayer::createNormal(fPoint(1963, 60.f));
	addObject(pPlayer, eOBJ::PLAYER);
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	CBackGround* pBGBack = new CBackGround;
	pBGBack->load(L"BG_stage2B", L"texture\\background\\stage2_back.bmp");
	pBGBack->setPos(fPoint(0.f, 0.f));
	addObject(pBGBack, eOBJ::BACKGROUND);

	//CFrontGround* pBGFront = new CFrontGround;
	//pBGFront->load(L"BG_stage1F", L"texture\\background\\bossStage_back.bmp");
	//pBGFront->setPos(fPoint(0.f, 0.f));
	//addObject(pBGFront, eOBJ::FRONTGROUND);

	CGround* pLfTWall1 = new CGround;
	pLfTWall1->setPos(fPoint(930.f, 255.f));
	pLfTWall1->getCollider()->setSize(fPoint(1860.f, 510.f));
	addObject(pLfTWall1, eOBJ::GROUND);

	CGround* pLfTWall2 = new CGround;
	pLfTWall2->setPos(fPoint(646.f, 562.f));
	pLfTWall2->getCollider()->setSize(fPoint(1292.f, 1124.f));
	addObject(pLfTWall2, eOBJ::GROUND);

	CGround* pLfTWall3 = new CGround;
	pLfTWall3->setPos(fPoint(1730.f, 928.f));
	pLfTWall3->getCollider()->setSize(fPoint(260.f, 636.f));
	addObject(pLfTWall3, eOBJ::GROUND);

	CGround* pLfTWall4 = new CGround;
	pLfTWall4->setPos(fPoint(800.f, 867.f));
	pLfTWall4->getCollider()->setSize(fPoint(1600.f, 514.f));
	addObject(pLfTWall4, eOBJ::GROUND);

	CGround* pGrd1 = new CGround;
	pGrd1->setPos(fPoint(1913.f, 1510.f));
	pGrd1->getCollider()->setSize(fPoint(954.f, 170.f));
	addObject(pGrd1, eOBJ::GROUND);

	CGround* pGrd2 = CGround::create(500, 1470, 1254, STG02_SIZEY);
	addObject(pGrd2, eOBJ::GROUND);

	CGround* pGrd3 = CGround::create(2060, 0, 2300, 1248);
	addObject(pGrd3, eOBJ::GROUND);

	CGround* pGrd4 = CGround::create(2300, 0, STG02_SIZEX, 1060);
	addObject(pGrd4, eOBJ::GROUND);
	
	CGround* pGrd5 = CGround::create(50, 1422, 308, 1542);
	addObject(pGrd5, eOBJ::GROUND);

	CGround* pGrd6 = CGround::create(0, 1710, 900, STG02_SIZEY);
	addObject(pGrd6, eOBJ::GROUND);

	CGround* pGrd7 = CGround::create(420, 1626, 1336, STG02_SIZEY);
	addObject(pGrd7, eOBJ::GROUND);

	CGround* pGrd8 = CGround::create(1336, 1785, STG02_SIZEX, STG02_SIZEY);
	addObject(pGrd8, eOBJ::GROUND);

	CGround* pGrd9 = CGround::create(1784, 1584, 2840, STG02_SIZEY);
	addObject(pGrd9, eOBJ::GROUND);

	CGround* pGrd10 = CGround::create(2558, 1422, 2668, 1460);
	addObject(pGrd10, eOBJ::GROUND);

	CGround* pGrd11 = CGround::create(2884, 1390, 3062, 1433);
	addObject(pGrd11, eOBJ::GROUND);

	CGround* pGrd12 = CGround::create(3250, 1374, 3364, 1406);
	addObject(pGrd12, eOBJ::GROUND);

	CGround* pGrd13 = CGround::create(2840, 1668, STG02_SIZEX, STG02_SIZEY);
	addObject(pGrd13, eOBJ::GROUND);

	CGround* pGrd14 = CGround::create(3550, 1350, STG02_SIZEX, STG02_SIZEY);
	addObject(pGrd14, eOBJ::GROUND);



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
}

void CScene_Stage02::exit()
{
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.8f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
