#include "framework.h"
#include "CScene_Stage03.h"

#include "CPlayer.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CMonster_Melee.h"
#include "CMonster_Fly.h"
#include "CAI.h"
#include "CGround.h"
#include "CWall.h"
#include "CWarp.h"
#include "CHUD_HP.h"
#include "CHUD_Soul.h"

#define STG03_SIZEX		3725
#define STG03_SIZEY		1700

CScene_Stage03::CScene_Stage03()
{
	m_bBGM = true;
}

CScene_Stage03::~CScene_Stage03()
{
}

void CScene_Stage03::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);

	if (gameGetPlayer()->getPos().x < 30.f)
		changeScn(eSCENE::STAGE_02);

	if (gameGetPlayer()->getPos().x > STG03_SIZEX - 30.f)
		changeScn(eSCENE::STAGE_04);

	if (KEY_ON('M'))
	{
		if (m_bBGM)
		{
			CSoundManager::getInst()->play(L"bgm_stg3", 0.1f);
		}
		else
		{
			CSoundManager::getInst()->stop(L"bgm_stg3");
		}
		m_bBGM = !m_bBGM;
	}
}

void CScene_Stage03::enter()
{
	camFadeIn(0.5f);
	camSetArea(0.f, 0.f, STG03_SIZEX, STG03_SIZEY);

	CPlayer* pPlayer = CPlayer::createNormal(fPoint(260.f, 1340.f));
	addObject(pPlayer, eOBJ::PLAYER);
	CGameManager::getInst()->registPlayer(pPlayer);
	CGameManager::getInst()->loadPlayerInfo(pPlayer);

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage3", L"texture\\background\\stage3_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage3", L"texture\\background\\stage3_front.bmp");
	pFg->setPos(fPoint(0.f, STG03_SIZEY));
	addObject(pFg, eOBJ::FRONTGROUND);

	CHUD_Soul* pSoul = new CHUD_Soul;
	addObject(pSoul, eOBJ::HUD);

	CHUD_HP* pHP = new CHUD_HP;
	addObject(pHP, eOBJ::HUD);

	// monster
	CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(2330, 1350));

	CMonster::create(eOBJNAME::MONS_MUSH, fPoint(1170, 702));
	CMonster::create(eOBJNAME::MONS_MUSH, fPoint(2770, 700));

	CMonster::create(eOBJNAME::MONS_BEE, fPoint(800, 700));
	CMonster::create(eOBJNAME::MONS_BEE, fPoint(1900, 900));
	CMonster::create(eOBJNAME::MONS_BEE, fPoint(2450, 650));


	// ground, wall
	CWall::create(-100, 0, 0, STG03_SIZEY);
	CWall::create(STG03_SIZEX, 0, STG03_SIZEX + 100, STG03_SIZEY);

	// 아래
	CGround::create(0, 1326, 220, STG03_SIZEY);
	CWall::create(0, 1346, 224, STG03_SIZEY);

	CGround::create(210, 1484, 814, STG03_SIZEY);
	CGround::create(810, 1270, 1248, STG03_SIZEY);
	CWall::create(806, 1300, 1252, STG03_SIZEY);

	CGround::create(1240, 1434, STG03_SIZEX, STG03_SIZEY);
	CGround::create(3264, 1268, STG03_SIZEX, STG03_SIZEY);
	CWall::create(3260, 1298, STG03_SIZEX, STG03_SIZEY);

	// 위
	CGround::create(0, 747, 647, 777);
	CWall::create(621, 0, 651, 767);
	CGround::create(0, 0, STG03_SIZEX, 350);
	CGround::create(1728, 0, 2150, 550);
	CWall::create(1722, 0,2156, 530);
	CWall::create(3000, 0, 3148, 882);
	CWall::create(2624, 800, 2654, 904);
	CGround::create(2630, 780, 3080, 946);
	CGround::create(3100, 770, STG03_SIZEX, 800);
	CGround::create(3594, 1000, STG03_SIZEX, 1032);
	CWall::create(3590, 700, STG03_SIZEX, 1000);

	// 공중
	CGround::create(917, 788, 1406, 890);
	CWall::create(913, 808, 1410, 870);

	CGround::create(1510, 930, 1616, 1042);
	CWall::create(1506, 950, 1620, 1022);

	CGround::create(1686, 1156, 1896, 1212);
	CWall::create(1682, 1168, 1900, 1200);

	CGround::create(2022, 990, 2130, 1102);
	CWall::create(2018, 1010, 2134, 1082);

	checkGrp(eOBJ::PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);
	checkGrp(eOBJ::MONSTER, eOBJ::WALL);

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::MONSTER, eOBJ::WALL);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::ATTACK, eOBJ::MONSTER);

	//
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	CSoundManager::getInst()->addSound(L"bgm_stg3", L"sound\\bgm\\Crossroads_Bass.wav", true);
	CSoundManager::getInst()->play(L"bgm_stg3", 0.1f);
}

void CScene_Stage03::exit()
{
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	CSoundManager::getInst()->stop(L"bgm_stg3");
}