#include "framework.h"
#include "CScene_Tool.h"
#include "resource.h"		// CreateDialog() �Լ��� IDD_TILEBOX�� �˱� ���� �ʿ�
#include "CTile.h"
#include "CTexture.h"
#include "commdlg.h"		// OPENFILENAME ����ü ����ϱ� ���ؼ�
#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

CScene_Tool::CScene_Tool()
{
	m_hWnd = 0;
	m_uiIndex = 0;

	m_fSpd = 350;
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::update()
{
	CScene::update();

	if (KEY_ON(VK_ESCAPE))
		changeScn(SCENE::TITLE);

	if (KEY_HOLD('A'))
	{
		CCameraManager::getInst()->scroll(fVec2(-1, 0), m_fSpd);
	}
	if (KEY_HOLD('D'))
	{
		CCameraManager::getInst()->scroll(fVec2(1, 0), m_fSpd);
	}
	if (KEY_HOLD('W'))
	{
		CCameraManager::getInst()->scroll(fVec2(0, -1), m_fSpd);
	}
	if (KEY_HOLD('S'))
	{
		CCameraManager::getInst()->scroll(fVec2(0, 1), m_fSpd);
	}

	setTileIndex();
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
	deleteObjectAll();
}

void CScene_Tool::setIndex(UINT idx)
{
	m_uiIndex = idx;
}

void CScene_Tool::setTileIndex()
{
	if (KEY_HOLD(VK_LBUTTON))
	{
		fPoint mPos = mousePos();
		mPos = realPos(mPos);

		int iTileX = (int)getTileX();
		int iTileY = (int)getTileY();

		int iX = (int)mPos.x / CTile::SIZE_TILE;
		int iY = (int)mPos.y / CTile::SIZE_TILE;

		// Ÿ�� ���� �� return
		if (mPos.x < 0.f || iTileX <= iX ||
			mPos.y < 0.f || iTileY <= iY)
			return;

		UINT index = iX + iY * iTileX;
		const vector<CObject*>& vecTile = getGroupObject(OBJ::TILE);
		((CTile*)vecTile[index])->setImageIndex(m_uiIndex);
	}
}

void CScene_Tool::saveTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = getTileX();
	UINT yCount = getTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// ��� Ÿ���� �ڱ� �ε����� ���Ͽ� �����ϰ�
	const vector<CObject*>& vecTile = getGroupObject(OBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
		((CTile*)vecTile[i])->save(pFile);

	fclose(pFile);

}

void CScene_Tool::saveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);					// ����ü ������.
	ofn.hwndOwner = hWnd;									// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;									// ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName);							// lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";			// ���� ����
	ofn.nFilterIndex = 0;									// �⺻ ���� ����. (0�� all)
	ofn.lpstrFileTitle = nullptr;							// Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0;									// Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = CPathManager::getInst()->getContentPath();
	strTileFolder += L"content\\map\\";
	ofn.lpstrInitialDir = strTileFolder.c_str();			// �ʱ���. (Ÿ�� ���� ���)
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;		// ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		saveTile(szName);
	}
}

void CScene_Tool::loadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; 
	ofn.nMaxFile = sizeof(szName); 
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";
	ofn.nFilterIndex = 0; 
	ofn.lpstrFileTitle = nullptr; 
	ofn.nMaxFileTitle = 0;
	wstring strTileFolder = CPathManager::getInst()->getContentPath();
	strTileFolder += L"content\\map\\";
	ofn.lpstrInitialDir = strTileFolder.c_str(); 
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; 

	if (GetOpenFileName(&ofn))
	{
		loadTile(szName);
	}
}

INT_PTR CALLBACK TileWinProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{	// �����ϱ�
			CScene* pCurScene = CSceneManager::getInst()->getCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->saveTileData();
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{	// �ҷ�����
			CScene* pCurScene = CSceneManager::getInst()->getCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->loadTileData();
		}
		else if (LOWORD(wParam) == IDC_BUTTON_SIZE)
		{	// �Է��� x,y ũ���� Ÿ�� ����
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->getCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->deleteObjectGroup(OBJ::TILE);
			pToolScene->createTile(x, y);
		}
		else if (LOWORD(wParam) == IDC_BUTTON_TILE)
		{	// ������ �ε����� Ÿ�� ����
			int index = GetDlgItemInt(hDlg, IDC_EDIT_TILE, nullptr, false);

			CScene* pCurScene = CSceneManager::getInst()->getCurScene();

			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			// Ÿ�� �̸����� ���
			CTexture* pTex = findTex(L"Tile");

			UINT iWidth = pTex->getBmpWidth();
			UINT iHeight = pTex->getBmpHeight();

			UINT iMaxX = iWidth / CTile::SIZE_TILE;
			UINT iMaxY = iHeight / CTile::SIZE_TILE;

			UINT iCurX = (index % iMaxX);
			UINT iCurY = (index / iMaxX) % iMaxY;

			BitBlt(GetDC(hDlg),
				(int)(150),
				(int)(150),
				(int)(CTile::SIZE_TILE),
				(int)(CTile::SIZE_TILE),
				pTex->getDC(),
				(int)(iCurX * CTile::SIZE_TILE),
				(int)(iCurY * CTile::SIZE_TILE),
				SRCCOPY);

			pToolScene->setIndex(index);
		}
		break;
	}
	return (INT_PTR)FALSE;
}
