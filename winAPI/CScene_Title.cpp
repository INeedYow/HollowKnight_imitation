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
#include "CBackGround_Title.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);

CScene_Title::CScene_Title()
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::update()
{
	CScene::update();

	if (KEY_ON(VK_TAB))
	{
		changeScn(GROUP_SCENE::TOOL);
	}

	if (KEY_ON(VK_LBUTTON))
	{
		fPoint fptLookAt = realPos(mousePos());
		CCameraManager::getInst()->setFocus(fptLookAt);
	}
}

void CScene_Title::enter()
{

	// Camera Look ����
	setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	CUI* pPanelUI = new CPanelUI();
	pPanelUI->setSize(fPoint(360.f, 150.f));
	pPanelUI->setPos(fPoint(WINSIZEX / 2.f - 180.f, WINSIZEY / 2.f));		// UI�� ī�޶��� ��ġ�� ������� ���� ��ǥ�� ���� ����
	addObject(pPanelUI, OBJ::UI);

	CButtonUI* pBtnStart = new CButtonUI();
	pBtnStart->setSize(fPoint(150.f, 30.f));
	pBtnStart->setPos(fPoint(90.f, 20.f));
	pBtnStart->setClickedCallBack(changeScene, (DWORD_PTR)SCENE::STAGE_01, 0);
	pPanelUI->addChild(pBtnStart);

	CButtonUI* pBtnTool = new CButtonUI();
	pBtnTool->setSize(fPoint(150.f, 30.f));
	pBtnTool->setPos(fPoint(90.f, 60.f));
	pBtnTool->setClickedCallBack(changeScene, (DWORD_PTR)SCENE::TOOL, 0);
	pPanelUI->addChild(pBtnTool);

	CButtonUI* pBtnExit = new CButtonUI();
	pBtnExit->setSize(fPoint(150.f, 30.f));
	pBtnExit->setPos(fPoint(90.f, 100.f));
	pBtnExit->setClickedCallBack(changeScene, (DWORD_PTR)SCENE::TITLE, 0);
	pPanelUI->addChild(pBtnExit);

	//CBackGround_Title* pBGTitle = new CBackGround_Title();
	//addObject(pBGTitle, OBJ::BACKGROUND);

}

void CScene_Title::exit()
{
	deleteObjectAll();

	CCollisionManager::getInst()->resetGroup();
}


void changeScene(DWORD_PTR param1, DWORD_PTR param2)
{
	changeScn((SCENE)param1);
}