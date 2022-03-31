#include "framework.h"
#include "CScene_Stage01.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CEffect.h"
#include "CGround.h"
#include "CWall.h"
#include "CHUD_HP.h"
#include "CHUD_Soul.h"
#include "CTriggerBox.h"

#include "CTest.h"

#define STG01_SIZEX 3840
#define STG01_SIZEY 2160

CScene_Stage01::CScene_Stage01()
{
	m_bBGM = true;
}

CScene_Stage01::~CScene_Stage01()
{
}

void CScene_Stage01::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_02);

	if (KEY_ON('M'))
	{
		if (m_bBGM)
		{
			CSoundManager::getInst()->play(L"bgm_stg1", 0.1f);
		}
		else
		{
			CSoundManager::getInst()->stop(L"bgm_stg1");
		}
		m_bBGM = !m_bBGM;
	}
}

void CScene_Stage01::enter()
{
	// 카메라
	camFadeIn(0.5f);
	camSetArea(0.f, 0.f, STG01_SIZEX, STG01_SIZEY);

	// Player 추가
	CPlayer* pPlayer = CPlayer::createNormal(fPoint(1200.f, 1430.f));
	addObject(pPlayer, eOBJ::PLAYER);

	CGameManager::getInst()->registPlayer(pPlayer);
	CGameManager::getInst()->loadPlayerInfo(pPlayer);		
	
	CTest* pTest = new CTest;
	pTest->setPos(fPoint(1350.f, 1470.f));
	addObject(pTest, eOBJ::TEST);

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage1", L"texture\\background\\stage1_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage1", L"texture\\background\\stage1_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);

	CHUD_Soul* pSoul = new CHUD_Soul;
	addObject(pSoul, eOBJ::HUD);

	CHUD_HP* pHP = new CHUD_HP;
	addObject(pHP, eOBJ::HUD);

	CTriggerBox* pTrg = new CTriggerBox;
	pTrg->setPos(fPoint(3580, STG01_SIZEY - 200.f));
	pTrg->getCollider()->setSize(fPoint(400.f, 100.f));
	pTrg->setCallBack(changeSceneWithPos,(DWORD_PTR)eSCENE::STAGE_02, 1963.f, 10.f);
	addObject(pTrg, eOBJ::TRIGGERBOX);

	// ground, wall
	CWall::create(-100, 0, 0, STG01_SIZEY);
	CWall::create(STG01_SIZEX, 0, STG01_SIZEX + 100, STG01_SIZEY);
	CGround::create(0, -30, STG01_SIZEX, 0);

	CGround::create(0, 1548, 2838, STG01_SIZEY);
	CWall::create(2806, 1580, 2838, 1612);
	CGround::create(0, 1590, 3010, STG01_SIZEY);
	CWall::create(2978, 1622, 3010, 1654);
	CGround::create(0, 1632, 3186, STG01_SIZEY);
	CWall::create(3154, 1664, 3186, 1696);
	CGround::create(0, 1674, 3500, 1706);
	CWall::create(3468, 1706, 3500, STG01_SIZEY);
	CGround::create(3670, 1674, STG01_SIZEX, 1706);
	CWall::create(3670, 1706, STG01_SIZEX, STG01_SIZEY);

	g_bDebug = true;


	// 충돌 체크
	checkGrp(eOBJ::PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::PLAYER, eOBJ::TEST);
	checkGrp(eOBJ::PLAYER, eOBJ::TRIGGERBOX);

	checkGrp(eOBJ::ATTACK, eOBJ::WALL);
	checkGrp(eOBJ::ATTACK, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::GROUND);

	// 카메라
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	CSoundManager::getInst()->addSound(L"bgm_stg1", L"sound\\bgm\\Dirtmouth1.wav", true);
	CSoundManager::getInst()->play(L"bgm_stg1", 0.1f);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	CSoundManager::getInst()->stop(L"bgm_stg1");
}