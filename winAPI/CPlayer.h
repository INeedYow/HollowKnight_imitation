#pragma once
#include "CObject.h"

class CTexture;
class CStatus;
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
	float		fSlashTimer;

	fVec2		fvKnockBackDir;
	float		fKnockBackTimer;
	float		fKnockBackSpd;
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
	UINT		m_uiCheck;			// ���� �߰�����

	CStatus*	m_pStatus;
	CTexture*	m_pTex;

private:
	void printInfo(HDC hDC);
	void checkUpdate();
	void updatePrevInfo(tPlayerPrevInfo prevInfo);		// gameMgr�� �������ֵ���(collMgró�� ���Ŀ�)

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
	
	void slash();
	void upSlash();
	void downSlash();

	virtual void collisionKeep(CCollider* pOther);
	virtual void collisionEnter(CCollider* pOther);
	virtual void collisionExit(CCollider* pOther);
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

	HANG,
	HANG2JUMP,

	LOOKUP,
	LOOKDOWN,
	LOOKUP2IDLE,
	LOOKDOWN2IDLE,

	END
};

// # state
#define P_HPMAX					5
#define P_SIZEX					62
#define P_SIZEY					124
#define P_SPDX					420
#define P_SPDY					820
#define P_SPDY_DW				410
#define P_GRAV					7000
#define P_SPDY_MIN				-1600
#define P_LAND_TIMER			0.7f				
#define P_KB_TIMER				0.2f
#define P_KB_SPD				100

#define P_JUMPHOLDMAX			0.35f
#define P_FIRESOUL				30
#define P_FOCUSSOUL				33
#define P_FOCUSMAX				1.2f
#define P_FIREDELAY				0.4f
#define P_ATTDELAY				0.2f
#define P_STUNDURA				0.4f
#define P_DURA_INVIN			1.5f

//
#define PSLASH_WIDTH			180
#define PSLASH_HEIGHT			120

#define PSLASH_OFFSETX			(P_SIZEX / 2 + PSLASH_WIDTH / 2)
#define PSLASH_OFFSETY			(P_SIZEY / 2 + PSLASH_HEIGHT / 2)

// �÷��̾� ���� �߰����� 
// (���ÿ� ����� �� �ִ� ������ ��Ʈ��, 
// ���ÿ� �ϳ��� ����Ǵ� ���� ���� Ŭ������,
// state�� ���� �޾ƿ��⺸�� ��Ʈ�������� �����ϴ� �� ���� ��)
#define SP_DIR					0x0001			// ��, �� ����
#define SP_AIR					0x0002			// ���߿� ��
#define SP_GODOWN				0x0004			// �ϰ�
#define SP_JUMPHOLD				0x0008			// ���� Ű ������ �ִ� ��Ȳ

#define SP_DBJUMP				0x0010			// �������� ����ߴ���
#define SP_DWSLASH				0x0020			// �ٿ����
#define SP_DASH					0x0040			// �뽬
#define SP_STOPANIM				0x0080

#define SP_NODMG				0x0100
#define SP_DEATH				0x0200