#include "framework.h"
#include "CScene_Stage02.h"

#include "CPlayer.h"
#include "CMissile.h"
#include "CUI.h"
#include "CBackGround.h"
#include "CFrontGround.h"
#include "CMonster_Melee.h"
#include "CMonster_Fly.h"
#include "CAI.h"
#include "CGround.h"
#include "CWall.h"
#include "CTriggerBox.h"
#include "CTriggerBox_Image.h"
#include "CHUD_HP.h"
#include "CHUD_Soul.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CAnimation.h"

#define STG02_SIZEX 3840
#define STG02_SIZEY 2160

void waitForKeyInput(DWORD_PTR param1, DWORD_PTR param2, DWORD_PTR param3);

CScene_Stage02::CScene_Stage02()
{
	m_bBGM = true;
}

CScene_Stage02::~CScene_Stage02()
{
}

void CScene_Stage02::update()
{
	CScene::update();

	fPoint camPos = getCamPos();

	if (KEY_ON(VK_ESCAPE))
		changeScn(eSCENE::TITLE);

	if (KEY_ON('N'))
		changeScn(eSCENE::STAGE_03);

	if (gameGetPlayer()->getPos().x >= STG02_SIZEX - 30)
		changeScn(eSCENE::STAGE_03);

	if (KEY_ON('M'))
	{
		if (m_bBGM)
		{
			CSoundManager::getInst()->play(L"bgm_stg2", 0.1f);
		}
		else
		{
			CSoundManager::getInst()->stop(L"bgm_stg2");
		}
		m_bBGM = !m_bBGM;
	}
}

