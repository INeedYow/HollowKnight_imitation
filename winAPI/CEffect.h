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
	CTexture* m_pTex;

	tEffectInfo m_tInfo;

public:
	CEffect();
	virtual ~CEffect();

	void setInfo(tEffectInfo info);

	const tEffectInfo& getInfo();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);
};