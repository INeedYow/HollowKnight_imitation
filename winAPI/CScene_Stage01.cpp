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
		changeScn(SCENE::TITLE);
}

void CScene_Stage01::enter()
{
	// Player 추가
	CObject* pPlayer = new CPlayer;
	pPlayer->setPos(fPoint(200, 200));
	addObject(pPlayer, OBJ::PLAYER);

	// Monster 추가
	CMonster* pMonster = new CMonster;
	pMonster->setPos(fPoint(1100, 350));
	pMonster->setCenterPos(pMonster->getPos());
	addObject(pMonster, OBJ::MONSTER);

	CTile* pTile = new CTile;
	pTile->setPos(fPoint(640.f, 600.f));
	pTile->setSize(fPoint(1000.f, 100.f));
	pTile->createCollider();
	pTile->getCollider()->setSize(fPoint(1000.f, 100.f));
	pTile->getCollider()->setShape(SHAPE::RECT);
	addObject(pTile, OBJ::TILE);

	//CBackGround* pBGBack = new CBackGround;
	//pBGBack->setName(OBJNAME::BACKGROUND);
	//pBGBack->setMove(false);
	//pBGBack->load(L"BG_stage1B", L"texture\\background\\stage1_back.bmp");
	//addObject(pBGBack, OBJ::BACKGROUND);

	/*CBackGround* pBGFront = new CBackGround;
	pBGFront->setName(OBJNAME::BACKGROUND);
	pBGFront->setMove(false);
	pBGFront->load(L"BG_stage1F", L"texture\\background\\stage1_front.bmp");
	addObject(pBGFront, OBJ::BACKGROUND);*/

	checkGrp(OBJ::PLAYER, OBJ::MONSTER);
	checkGrp(OBJ::PLAYER, OBJ::TILE);
	checkGrp(OBJ::MONSTER, OBJ::TILE);
	checkGrp(OBJ::MISSILE_PLAYER, OBJ::MONSTER);

	setTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	deleteObjectAll();
	resetGrp();
}
