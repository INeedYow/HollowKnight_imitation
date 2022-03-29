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

	// 씬 전환
	if (gameGetPlayer()->getPos().y >= STG01_SIZEY - 40)
		changeScn(eSCENE::STAGE_02);

	if (KEY_ON('M'))
	{
		if (m_bBGM)
		{
			CSoundManager::getInst()->play(L"bgm_stg1", 0.1f);
			m_bBGM = !m_bBGM;
		}
		else
		{
			CSoundManager::getInst()->stop(L"bgm_stg1");
			m_bBGM = !m_bBGM;
		}
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

	if (CGameManager::getInst()->getPlayer() == nullptr)		
	{	// 처음 nullptr일 땐 생성하고 등록만
		CGameManager::getInst()->registPlayer(pPlayer);
	}
	else
	{	// 저장해둔 정보 입력
		CGameManager::getInst()->registPlayer(pPlayer);
		CGameManager::getInst()->loadPlayerInfo(pPlayer);		
	}

	//test
	/////////////////////////////////////////////////////////
	//CSpear* pSpear = new CSpear;
	//pSpear->setPos(fPoint(1200.f, 1200.f));
	//pSpear->setName(eOBJNAME::MISSILE_MONSTER);
	//pSpear->setMaxSpd(1.f);
	//pSpear->getCollider()->setSize(fPoint(60.f, 60.f));
	//pSpear->setTex(L"Spear_Boss", L"texture\\boss\\boss_spearBig.bmp");
	//pSpear->createAnim(L"Spear_normal", pSpear->getTex(),
	//	fPoint(0.f, 0.f), fPoint(400.f, 91.f), fPoint(0.f, 0.f), 1.f, 1, false);
	//pSpear->getAnimator()->play(L"Spear_normal");

	//createObj(pSpear, eOBJ::MISSILE_MONSTER);
	/////////////////////////////////////////////////////////

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage1", L"texture\\background\\stage1_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage1", L"texture\\background\\stage1_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);

	CHUD_HP* pHP = new CHUD_HP;
	addObject(pHP, eOBJ::HUD);

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
	//CGameManager::getInst()->savePlayerInfo();

	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	CSoundManager::getInst()->stop(L"bgm_stg1");
}
