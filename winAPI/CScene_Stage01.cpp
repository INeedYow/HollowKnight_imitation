#include "framework.h"
#include "CScene_Stage01.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"
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

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_02);

	if (KEY_HOLD('H'))
	{
		CCameraManager::getInst()->scroll(fVec2(-1, 0), 400.f);
	}
	if (KEY_HOLD('K'))
	{
		CCameraManager::getInst()->scroll(fVec2(1, 0), 400.f);
	}
	if (KEY_HOLD('U'))
	{
		CCameraManager::getInst()->scroll(fVec2(0, -1), 400.f);
	}
	if (KEY_HOLD('J'))
	{
		CCameraManager::getInst()->scroll(fVec2(0, 1), 400.f);
	}

}

void CScene_Stage01::enter()
{
	camFadeOut(0.6f);
	camFadeIn(0.6f);

	// Player �߰�
	CObject* pPlayer = CPlayer::createNormal(fPoint(1200.f, 1430.f));
	addObject(pPlayer, eOBJ::PLAYER);
	
	CBackGround* pBGBack = new CBackGround;
	pBGBack->load(L"BG_stage1B", L"texture\\background\\stage0_back.bmp");
	pBGBack->setPos(fPoint(0.f, 0.f));
	//pBGBack->setSize(fPoint(STG01_SIZEX, STG01_SIZEY));	// load���� ����
	addObject(pBGBack, eOBJ::BACKGROUND);

	//CFrontGround* pBGFront = new CFrontGround;
	//pBGFront->load(L"BG_stage1F", L"texture\\background\\bossStage_back.bmp");
	//pBGFront->setPos(fPoint(0.f, 0.f));
	//pBGFront->setSize(fPoint(3000.f, 1689.f));
	//addObject(pBGFront, eOBJ::FRONTGROUND);

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

	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::BOSS);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::SHIELD);
	checkGrp(eOBJ::PLAYER, eOBJ::TILE);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);

	checkGrp(eOBJ::MONSTER, eOBJ::TILE);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::BOSS);

	checkGrp(eOBJ::ATTACK, eOBJ::BOSS);

	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);
}

void CScene_Stage01::exit()
{
	// TODO �÷��̾� ĳ���� �� ��� delete�ϸ� �� �ɵ�
	deleteObjectAll();
	resetGrp();
}
