#pragma once
#include "CObject.h"

class CTexture;
class CAI;
enum class eSTATE_PLAYER;

struct tPlayerInfo
{
	UINT		uiHP;
	UINT		uiSoul;
	UINT		uiZio;

	float		fSpdX;
	float		fSpdY;
	float		fGravity;

	float		fNoDmgTimer;

	int			iBottomCnt;

	fVec2		fvKnockBackDir;
	//float		fKnockBackSpd;
};

struct tPrevInfo
{
	fPoint	fpPrevPos;
	UINT	uiPrevHP;
};

class CPlayer : public CObject
{
	tPlayerInfo m_tInfo;
	tPrevInfo	m_tPrevInfo;

	UINT		m_uiCheck;			// 상태 추가정보

	CAI*		m_pAI;
	CTexture*	m_pTex;

private:
	//void renewPrevInfo(fPoint pos);
	void createRotTester();
	void printInfo(HDC hDC);
	void checkUpdate();
	//void addDirAndPlay(const wstring& keyWord);

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* clone();

	static CPlayer* createNormal(fPoint pos);

	void playAnim(const wstring& keyWord = L"\0");

	virtual void update();
	virtual void render(HDC hDC);

	void setAI(CAI* ai);
	void setPlayerInfo(const tPlayerInfo& info);
	
	const tPlayerInfo& getPlayerInfo();

	void setCheck(UINT chk, bool isOn);

	bool isCheck(UINT chk);
	UINT getCheck();

	void createMissile();
	// slash들 함수포인터로 묶을 수 있지 않을까
	void firstSlash();
	void secondSlash();
	void upSlash();
	void downSlash();

	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);
};

enum class eSTATE_PLAYER
{
	IDLE,
	RUN,
	JUMP,
	DOUBLEJUMP,
	FALL,
	SLASH1,
	UPSLASH,
	DOWNSLASH,
	FIRE,
	FOCUS,
	DASH,
	DASH2IDLE,
	STUN,
	DEATH,

	// TODO
	SLASH2,
	HANG,

	LOOKUP,
	LOOKDOWN,

	END
};

// # state
#define P_SIZEX					64
#define P_SIZEY					128
#define P_SPDX					180
#define P_SPDY					500
#define P_GRAV					2800
#define P_GRAVMAX				(P_GRAV * 3)
#define P_JUMPHOLDMAX			0.35
#define P_FIRESOUL				30
#define P_FOCUSSOUL				33
#define P_FOCUSMAX				1.2
#define P_FIREDELAY				0.5
#define P_ATTDELAY				0.4
#define P_STUNDURA				0.5
#define P_INVINTIMER_DEFAULT	1.0

//
#define PSLASH_SIZEX			120
#define PSLASH_SIZEY			120

#define PSLASH_OFFSETX			(P_SIZEX / 2 + PSLASH_SIZEX / 2)
#define PSLASH_OFFSETY			(P_SIZEY / 2 + PSLASH_SIZEY / 2)

// 플레이어 상태 추가정보 
// (동시에 적용될 수 있는 개념은 비트로, 
// 동시에 하나만 실행되는 경우는 상태 클래스로,
// state의 종류 받아오기보다 비트연산으로 구분하는 게 좋은 듯)
#define SP_DIR					0x0001			// 좌, 우 방향
#define SP_AIR					0x0002			// 공중에 뜸
#define SP_JUMPHOLD				0x0004			// 점프 키 누르고 있는 상황
#define SP_DBJUMP				0x0008

//#define SP_GODOWN				0x0010			// y값 증가 중(fall)
//#define SP_GOUP				0x0020			// y값 감소 중(jump)
#define SP_STOPANIM				0x0040
#define SP_NODMG				0x0080