#include "framework.h"
#include "CScene_Title.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTile.h"
#include "CTexture.h"
#include "commdlg.h"		// OPENFILENAME 구조체 사용하기 위해서
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CBackGround.h"
#include "CImage.h"
#include "CButtonUI_Image.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);
void quitWindow(DWORD_PTR param1, DWORD_PTR param2);

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::enter()
{
	// Camera Look 지정
	camSetFocusNow(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	CBackGround* pBG = new CBackGround;
	pBG->load(L"BG_title", L"texture\\background\\BG_title3.bmp");
	pBG->setPos(fPoint(0.f, 0.f));
	pBG->setSize(fPoint((float)WINSIZEX, (float)WINSIZEY));
	pBG->setName(eOBJNAME::BACKGROUND);
	addObject(pBG, eOBJ::BACKGROUND);

	CImage* pImg = new CImage;
	pImg->load(L"TextImage_title", L"texture\\image\\titleText.bmp");
	pImg->setPos(fPoint(130.f, 60.f));
	pImg->setName(eOBJNAME::IMAGE);
	addObject(pImg, eOBJ::IMAGE);

	CUI* pPanelUI = new CPanelUI();
	pPanelUI->setSize(fPoint(360.f, 150.f));
	pPanelUI->setPos(fPoint(WINSIZEX / 2.f - 180.f, WINSIZEY / 2.f + 200));		// UI는 카메라의 위치와 상관없이 절대 좌표를 통해 구현
	addObject(pPanelUI, eOBJ::UI);

	CButtonUI* pBtnStart = new CButtonUI();
	pBtnStart->setSize(fPoint(150.f, 30.f));
	pBtnStart->setPos(fPoint(90, 20.f));
	pBtnStart->setClickedCallBack(changeScene, (DWORD_PTR)eSCENE::STAGE_01, 0);
	pPanelUI->addChild(pBtnStart);

	CButtonUI* pBtnTool = new CButtonUI();
	pBtnTool->setSize(fPoint(150.f, 30.f));
	pBtnTool->setPos(fPoint(90, 60.f));
	pBtnTool->setClickedCallBack(changeScene, (DWORD_PTR)eSCENE::TOOL, 0);
	pPanelUI->addChild(pBtnTool);

	CButtonUI* pBtnExit = new CButtonUI();
	pBtnExit->setSize(fPoint(150.f, 30.f));
	pBtnExit->setPos(fPoint(90, 100.f));
	pBtnExit->setClickedCallBack(quitWindow, 0, 0);
	pPanelUI->addChild(pBtnExit);

	CButtonUI_Image* pTest = new CButtonUI_Image;
	pTest->load(L"test11", L"texture\\UI\\enemy_missile.bmp");
	pTest->setPos(fPoint(220.f, 520.f));
	pTest->setSize(fPoint(100.f, 100.f));
	pTest->setClickedCallBack(changeScene, (DWORD_PTR)eSCENE::STAGE_04, 0);
	addObject(pTest, eOBJ::UI);


}

void CScene_Title::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}


void changeScene(DWORD_PTR param1, DWORD_PTR param2)
{	// 타이틀에서 씬 전환하는 버튼 UI 연결 함수
	changeScn((eSCENE)param1);
}

void quitWindow(DWORD_PTR param1, DWORD_PTR param2)
{
	PostQuitMessage(0);
}