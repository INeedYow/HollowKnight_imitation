#pragma once
#include "CObject.h"

class CTexture;
class CObject;

class CEffect : public CObject
{
	wstring		m_strName;
	bool		m_bActive;		// 활성화 비활성화

	float		m_fDura;
	fPoint		m_fpOffset;

	CObject*	m_pFollow;		// 따라다닐 오브젝트(nullptr)이면 제자리
	CTexture*	m_pTex;

public:
	CEffect();
	virtual ~CEffect();

	void setDuration(float fDura);
	void setFollow(CObject* pFollow);
	void setEffName(const wstring& strName);
	void setOffset(fPoint offset);
	void setActive(bool isAct);
	void setTex(CTexture* pTex);

	fPoint getOffset();
	float getDuration();
	const wstring& getEffName();
	CTexture* getTex();
	bool isActive();

	virtual void update();
	virtual void render(HDC hDC);

	void load(const wstring& strKey, const wstring& strPath);
};