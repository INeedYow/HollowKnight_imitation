#pragma once
#include "CObject.h"

class CTexture;

struct tEffectInfo
{
	float fTimer;
	float fDura;
};

class CEffect : public CObject
{
	friend class CEffector;

	CTexture* m_pTex;

	wstring		m_strName;
	tEffectInfo m_tInfo;

public:
	CEffect();
	virtual ~CEffect();

	void setInfo(tEffectInfo info);
	void setName(const wstring& strName);

	CTexture* getTex();
	const wstring& getName();
	const tEffectInfo& getInfo();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);
};