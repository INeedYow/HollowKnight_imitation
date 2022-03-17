#include "framework.h"
#include "CEventManager.h"
#include "CObject.h"
#include "CScene.h"

CEventManager::CEventManager()
{

}
CEventManager::~CEventManager()
{

}

void CEventManager::execute(const tEvent& _event)
{	// �̺�Ʈ ������ ���� ó�� ( Param ����ȯ ����, Param�� ���� �ּ����� ���� ��)
	switch (_event.eEvent)
	{
	case eEvent::CREATEOBJ:		// ���� ���� ������Ʈ Ÿ�Կ� �°� �߰����ָ� �� ��
		// lParam : obj ptr
		// wParam : obj eGroup (GROUP_OBJECT) / (OBJ)
	{
		CObject* pObj = (CObject*)_event.lParam;
		eOBJ eGroup = (eOBJ)_event.wParam;

		CSceneManager::getInst()->getCurScene()->addObject(pObj, eGroup);
	}
	break;

	case eEvent::DELETEOBJ:		// �ٷ� ����� �浹 ���� ���� ó���� �̷������ ���� -> 1������ ������
		// lParam : obj ptr
			// obj�� ���� ��⿭ ���Ϳ� �߰�
			// ����� �۾��� ���� ������ update����
	{
		CObject* pObj = (CObject*)_event.lParam;
		if (pObj->isDead())						// ���� �浹 �� �ߺ� push_back ����
			return;
		pObj->setDead();
		m_vecDead.push_back(pObj);
	}
	break;

	case eEvent::SCENECHANGE:
		// lParam : scn eGroup (GROUP_SCENE) / (SCENE)
	{
		CUIManager::getInst()->setFocusUI(nullptr);				// ����ȯ �� ��Ŀ�� ����
		CSceneManager::getInst()->sceneChange((eSCENE)_event.lParam);
	}
	break;

	}
}

void CEventManager::update()
{
	// �� ������ �������� ó�� (���� ����)
	for (int i = 0; i < m_vecDead.size(); i++)
		delete m_vecDead[i];

	m_vecDead.clear();

	// �� �����ӵ��� �߰��� �̺�Ʈ�� ó��
	for (int i = 0; i < m_vecEvent.size(); i++)
		execute(m_vecEvent[i]);

	m_vecEvent.clear();
}

void CEventManager::eventCreateObject(CObject* pObj, eOBJ eGroup)
{
	tEvent newEvent = {};
	newEvent.eEvent = eEvent::CREATEOBJ;
	newEvent.lParam = (DWORD_PTR)pObj;				// ����ȯ
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

void CEventManager::addEvent(const tEvent& _event)
{
	m_vecEvent.push_back(_event);
}
