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
	camFadeOut(0.6f);
	camFadeIn(0.6f);

	// Player �߰�
	CObject* pPlayer = new CPlayer;
	pPlayer->setPos(fPoint(200, 1500));
	addObject(pPlayer, eOBJ::PLAYER);

	//// Monster �߰�
	//CMonster* pMonster = new CMonster;
	//pMonster->setPos(fPoint(1100, 350));
	//addObject(pMonster, eOBJ::MONSTER);

	CBoss_Markoth* pBoss = new CBoss_Markoth;
	pBoss->setPos(fPoint(1000.f, 1200.f));
	pBoss->setSize(fPoint(300.f, 400.f));
	pBoss->getCollider()->setSize(fPoint(220.f, 320.f));
	addObject(pBoss, eOBJ::BOSS);

	//CBackGround* pBGBack = new CBackGround;
	//pBGBack->load(L"BG_stage1B", L"texture\\background\\stage1_back.bmp");
	//pBGBack->setPos(fPoint(0.f, 0.f));
	//pBGBack->setSize(fPoint(991.f, 1518.f));
	//addObject(pBGBack, eOBJ::BACKGROUND);

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

	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();
	resetGrp();
}