void CScene_Stage02::enter()
{
	//camFadeIn(0.5f); 
	camSetArea(0.f, 0.f, STG02_SIZEX, STG02_SIZEY);

	CPlayer* pPlayer = CPlayer::createNormal(fPoint(1963, 0.f));
	addObject(pPlayer, eOBJ::PLAYER);
	CGameManager::getInst()->registPlayer(pPlayer);
	CGameManager::getInst()->loadPlayerInfo(pPlayer);

	CBackGround* pBg = new CBackGround;
	pBg->load(L"BG_stage2", L"texture\\background\\stage2_back.bmp");
	pBg->setPos(fPoint(0.f, 0.f));
	addObject(pBg, eOBJ::BACKGROUND);

	CFrontGround* pFg = new CFrontGround;
	pFg->load(L"FG_stage2", L"texture\\background\\stage2_front.bmp");
	pFg->setPos(fPoint(0.f, 0.f));
	addObject(pFg, eOBJ::FRONTGROUND);

	CHUD_Soul* pSoul = new CHUD_Soul;
	addObject(pSoul, eOBJ::HUD);

	CHUD_HP* pHP = new CHUD_HP;
	addObject(pHP, eOBJ::HUD);

	// monster
	CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(1550, 1720));
	CMonster::create(eOBJNAME::MONS_BEETLE, fPoint(3000, 1310));

	CMonster::create(eOBJNAME::MONS_MUSH, fPoint(200, 1550));
	CMonster::create(eOBJNAME::MONS_MUSH, fPoint(3200, 1570));
	CMonster::create(eOBJNAME::MONS_MUSH, fPoint(3400, 1500));

	//CWarp* pWp1 = new CWarp;
	//pWp1->setDestScene(eSCENE::STAGE_01);
	//pWp1->load(L"warp_mapChange", L"texture\\image\\text_mapChange.bmp");
	//pWp1->setPos(fPoint(1958.f, 1380));
	//pWp1->getCollider()->setSize(fPoint(80.f, 80.f));
	//pWp1->setImageOffset(fPoint(0.f, -180.f));
	//addObject(pWp1, eOBJ::WARP);

	// TODO
	// 이전 맵과 다음 맵의 플레이어 진입 위치를 다르게 하려고 gameMgr에 진입점을 저장하게 하려고
	// 처음에 fPoint enterPos = fPoint(100.f, 100.f); 처럼 지역변수로 하니까 함수포인터 인자로 포인터를 줘야해서
	// &enterPos로 주니까 원본이 쓰레기값이 돼서인지 제대로 작동하지 않고 0, 0으로 이동하는 문제가 있어서
	// 어차피 주소로 넘겨주니까 동적할당을 해서 주소값을 주는 걸로 해보려고 했더니 해제하는 거 고민하다가
	// 게임 매니저가 해당 위치에 플레이어 셋해주고 해당 주소값 delete해주려 했더니 맵 진입점이 동시에 둘 이상인 경우 모두 해제가 안 되니까
	// 진입점 좌표 주소들을 vector배열로 갖고 있다가 모두 해제해주는 식으로 해야하나 했다가
	// 미리 다 만들어두지 말고 해당 씬 전환 호출 시 해당 좌표 할당하고 gameMgr는 사용한 것만 지우는 식으로 해결하려 했는데 또 안 되네
	// 아 enter 함수 끝나면 사라지니까 바로 쓰레기값 되는구나
		// pos들을 scn자체에서 관리하게 하거나 데이터 영역에 두거나 ㅇ누램ㄴ오랜ㅁㅇ래ㅑㅇㄴㄹㅇㄴ
	// 누가 이기나 보자 시작 좌표 달리하는 게 이렇게 어려울 일이었나 내가 어렵게 하고 있는 건가

	fPoint stg1enterPos = fPoint(3400.f, 1600.f);
	fPoint stg3enterPos = fPoint(100.f, 1250.f);

	CTriggerBox_Image* pTb = new CTriggerBox_Image;
	pTb->setPos(fPoint(1958.f, 1380));
	pTb->setCallBack(waitForKeyInput, (DWORD_PTR)eSCENE::STAGE_01, (DWORD_PTR)&stg1enterPos, 0);
	pTb->getCollider()->setSize(fPoint(80.f, 80.f));
	pTb->setTex(L"TextImg_map2to1", L"texture\\image\\text_mapChange.bmp");
	pTb->createAnimator();
	pTb->getAnimator()->createAnimation(L"map2to1", pTb->getTex(),
		fPoint(0,0), fPoint(120, 96), fPoint(120, 0), 0.7f, 1, false);
	pTb->getAnimator()->findAnimation(L"map2to1")->setAllOffset(fPoint(0.f, - 170.f));
	pTb->PLAY(L"map2to1");
	addObject(pTb, eOBJ::TRIGGERBOX);

	CTriggerBox* pTb2 = new CTriggerBox;
	pTb2->setPos(fPoint(STG02_SIZEX, 1233));
	pTb2->setCallBack(changeSceneWithPos, (DWORD_PTR)eSCENE::STAGE_03, (DWORD_PTR)&stg3enterPos, 0);
	pTb2->getCollider()->setSize(fPoint(80.f, 200.f));
	addObject(pTb2, eOBJ::TRIGGERBOX);

	// ground, wall
	CWall::create(-100, 0, 0, STG02_SIZEY);
	CWall::create(STG02_SIZEX, 0, STG02_SIZEX + 100, STG02_SIZEY);
	CGround::create(0, -30, STG02_SIZEX, 0);

	CWall::create(1826, 0, 1858, 1148);
	CGround::create(1608, 1148, 1854, 1180);
	CWall::create(1604, 1096, 1636, 1148);
	CGround::create(0, 1064, 1632, 1096);

	CGround::create(54, 1424, 304, 1532);
	CWall::create(50, 1456, 308, 1500);

	CGround::create(0, 1708, 416, 1740);
	CWall::create(420, 1662, 1332, STG02_SIZEY);
	CGround::create(424, 1630, 1328, STG02_SIZEY);
	CGround::create(490, 1462, 1256, 1494);
	CWall::create(486, 1494, 518, 1657);
	CWall::create(1230, 1494, 1260, 1650);
	CGround::create(1234, 1462, 1256, 1494);
	CGround::create(1336, 1790, 1996, STG02_SIZEY);
	CWall::create(1776, 1610, 2832, STG02_SIZEY);
	CGround::create(1442, 1540, 1796, 1570);
	CGround::create(1442, 1424, 2380, 1456);
	CWall::create(1438, 1456, 2384, 1540);
	CGround::create(2346, 1590, 2828, 1622);
	CGround::create(2796, 1670, STG02_SIZEX, STG02_SIZEY);
	CWall::create(3554, 1370, STG02_SIZEX, STG02_SIZEY);
	CGround::create(3558, 1336, STG02_SIZEX, 1370);

	CGround::create(2560, 1424, 2666, 1460);
	CWall::create(2556, 1440, 2670, 1445);

	CGround::create(2884, 1386, 3060, 1430);
	CWall::create(2880, 1400, 3064, 1420);

	CGround::create(3252, 1372, 3360, 1406);
	CWall::create(3248, 1382, 3364, 1396);

	CWall::create(2060, 0, 2300, 1150);
	CGround::create(2064, 1150, 2296, 1180);
	CGround::create(2300, 0, STG02_SIZEX, 1000);

	// coll
	checkGrp(eOBJ::PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::MONSTER, eOBJ::GROUND);
	checkGrp(eOBJ::MONSTER, eOBJ::WALL);

	checkGrp(eOBJ::PLAYER, eOBJ::TRIGGERBOX);
	checkGrp(eOBJ::PLAYER, eOBJ::WARP);
	checkGrp(eOBJ::PLAYER, eOBJ::MONSTER);
	checkGrp(eOBJ::PLAYER, eOBJ::MISSILE_MONSTER);

	checkGrp(eOBJ::MONSTER, eOBJ::ATTACK);

	checkGrp(eOBJ::ATTACK, eOBJ::WALL);
	checkGrp(eOBJ::ATTACK, eOBJ::GROUND);

	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::GROUND);
	checkGrp(eOBJ::MISSILE_PLAYER, eOBJ::MONSTER);

	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::WALL);
	checkGrp(eOBJ::MISSILE_MONSTER, eOBJ::GROUND);

	// cam
	camSetFocusNow(pPlayer->getPos());
	camSetTrace(pPlayer);

	CSoundManager::getInst()->addSound(L"bgm_stg2", L"sound\\bgm\\cave_wind_loop.wav", true);
	CSoundManager::getInst()->play(L"bgm_stg2", 0.1f);
}

void CScene_Stage02::exit()
{
	deleteObjectAll();
	resetGrp();

	camFadeOut(0.5f);
	camFadeIn(0.5f);

	camSetIsArea(false);
	camSetFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	//delete pStg1enterPos;
	//delete pStg3enterPos;
}

void waitForKeyInput(DWORD_PTR param1, DWORD_PTR param2, DWORD_PTR param3)
{
	if (KEY_ON(VK_UP))
	{
		changeSceneWithPos(param1, param2, param3);
	}
}