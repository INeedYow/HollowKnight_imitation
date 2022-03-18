#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
//#include "CMonster.h"
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
	camFadeOut(0.9f);
	camFadeIn(0.9f);

	// Player 추가
	CObject* pPlayer = new CPlayer;
	pPlayer->setPos(fPoint(200, 3000));
	addObject(pPlayer, eOBJ::PLAYER);

	//// Monster 추가
	//CMonster* pMonster = new CMonster;
	//pMonster->setPos(fPoint(1100, 350));
	//addObject(pMonster, eOBJ::MONSTER);

	CBoss_Markoth* pBoss = new CBoss_Markoth;
	pBoss->setPos(fPoint(1000.f, 2800.f));
	pBoss->setSize(fPoint(300.f, 400.f));
	pBoss->getCollider()->setSize(fPoint(220.f, 320.f));
	addObject(pBoss, eOBJ::BOSS);

	CBackGround* pBGBack = new CBackGround;
	pBGBack->load(L"BG_stage1B", L"texture\\background\\stage1_back.bmp");
	addObject(pBGBack, eOBJ::BACKGROUND);

	/*CBackGround* pBGFront = new CBackGround;
	pBGFront->setName(OBJNAME::BACKGROUND);
	pBGFront->setMove(false);
	pBGFront->load(L"BG_stage1F", L"texture\\background\\stage1_front.bmp");
	addObject(pBGFront, OBJ::BACKGROUND);*/

	g_bDebug = true;

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::BOSS);
	checkGrp(eOBJ::ATTACK, eOBJ::BOSS);

	camSetTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();
	resetGrp();
}
