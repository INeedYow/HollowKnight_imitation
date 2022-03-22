#include "framework.h"
#include "CScene_Stage02.h"

#include "CPlayer.h"
#include "CTile.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CGround.h"

CScene_Stage02::CScene_Stage02()
{
}

CScene_Stage02::~CScene_Stage02()
{
}

void CScene_Stage02::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);

	if (KEY_HOLD('A'))
	{
		CCameraManager::getInst()->scroll(fVec2(-1, 0), 500.f);
	}
	if (KEY_HOLD('D'))
	{
		CCameraManager::getInst()->scroll(fVec2(1, 0), 500.f);
	}
	if (KEY_HOLD('W'))
	{
		CCameraManager::getInst()->scroll(fVec2(0, -1), 500.f);
	}
	if (KEY_HOLD('S'))
	{
		CCameraManager::getInst()->scroll(fVec2(0, 1), 500.f);
	}
}

void CScene_Stage02::enter()
{
	camFadeOut(0.6f);
	camFadeIn(0.6f);

	CBackGround* pBGBack = new CBackGround;
	pBGBack->load(L"BG_stage1B", L"texture\\background\\stage2_basic.bmp");
	pBGBack->setPos(fPoint(0.f, 0.f));
	pBGBack->setSize(fPoint(3840.f, 2160.f));
	addObject(pBGBack, eOBJ::BACKGROUND);

	//CObject* pPlayer = CPlayer::createNormal(fPoint(200.f, 1500.f));
	//pPlayer->setPos(fPoint(20.f, 1500.f));
	//addObject(pPlayer, eOBJ::PLAYER);

	//checkGrp(eOBJ::PLAYER, eOBJ::GROUND);
}

void CScene_Stage02::exit()
{
	deleteObjectAll();
	resetGrp();
}
