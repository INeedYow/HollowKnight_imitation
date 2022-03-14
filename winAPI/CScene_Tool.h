#pragma once
#include "CScene.h"
class CScene_Tool :public CScene
{
	HWND	m_hWnd;
	UINT	m_uiIndex;

	float	m_fSpd;		// ����Ű�� ȭ�� �̵��ϸ� Ÿ�� �۾��� �� �ֵ��� �Ϸ���

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

