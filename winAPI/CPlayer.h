#pragma once
#include "CObject.h"

class CTexture;
class CStatus;
class CEffector;
enum class eSTATE_PLAYER;

struct tPlayerInfo
{
	UINT		uiHP;
	UINT		uiSoul;
	UINT		uiZio;

	float		fSpdX;
	float		fSpdY;
	float		fGravity;
	int			iBottomCnt;

	float		fLandTimer;
	float		fNoDmgTimer;

	fVec2		fvKnockBackDir;
};

struct tPlayerPrevInfo
{
	fPoint		fpPrevPos;
};

class CPlayer : public CObject
{
	friend class CGameManager;

	tPlayerInfo			m_tInfo;
	tPlayerPrevInfo		m_tPrevInfo;
	UINT		m_uiCheck;			// 상태 추가정보

	CStatus*	m_pStatus;
	CTexture*	m_pTex;
	CEffector*	m_pEffector;		// 미구현 // 방법 고민 중

private:
	void createRotTester();
	void printInfo(HDC hDC);
	void checkUpdate();
	void updatePrevInfo(tPlayerPrevInfo prevInfo);		// gameMgr가 갱신해주도록(collMgr처리 이후에)
	//void addDirAndPlay(const wstring& keyWord);

public:
	CPlayer();
	~CPlayer();
	virtual CPlayer* clone();

	static CPlayer* createNormal(fPoint pos);

	void playAnim(const wstring& keyWord = L"\0");

	virtual void update();
	virtual void render(HDC hDC);

	void setStatus(CStatus* pStatus);
	void setPlayerInfo(const tPlayerInfo& info);
	
	const tPlayerInfo& getPlayerInfo();

	void setCheck(UINT chk, bool isOn);

	bool isCheck(UINT chk);
	UINT getCheck();
	CStatus* getAI();

	void createMissile();
	
	void firstSlash();
	void secondSlash();
	void upSlash();
	void downSlash();

	void collisionKeep(CCollider* pOther);
	void collisionEnter(CCollider* pOther);
	void collisionExit(CCollider* pOther);

	eDIR collDirVersusGround(CCollider* pOther);
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
	LAND,
	STUN,
	DEATH,

	// TODO
	SLASH2,

	HANG,
	HANG2JUMP,

	LOOKUP,
	LOOKDOWN,
	LOOKUP2IDLE,
	LOOKDOWN2IDLE,

	END
};

// # state
#define P_SIZEX					62
#define P_SIZEY					124
#define P_SPDX					420
#define P_SPDY					820
#define P_SPDY_DW				500
#define P_GRAV					7000
#define P_SPDY_MIN				-1600
#define P_LAND_TIMER			0.7				

#define P_JUMPHOLDMAX			0.35
#define P_FIRESOUL				30
#define P_FOCUSSOUL				33
#define P_FOCUSMAX				1.2
#define P_FIREDELAY				0.4
#define P_ATTDELAY				0.2
#define P_STUNDURA				0.4
#define P_DURA_INVIN			1.5

//
#define PSLASH_WIDTH			180
#define PSLASH_HEIGHT			120

#define PSLASH_OFFSETX			(P_SIZEX / 2 + PSLASH_WIDTH / 2)
#define PSLASH_OFFSETY			(P_SIZEY / 2 + PSLASH_HEIGHT / 2)

// 플레이어 상태 추가정보 
// (동시에 적용될 수 있는 개념은 비트로, 
// 동시에 하나만 실행되는 경우는 상태 클래스로,
// state의 종류 받아오기보다 비트연산으로 구분하는 게 좋은 듯)
#define SP_DIR					0x0001			// 좌, 우 방향
#define SP_AIR					0x0002			// 공중에 뜸
#define SP_JUMPHOLD				0x0004			// 점프 키 누르고 있는 상황
#define SP_DBJUMP				0x0008			// 더블점프 사용했는지

#define SP_GODOWN				0x0010			// 하강
#define SP_DWSLASH				0x0020			// 
#define SP_STOPANIM				0x0040
#define SP_NODMG				0x0080