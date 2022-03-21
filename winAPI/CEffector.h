#pragma once

class CEffect;

class CEffector
{
	friend class CObject;

	map<wstring, CEffect*> m_mapEff;	// ����
	list<CEffect*>	m_listEff;			// ���� ��� ��

	CObject*		m_pOwner;

public:
	CEffector();
	~CEffector();

	CObject* getOwner();

	void update();
	void render(HDC hDC);

	void createEffect(const wstring& strName, CTexture* pTex);
	CEffect* findEffect(const wstring& strName);
	void show(const wstring& strName);
};