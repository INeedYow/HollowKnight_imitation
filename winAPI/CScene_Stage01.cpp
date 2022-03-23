#include "framework.h"
#include "CScene_Stage01.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"

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
	vector<CObject*> vecPlayer = getGroupObject(eOBJ::PLAYER);
	fPoint pos = vecPlayer[0]->getPos();

	if (pos.y >= STG01_SIZEY)
		changeScn(eSCENE::STAGE_02);

	//if (KEY_HOLD('H'))
	//{
	//	CCameraManager::getInst()->scroll(fVec2(-1, 0), 400.f);
	//}
	//if (KEY_HOLD('K'))
	//{
	//	CCameraManager::getInst()->scroll(fVec2(1, 0), 400.f);
	//}
	//if (KEY_HOLD('U'))
	//{
	//	CCameraManager::getInst()->scroll(fVec2(0, -1), 400.f);
	//}
	//if (KEY_HOLD('J'))
	//{
	//	CCameraManager::getInst()->scroll(fVec2(0, 1), 400.f);
	//}
}

void CScene_Stage01::enter()
{
	camFadeIn(0.8f);

	// Player 추가
	CObject* pPlayer = CPlayer::createNormal(fPoint(1200.f, 1430.f));
	addObject(pPlayer, eOBJ::PLAYER);
	
	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage1", L"texture\\background\\stage1_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage1", L"texture\\background\\stage1_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);

	CGround* pLeftWall = new CGround;
	pLeftWall->setPos(fPoint(-450.f, 1600.f));
	pLeftWall->getCollider()->setSize(fPoint(1000.f, 1600.f));
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

	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::ATTACK, eOBJ::TILE);
	checkGrp(eOBJ::ATTACK, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::GROUND);

	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	// TODO 실패..
	camSetArea(0.f, 0.f, STG01_SIZEX, STG01_SIZEY);
}

void CScene_Stage01::exit()
{
	// TODO 플레이어 캐릭터 등 모두 delete하면 안 될듯
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.8f);
	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
}
