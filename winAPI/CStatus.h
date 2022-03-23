#pragma once

class CPlayer;
class CState_Player;
enum class eSTATE_PLAYER;

class CStatus
{
	friend class CPlayer;

	map<eSTATE_PLAYER, CState_Player*> m_mapState;
	CPlayer*		m_pOwner;
	CState_Player*	m_pCurState;

public:
	CStatus();
	~CStatus();

	void update(UINT& chk);

	CPlayer* getOwner();

	CState_Player* findState(eSTATE_PLAYER state);
	CState_Player* getCurState();

	void setCurState(eSTATE_PLAYER state);

	void addState(CState_Player* pState);				// map¿¡ Ãß°¡
	void changeState(eSTATE_PLAYER nextState);
};

