#include "framework.h"
#include "CEventManager.h"
#include "CObject.h"
#include "CScene.h"
#include "CStatus.h"
#include "CAI.h"

CEventManager::CEventManager()
{

}
CEventManager::~CEventManager()
{

}

void CEventManager::execute(const tEvent& _event)
{	// 이벤트 종류에 따라 처리 ( Param 형변환 주의, Param들 내용 주석으로 남길 것)
	switch (_event.eEvent)
	{
	case eEvent::CREATEOBJ:		// 현재 씬에 오브젝트 타입에 맞게 추가해주면 될 듯
		// lParam : obj ptr
		// wParam : obj eGroup (GROUP_OBJECT) / (OBJ)
	{
		CObject* pObj = (CObject*)_event.lParam;
		eOBJ eGroup = (eOBJ)_event.wParam;

		CSceneManager::getInst()->getCurScene()->addObject(pObj, eGroup);
	}
	break;

	case eEvent::DELETEOBJ:		// 바로 지우면 충돌 해제 등의 처리가 이루어지지 않음 -> 1프레임 유예함
		// lParam : obj ptr
			// obj를 삭제 대기열 벡터에 추가
			// 지우는 작업은 다음 프레임 update에서
	{
		CObject* pObj = (CObject*)_event.lParam;
		if (pObj->isDead())						// 다중 충돌 시 중복 push_back 방지
			return;
		pObj->setDead();
		m_vecDead.push_back(pObj);
	}
	break;

	case eEvent::SCENECHANGE:
		// lParam : scn eGroup (GROUP_SCENE) / (SCENE)
	{
		CUIManager::getInst()->setFocusUI(nullptr);				// 씬전환 시 포커스 해제
		CSceneManager::getInst()->sceneChange((eSCENE)_event.lParam);
	}
	break;

	case eEvent::CHANGE_MY_STATE:
		// lParam : CStatus
		// wParam : next state
	{
		CStatus* pSta = (CStatus*)_event.lParam;
		eSTATE_PLAYER nextState = (eSTATE_PLAYER)_event.wParam;
		pSta->changeState(nextState);
	}
	break;

	case eEvent::CHANGE_MONS_STATE:
		// lParam : CAI
		// wParam : next state
	{
		CAI* pAI = (CAI*)_event.lParam;
		eSTATE_MONS nextState = (eSTATE_MONS)_event.wParam;
		pAI->changeState(nextState);
	}
	break;

	}
}

void CEventManager::update()
{
	// 전 프레임 집행유예 처리 (순서 주의)
	for (int i = 0; i < m_vecDead.size(); i++)
		delete m_vecDead[i];

	m_vecDead.clear();

	// 전 프레임동안 추가된 이벤트들 처리
	for (int i = 0; i < m_vecEvent.size(); i++)
		execute(m_vecEvent[i]);

	m_vecEvent.clear();
}

void CEventManager::eventCreateObject(CObject* pObj, eOBJ eGroup)
{
	tEvent newEvent = {};
	newEvent.eEvent = eEvent::CREATEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;				// 형변환
	newEvent.wParam = (DWORD_PTR)eGroup;

	addEvent(newEvent);
}

void CEventManager::eventDeleteObject(CObject* pObj)
{
	tEvent newEvent = {};
	newEvent.eEvent = eEvent::DELETEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;

	addEvent(newEvent);
}

void CEventManager::eventChangeScene(eSCENE eScn)
{
	tEvent newEvent = {};
	newEvent.eEvent = eEvent::SCENECHANGE;
	newEvent.lParam = (DWORD_PTR)eScn;

	addEvent(newEvent);
}

void CEventManager::eventChangeMyState(CStatus* status, eSTATE_PLAYER state)
{
	tEvent newEvent = {};
	newEvent.eEvent = eEvent::CHANGE_MY_STATE;
	newEvent.lParam = (DWORD_PTR)status;
	newEvent.wParam = (DWORD_PTR)state;

	CEventManager::getInst()->addEvent(newEvent);
}

void CEventManager::eventChangeMonsState(CAI* ai, eSTATE_MONS state)
{
	tEvent newEvent = {};
	newEvent.eEvent = eEvent::CHANGE_MONS_STATE;
	newEvent.lParam = (DWORD_PTR)ai;
	newEvent.wParam = (DWORD_PTR)state;

	CEventManager::getInst()->addEvent(newEvent);
}

void CEventManager::addEvent(const tEvent& _event)
{
	m_vecEvent.push_back(_event);
}
