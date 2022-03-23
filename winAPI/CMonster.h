#pragma once
#include "CObject.h"

class CAI;

// TODO 플레이어 수정
struct tMonsInfo
{
	int		iHP;
	float	fSpd;
	fVec2	fvDir;
	float	fDist;					// 플레이어와 거리
	float	fTraceRange;			// trace 하는 거리

	fVec2	fvKnockBackDir;
	float	fKnockBackSpd;
	float	fKnockBackTimer;

	//tMonsInfo():
	//	iHP(0),
	//	fSpd(0.f),
	//	fvDir(0.f,0.f),
	//	fvKnockBackDir(0.f,0.f),
	//	fKnockBackSpd(0.f),
	//	fKnockBackTimer(0.f)
	//{}
	//tMonsInfo(int hp, float spd, fVec2 dir,
	//	fVec2 kbDir, float kbSpd, float kbTimer): 
	//	iHP(hp),
	//	fSpd(spd),
	//	fvDir(dir),
	//	fvKnockBackDir(kbDir),
	//	fKnockBackSpd(kbSpd),
	//	fKnockBackTimer(kbTimer)
	//{}	// 
};


class CMonster : public CObject
{
private:
	tMonsInfo	m_tInfo;

	UINT		m_uiCheck;		// 비트 연산

	CTexture*	m_pTex;

	CAI*		m_pAI;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* clone() = 0;

	virtual void update();
	virtual void render(HDC hDC) = 0;

	static CMonster* create(eOBJNAME eName, fPoint pos);

	void collisionEnter(CCollider* pOther){}
	void collisionKeep(CCollider* pOther){}
	void collisionExit(CCollider* pOther){}

	void setAI(CAI* pAI);
	void setTex(const wstring& strName, const wstring& strPath);
	void setMonsInfo(const tMonsInfo& info);
	void setCheck(UINT chk, bool isOn);

	const tMonsInfo& getMonsInfo();
	CTexture* getTex();
	bool isCheck(UINT chk);


private:
	virtual void death() = 0;		// 죽었을 때 애니메이션 등 처리
};

//
enum class eSTATE_MONS
{
	STOP,
	PATROL,
	TRACE,
	ATTACK,


	END
};

//
#define SM_DIR				0x0001
#define SM_AIR				0x0002
#define SM_TRACE			0x0004		// 따라가는 기능이 있는 몬스터인지