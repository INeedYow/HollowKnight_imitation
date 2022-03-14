#pragma once
#include "CScene.h"
class CScene_Tool :public CScene
{
	HWND	m_hWnd;
	UINT	m_uiIndex;

	float	m_fSpd;		// 방향키로 화면 이동하며 타일 작업할 수 있도록 하려고

public:
	CScene_Tool();
	virtual ~CScene_Tool();

	virtual void update();

	virtual void enter();
	virtual void exit();

	void setIndex(UINT idx);
	void setTileIndex();

	void saveTile(const wstring& strPath);
	void saveTileData();
	void loadTileData();

};

