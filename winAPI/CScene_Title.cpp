#include "framework.h"
#include "CScene_Title.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CTile.h"
#include "CTexture.h"
#include "commdlg.h"		// OPENFILENAME ����ü ����ϱ� ���ؼ�
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CBackGround.h"
#include "CImage.h"
#include "CButtonUI_Image.h"
#include "CSound.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);
void quitWindow(DWORD_PTR param1, DWORD_PTR param2);
void changeSceneWithPos(DWORD_PTR param1, DWORD_PTR param2, DWORD_PTR param3);

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::update()
{
	CScene::update();

	if (KEY_ON('4'))
		changeScn(eSCENE::STAGE_03);
}

void CScene_Title::enter()
{
	// Camera Look ����
	camSetFocusNow(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));
	camSetArea(0.f, 0.f, WINSIZEX, WINSIZEY);

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

	//CSoundManager::getInst()->addSound(L"bgm_title", L"sound\\bgm\\Title.wav", true);
	//CSoundManager::getInst()->play(L"bgm_title", 0.1f);
}

void CScene_Title::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();

	// TODO error
	//CSoundManager::getInst()->stop(L"bgm_title");
}



/////////////////// �Լ������� �Լ��� /////////////////////////

void changeScene(DWORD_PTR param1, DWORD_PTR param2)
{	// Ÿ��Ʋ���� �� ��ȯ�ϴ� ��ư UI ���� �Լ�
	changeScn((eSCENE)param1);
}

void changeSceneWithPos(DWORD_PTR param1, DWORD_PTR param2, DWORD_PTR param3)
{	// ������ ��
	changeScene((DWORD_PTR)param1, 0);
	// �� ��ȯ�� �÷��̾� ��ġ x,y�� �Է¹޾Ƽ� ���ӸŴ����� ����
	CGameManager::getInst()->savePos(fPoint((float)param2,(float)param3));
	
}

void quitWindow(DWORD_PTR param1, DWORD_PTR param2)
{
	PostQuitMessage(0);
}