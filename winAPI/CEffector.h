#pragma once

class CEffect;

class CEffector
{
	friend class CObject;

	map<wstring, CEffect*> m_mapEff;

	CObject*		m_pOwner;

public:
	CEffector();
	~CEffector();

	CObject* getOwner();

	void update();
	void render(HDC hDC);

	void createEffect(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint slice,
		fPoint step, float dura, UINT frmCnt);
};