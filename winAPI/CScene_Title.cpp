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
	pBG->load(L"BG_title", L"texture\\background\\bg_room.bmp");
	pBG->setPos(fPoint(0.f, 0.f));
	pBG->setSize(fPoint((float)WINSIZEX, (float)WINSIZEY));
	pBG->setName(eOBJNAME::BACKGROUND);
	addObject(pBG, eOBJ::BACKGROUND);

	CImage* pImg = new CImage;
	pImg->load(L"TextImage_title", L"texture\\image\\titleText.bmp");
	pImg->setPos(fPoint(130.f, 60.f));
	pImg->setName(eOBJNAME::IMAGE);
	addObject(pImg, eOBJ::IMAGE);

	CButtonUI_Image* pBtnStart = new CButtonUI_Image;
	pBtnStart->load(L"Btn_Start", L"texture\\image\\button_start.bmp");
	pBtnStart->setPos(fPoint(WINSIZEX / 2.f - 74.f, WINSIZEY / 2.f + 140));
	pBtnStart->setClickedCallBack(changeScene, (DWORD_PTR)eSCENE::STAGE_01, 0);
	addObject(pBtnStart, eOBJ::UI);

	CButtonUI_Image* pBtnExit = new CButtonUI_Image;
	pBtnExit->load(L"Btn_Exit", L"texture\\image\\button_exit.bmp");
	pBtnExit->setPos(fPoint(WINSIZEX / 2.f - 82.f, WINSIZEY / 2.f + 220));
	pBtnExit->setClickedCallBack(quitWindow, 0, 0);
	addObject(pBtnExit, eOBJ::UI);
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