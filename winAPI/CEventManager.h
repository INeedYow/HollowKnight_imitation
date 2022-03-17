#pragma once

class CObject;

struct tEvent
{
	eEvent		eEvent;
	DWORD_PTR	lParam;		// �̺�Ʈ ������ ���� �ʿ��� �Ķ���� �ٸ��� ������
	DWORD_PTR	wParam;			// DWORD_PTR(�������ڷ���)���� ���� �� ����� �� ���� �ڷ������� ����ȯ
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
	//void init();				// init()������ ���� �ʿ����

	void update();

	void eventCreateObject(CObject* pObj, eOBJ group);
	void eventDeleteObject(CObject* pObj);
	void eventChangeScene(eSCENE scn);
};

// �� ������ ���� �߻��� �̺�Ʈ(������Ʈ ����, ����, ����ȯ ��)�� 
// ������ ������ �ƴ϶� �� �������� ������ ���� ������ ���� ó��
	// ������ ����ȭ