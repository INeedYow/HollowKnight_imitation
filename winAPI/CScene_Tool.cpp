#include "framework.h"
#include "CScene_Tool.h"
#include "resource.h"		// CreateDialog() 함수가 IDD_TILEBOX를 알기 위해 필요
#include "CTile.h"

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


CScene_Tool::CScene_Tool()
{
	m_hWnd = 0;
	m_uiIndex = 0;
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	if (KEY_ON(VK_TAB))
		changeScn(SCENE::TITLE);

}

void CScene_Tool::enter()
{

	createTile(5, 5);

	setFocus(fPoint(WINSIZEX / 2.f, WINSIZEY / 2.f));

	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWinProc);

	ShowWindow(m_hWnd, SW_SHOW);
}

void CScene_Tool::exit()
{
	EndDialog(m_hWnd, IDOK);
}

void CScene_Tool::setIndex(UINT idx)
{
	m_uiIndex = idx;
}

void CScene_Tool::setTileIndex()
{
	if (KEY_ON(VK_LBUTTON))
	{
		fPoint mPos = mousePos();
		mPos = realPos(mPos);
	}
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->getCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->deleteObjectGroup(OBJ::TILE);
			pToolScene->createTile(x, y);
		}
		else if (LOWORD(wParam) == IDC_BUTTON_TILE)
		{
			int index = GetDlgItemInt(hDlg, IDC_EDIT_TILE, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->getCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->setIndex(index);
		}
		break;
	}
	return (INT_PTR)FALSE;
}