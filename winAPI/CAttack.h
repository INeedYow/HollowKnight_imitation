#pragma once
#include "CObject.h"

class CTexture;
class CObject;

// pOwner·Î ±¸ºÐ
class CAttack : public CObject
{
	eDIR	m_eDir;
	float	m_fDura;
	//UINT	m_uiDmg;

	CObject* m_pOwner;
	CTexture* m_pTex;

public:
	CAttack();
	virtual ~CAttack();
	virtual CAttack* clone();

	virtual void update();
	virtual void render(HDC hDC);
	
	void setDir(eDIR dir);
	void setDura(float dura);
	//void setDmg(UINT dmg);
	void setOwner(CObject* pOwner);
	void setTex(const wstring& strName, const wstring& strPath);

	CObject* getOwner();
	CTexture* getTex();

	void collisionEnter(CCollider* pOther);
};