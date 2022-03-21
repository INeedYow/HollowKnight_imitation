#pragma once
#include "CObject.h"

class CTexture;

// missile 이름으로 구분
class CMissile : public CObject
{
private:
	fVec2 m_fvDir;
	float m_fSpeed;
	float m_fTimer;

	CTexture* m_pTex;

public:
	CMissile();
	~CMissile();
	virtual CMissile* clone();

	virtual void update();
	virtual void render(HDC hDC);

	void setDir(fVec2 vec);
	void setDir(float theta);
	void setTimer(float timer);
	void setSpeed(float spd);
	void setTex(const wstring& strName, const wstring& strPath);

	CTexture* getTex();
	float getSpeed();
	float getTimer();
	fVec2 getDir();

	void collisionEnter(CCollider* pOther);
	void collisionKeep(CCollider* pOther);
};

