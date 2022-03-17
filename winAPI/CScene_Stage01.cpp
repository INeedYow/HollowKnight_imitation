#include "framework.h"
#include "CScene_Stage01.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"

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
	pPlayer->setPos(fPoint(200, 200));
	addObject(pPlayer, eOBJ::PLAYER);

	// Monster 추가
	CMonster* pMonster = new CMonster;
	pMonster->setPos(fPoint(1100, 350));
	pMonster->setCenterPos(pMonster->getPos());
	addObject(pMonster, eOBJ::MONSTER);

	createTile(4, 15);

	CBackGround* pBGBack = new CBackGround;
	pBGBack->setName(eOBJNAME::BACKGROUND);
	pBGBack->load(L"BG_stage1B", L"texture\\background\\stage1_back.bmp");
	addObject(pBGBack, eOBJ::BACKGROUND);

	/*CBackGround* pBGFront = new CBackGround;
	pBGFront->setName(OBJNAME::BACKGROUND);
	pBGFront->setMove(false);
	pBGFront->load(L"BG_stage1F", L"texture\\background\\stage1_front.bmp");
	addObject(pBGFront, OBJ::BACKGROUND);*/

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);

	camSetTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();
	resetGrp();
}
