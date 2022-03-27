#include "framework.h"
#include "CScene_Stage01.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
#include "CEffect.h"

#include "CMonster_Melee.h"
#include "CSpear.h"

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


	//// monster test
	//CMonster_Melee* pMon1 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(1500, 1430));
	//addObject(pMon1, eOBJ::MONSTER);

	//CMonster_Melee* pMon2 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_MUSH, fPoint(1800, 1430));
	//addObject(pMon2, eOBJ::MONSTER);
	
	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage1", L"texture\\background\\stage1_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage1", L"texture\\background\\stage1_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);

	// ground
	CGround* pLeftWall = CGround::create(-600, 0, 0, STG01_SIZEY);
	addObject(pLeftWall, eOBJ::GROUND);

	CGround* pGround1 = new CGround;
	pGround1->setPos(fPoint(1417.f, STG01_SIZEY));
	pGround1->getCollider()->setSize(fPoint(2834.f, 1230.f));
	addObject(pGround1, eOBJ::GROUND);

	CGround* pStair1 = new CGround;
	pStair1->setPos(fPoint(1504.f, STG01_SIZEY));
	pStair1->getCollider()->setSize(fPoint(3008.f, 1130.f));
	addObject(pStair1, eOBJ::GROUND);

	CGround* pStair2 = new CGround;
	pStair2->setPos(fPoint(1593.f, STG01_SIZEY));
	pStair2->getCollider()->setSize(fPoint(3186.f, 1040.f));
	addObject(pStair2, eOBJ::GROUND);

	CGround* pGround2 = new CGround;
	pGround2->setPos(fPoint(1747.f, STG01_SIZEY));
	pGround2->getCollider()->setSize(fPoint(3494.f, 962.f));
	addObject(pGround2, eOBJ::GROUND);

	CGround* pGround3 = new CGround;
	pGround3->setPos(fPoint(STG01_SIZEX, STG01_SIZEY));
	pGround3->getCollider()->setSize(fPoint(348.f, 962.f));
	addObject(pGround3, eOBJ::GROUND);

	CGround* pRightWall = new CGround;
	pRightWall->setPos(fPoint(STG01_SIZEX + 450, 1600.f));
	pRightWall->getCollider()->setSize(fPoint(1000.f, 1600.f));
	addObject(pRightWall, eOBJ::GROUND);

	g_bDebug = true;

	////////////////
	/*CEffect* pEff = new CEffect;
	pEff->setEffName(L"EF_dash_R");
	pEff->load(L"Effect_dash", L"texture\\effect\\effect_dash.bmp");
	pEff->setDuration(0.4f);
	pEff->setFollow(pPlayer);
	pEff->setOffset(fPoint(100.f, 0.f));
	pEff->createAnim(L"effect_dash", pEff->getTex(),
		fPoint(289, 0), fPoint(289, 146), fPoint(289, 0), 0.1f, 4, false);
	CEffectManager::getInst()->addEffect(pEff);
	pEff->PLAY(L"effect_dash");
	addObject(pEff, eOBJ::EFFECT);*/

	////////////////

	// 충돌 체크
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);

	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MONSTER, eOBJ::ATTACK);
	checkGrp(eOBJ::ATTACK, eOBJ::TILE);
	checkGrp(eOBJ::ATTACK, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);

	// 카메라
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

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
