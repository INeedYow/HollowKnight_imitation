#pragma once

class CObject;

class CScene
{
	vector<CObject*> m_arrObj[(int)OBJ::SIZE];		// ���� �迭
	wstring m_strName;

	UINT m_uiTileX;
	UINT m_uiTileY;

public:
	CScene();
	virtual ~CScene();

	void setName(const wstring& strName);
	wstring getName();
	UINT	getTileX();
	UINT	getTileY();

	void addObject(CObject* pObj, OBJ objType);

	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC hDC);

	void renderTile(HDC hDC);

	virtual void enter() = 0;
	virtual void exit() = 0;

	// const ����, �ش� OBJ�� �迭.
	const vector<CObject*>& getGroupObject(OBJ type);

	void deleteObjectGroup(OBJ objGroup);			// �ش� obj�׷츸 delete
	void deleteObjectAll();							// ��ü obj delete

	void createTile(UINT xSize, UINT ySize);
	void loadTile(const wstring& strPath);
};
