#include "framework.h"
#include "CScene_Stage03.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CBoss_Markoth.h"
#include "CGround.h"
#include "CWall.h"
#include "CHUD_HP.h"
#include "CHUD_Soul.h"

#define STG03_SIZEX				3000
#define STG03_SIZEY				1689
#define STG03_FRONT_SIZEY		470

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

	CBoss_Markoth* pBoss = new CBoss_Markoth;
	pBoss->setPos(fPoint(2270.f, 1040.f));
	pBoss->getCollider()->setSize(fPoint(200.f, 310.f));
	pBoss->getCollider()->setOffset(fPoint(0.f, 20.f));
	addObject(pBoss, eOBJ::BOSS);

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage3", L"texture\\background\\stage3_back3.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage3", L"texture\\background\\stage3_front_part470.bmp");
	pFg->setPos(fPoint(0.f, STG03_SIZEY - STG03_FRONT_SIZEY));
	addObject(pFg, eOBJ::FRONTGROUND);

	CHUD_Soul* pSoul = new CHUD_Soul;
	addObject(pSoul, eOBJ::HUD);

	CHUD_HP* pHP = new CHUD_HP;
	addObject(pHP, eOBJ::HUD);

	// ground, wall
	CWall::create(0, 0, 268, STG03_SIZEY);
	CWall::create(2654, 0, STG03_SIZEX, STG03_SIZEY);

	CGround::create(0, 1492, STG03_SIZEX, STG03_SIZEY);

	// ¿ÞÂÊ ¾Æ·¡
	CGround::create(864, 1040, 1036, 1100);
	CWall::create(860, 1055, 1040, 1085);
	// Áß¾Ó ¾Æ·¡
	CGround::create(1350, 1200, 1530, 1250);
	CWall::create(1346, 1215, 1534, 1235);
	// ¿ÞÂÊ À§
	CGround::create(1080, 656, 1180, 708);
	CWall::create(1076, 671, 1184, 693);
	// Áß¾Ó À§
	CGround::create(1578, 814, 1750, 866);
	CWall::create(1574, 829, 1754, 851);
	// ¿À¸¥ÂÊ ¾Æ·¡
	CGround::create(1942, 1082, 2036, 1132);
	CWall::create(1938, 1097, 2040, 1117);

	checkGrp(eOBJ::PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);
	checkGrp(eOBJ::MONSTER, eOBJ::WALL);

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::SHIELD);
	checkGrp(eOBJ::PLAYER, eOBJ::BOSS);

	checkGrp(eOBJ::MONSTER, eOBJ::WALL);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::BOSS);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::ATTACK, eOBJ::BOSS);
	checkGrp(eOBJ::ATTACK, eOBJ::MONSTER);
	checkGrp(eOBJ::ATTACK, eOBJ::SHIELD);

	//
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);
	//camSetTrace(pBoss);
	
	CSoundManager::getInst()->addSound(L"bgm_stg3", L"sound\\bgm\\Boss_Battle.wav", true);
	CSoundManager::getInst()->play(L"bgm_stg3", 0.1f);
}

void CScene_Stage03::exit()
{
	//CGameManager::getInst()->savePlayerInfo();

	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	CSoundManager::getInst()->stop(L"bgm_stg3");
}