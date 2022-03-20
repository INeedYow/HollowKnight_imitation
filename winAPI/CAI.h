#pragma once

class CPlayer;
class CState;
enum class eSTATE_PLAYER;

class CAI
{
	friend class CPlayer;

	map<eSTATE_PLAYER, CState*> m_mapState;
	CPlayer*		m_pOwner;
	CState*			m_pCurState;

public:
	CAI();
	~CAI();

	void update(UINT& chk);

	CPlayer* getOwner();

	CState* findState(eSTATE_PLAYER state);
	CState* getCurState();

	void setCurState(eSTATE_PLAYER state);

	void addState(CState* pState);				// map¿¡ Ãß°¡
	void changeState(eSTATE_PLAYER nextState);


};

