#include "framework.h"
#include "CScene_Stage02.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CMonster_Melee.h"
#include "CAI.h"

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

	if (gameGetPlayer()->getPos().x >= STG02_SIZEX - 40)
		changeScn(eSCENE::STAGE_03);
}

void CScene_Stage02::enter()
{
	camFadeIn(0.5f); 
	camSetArea(0.f, 0.f, STG02_SIZEX, STG02_SIZEY);

	CPlayer* pPlayer = CPlayer::createNormal(fPoint(1963, 0.f));
	addObject(pPlayer, eOBJ::PLAYER);
	CGameManager::getInst()->registPlayer(pPlayer);
	CGameManager::getInst()->loadPlayerInfo(pPlayer);

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage2", L"texture\\background\\stage2_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage2", L"texture\\background\\stage2_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);

	// monster
	CMonster_Melee* pMon1 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(1495, 1710));
	addObject(pMon1, eOBJ::MONSTER);

	CMonster_Melee* pMon2 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(230, 1610));
	addObject(pMon2, eOBJ::MONSTER);

	CMonster_Melee* pMon3 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(3000, 1300));
	addObject(pMon3, eOBJ::MONSTER);

	CMonster_Melee* pMon4 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_MUSH, fPoint(3800, 1600));
	addObject(pMon2, eOBJ::MONSTER);

	CMonster_Melee* pMon5 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_MUSH, fPoint(200, 1300));
	addObject(pMon2, eOBJ::MONSTER);

	// ground
	CGround* pGrd1 = CGround::create(1444, 1430, 2378, 1580);
	addObject(pGrd1, eOBJ::GROUND);

	CGround* pGrd2 = CGround::create(500, 1470, 1254, STG02_SIZEY);
	addObject(pGrd2, eOBJ::GROUND);

	CGround* pGrd3 = CGround::create(0, 1710, 900, STG02_SIZEY);
	addObject(pGrd3, eOBJ::GROUND);

	CGround* pGrd4 = CGround::create(420, 1626, 1336, STG02_SIZEY);
	addObject(pGrd4, eOBJ::GROUND);

	CGround* pGrd5 = CGround::create(1336, 1785, STG02_SIZEX, STG02_SIZEY);
	addObject(pGrd5, eOBJ::GROUND);

	CGround* pGrd6 = CGround::create(1784, 1584, 2840, STG02_SIZEY);
	addObject(pGrd6, eOBJ::GROUND);

	CGround* pGrd7 = CGround::create(2840, 1668, STG02_SIZEX, STG02_SIZEY);
	addObject(pGrd7, eOBJ::GROUND);

	CGround* pGrd8 = CGround::create(3550, 1350, STG02_SIZEX, STG02_SIZEY);
	addObject(pGrd8, eOBJ::GROUND);

	// right top
	CGround* pRtTp1 = CGround::create(2062, 0, 2300, 1182);
	addObject(pRtTp1, eOBJ::GROUND);

	CGround* pRtTp2 = CGround::create(2300, 0, STG02_SIZEX, 1010);
	addObject(pRtTp2, eOBJ::GROUND);

	// left top
	CGround* pLfTp1 = CGround::create(0, 0, 1856, 494);
	addObject(pLfTp1, eOBJ::GROUND);

	CGround* pLfTp2 = CGround::create(0, 0, 1280, 1060);
	addObject(pLfTp2, eOBJ::GROUND);

	CGround* pLfTp3 = CGround::create(1280, 630, 1610, 1060);
	addObject(pLfTp3, eOBJ::GROUND);

	CGround* pLfTp4 = CGround::create(1610, 630 ,1856, 1182);
	addObject(pLfTp4, eOBJ::GROUND);

	// float floor
	CGround* pFloat1 = CGround::create(50, 1422, 308, 1542);
	addObject(pFloat1, eOBJ::GROUND);

	CGround* pFloat2 = CGround::create(2558, 1422, 2668, 1460);
	addObject(pFloat2, eOBJ::GROUND);

	CGround* pFloat3 = CGround::create(2884, 1390, 3062, 1433);
	addObject(pFloat3, eOBJ::GROUND);

	CGround* pFloat4 = CGround::create(3250, 1374, 3364, 1406);
	addObject(pFloat4, eOBJ::GROUND);

	// coll
	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);

	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::ATTACK, eOBJ::MONSTER);

	// cam
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);
}

void CScene_Stage02::exit()
{
	CGameManager::getInst()->savePlayerInfo();

	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
