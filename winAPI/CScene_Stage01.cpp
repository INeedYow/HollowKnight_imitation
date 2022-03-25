#include "framework.h"
#include "CScene_Stage01.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"

#include "CMonster_Melee.h"

#define STG01_SIZEX 3840
#define STG01_SIZEY 2160

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

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_02);

	// 씬 전환
	if (gameGetPlayer()->getPos().y >= STG01_SIZEY - 50)
		changeScn(eSCENE::STAGE_02);

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

	// monster test
	CMonster_Melee* pMon1 = (CMonster_Melee*)CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(1500, 1430));
	addObject(pMon1, eOBJ::MONSTER);
	
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

	// 카메라
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	// TODO 캐릭터 정보 유지하는 법
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
