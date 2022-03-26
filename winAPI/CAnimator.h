#pragma once

class CAnimation;
class CTexture;

class CAnimator
{
	friend class CObject;

	map<wstring, CAnimation*>	m_mapAni;		// 키값으로 애니메이션 저장
	CAnimation*		m_pCurAni;
	CObject*		m_pOwner;

	CTexture*		m_pMemTex;					// 회전 시 필요한 texture

public:
	CAnimator();
	~CAnimator();

	CObject* getOwner();

	void update();
	void render(HDC hDC, float theta = 0.f);

	void createAnimation(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint slice,
		fPoint step, float dura, UINT frmCnt, bool isRepeat = true);
	CAnimation* findAnimation(const wstring& strName);
	void play(const wstring& strName);

	void createMemTex(const wstring& texName, UINT sizeX, UINT sizeY);
	CTexture* getMemTex();
	
};