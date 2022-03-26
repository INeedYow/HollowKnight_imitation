#pragma once
#include "CObject.h"

class CTexture;

class CShield : public CObject
{
	CTexture* m_pTex;
	CTexture* m_pMemTex;

	CObject* m_pOwner;

	float	m_fRadius;
	float	m_fSpd;
	float	m_fTheta;
	bool	m_bRotRight;

public:
	CShield();
	CShield(fPoint pos, CObject* pOwner);
	virtual ~CShield();
	virtual CShield* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void toggleRot();

	void setRot(bool isRight);
	void setOwner(CObject* pOwner);
	void setfSpeed(float spd);
	void setRadius(float rad);
	void setTheta(float theta);
	void setTex(const wstring& strName, const wstring& strPath);
	void createMemTex(const wstring& texName, UINT sizeX, UINT sizeY);

	bool isRotRight();

	CTexture* getTex();
	float getSpeed();
	float getRadius();
	float getTheta();

	void collisionEnter(CCollider* pOther);

private:
	void calculateRad();
};

#define SHD_SIZEX			166
#define SHD_SIZEY			308


#define SHD_MEMTEX_SIZE		(UINT)(SHD_SIZEY * 1.5f)