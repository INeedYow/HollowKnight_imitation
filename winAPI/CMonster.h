#pragma once
#include "CObject.h"

class CAI;

struct tMonsInfo
{
	int		iHP;
	float	fSpd;
	fVec2	fvDir;
	float	fDist;					// 플레이어와 거리
	float	fTraceRange;			// trace 하는 거리
	float	fAtkRange;				// 공격 사거리

	fVec2	fvKnockBackDir;
	float	fKnockBackSpd;
	float	fKnockBackTimer;
};


class CMonster : public CObject
{
private:
	tMonsInfo	m_tInfo;
	UINT		m_uiCheck;		// 상태 비트체크용

	CTexture*	m_pTex;
	CAI*		m_pAI;

public:
	void printInfo(HDC hDC);

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* clone() = 0;

	virtual void update();
	virtual void render(HDC hDC) = 0;

	virtual void collisionEnter(CCollider* pOther){}
	virtual void collisionKeep(CCollider* pOther){}
	virtual void collisionExit(CCollider* pOther){}

	void setAI(CAI* pAI);
	void setTex(const wstring& strName, const wstring& strPath);
	void setMonsInfo(const tMonsInfo& info);
	void setCheck(UINT chk, bool isOn);

	const tMonsInfo& getMonsInfo();
	CTexture* getTex();
	CAI* getAI();
	bool isCheck(UINT chk);

	virtual void death() = 0;		// 죽었을 때 애니메이션 등 처리

	void playAnim(const wstring& keyWord);

	static CMonster* create(eOBJNAME eName, fPoint pos);
};

//
enum class eSTATE_MONS
{
	STOP,
	PATROL,
	TRACE,
	ATTACK,

	DIE,


	// boss
	IDLE,
	MOVE,
	SPAWN,
	READY,
	SKILL,
	DEATH,

	END
};

#define SM_KBTIME				0.2
#define SM_KBSPD_L				500
#define SM_KBSPD_M				700

//
#define SM_TRACE				0x0001		// 따라가는 기능이 있는 몬스터인지
#define SM_FALL					0x0002		// 떨어지는 중
#define SM_DEATH				0x0004		// setInfo에서 중복 death호출 방지용

#define SM_DIR					0x0010		
#define SM_TURN					0x0020		// 방향전환

//
#define SB_TIMER			0x00010000		// 보스 쿨타임 timer 도는 상태인지