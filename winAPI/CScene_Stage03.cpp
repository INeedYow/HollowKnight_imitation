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

#define STG03_SIZEX 3000
#define STG03_SIZEY 1689

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
			m_bBGM = !m_bBGM;
		}
		else
		{
			CSoundManager::getInst()->stop(L"bgm_stg3");
			m_bBGM = !m_bBGM;
		}
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
	pBg->load(L"BG_stage3", L"texture\\background\\stage3_test.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	/*CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage3", L"texture\\background\\stage3_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);*/

	// ground, wall
	CWall::create(0, 0, 268, STG03_SIZEY);
	CWall::create(2654, 0, STG03_SIZEX, STG03_SIZEY);

	CGround::create(0, 1492, STG03_SIZEX, STG03_SIZEY);

	CGround::create(1076, 1120, 1240, 1170);
	CWall::create(1080, 1135, 1244, 1155);

	CGround::create(1544, 864, 1764, 928);
	CWall::create(1540, 884, 1768, 908);

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