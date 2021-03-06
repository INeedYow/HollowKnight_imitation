#pragma once

class CObject;
class CStatus;
class CAI;
enum class eSTATE_PLAYER;
enum class eSTATE_MONS;

struct tEvent
{
	eEvent		eEvent;
	DWORD_PTR	lParam;		// 이벤트 종류에 따라 필요한 파라미터 다르기 때문에
	DWORD_PTR	wParam;			// DWORD_PTR(포인터자료형)으로 받은 후 사용할 때 원래 자료형으로 형변환
};

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<tEvent>	 m_vecEvent;
	vector<CObject*> m_vecDead;

	void execute(const tEvent& _event);
	void addEvent(const tEvent& _event);

public:
	//void init();				// init()과정은 딱히 필요없음

	void update();

	void eventCreateObject(CObject* pObj, eOBJ group);
	void eventDeleteObject(CObject* pObj);
	void eventChangeScene(eSCENE scn);

	void eventChangeMyState(CStatus* status, eSTATE_PLAYER state);
	void eventChangeMonsState(CAI* ai, eSTATE_MONS state);
};

// 한 프레임 동안 발생한 이벤트(오브젝트 생성, 삭제, 씬전환 등)를 
// 프레임 도중이 아니라 한 프레임이 끝나고 다음 프레임 전에 처리
	// 프레임 동기화