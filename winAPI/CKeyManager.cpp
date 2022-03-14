#include "framework.h"
#include "CKeyManager.h"


CKeyManager::CKeyManager()
{
	m_arrPrevKey[0] = {};
	m_arrCurKey[0]	= {};
	m_fpCurMousePos = {};
}

CKeyManager::~CKeyManager()
{
}

// ��Ŀ�� �ǰ� �ִ� ������â�� ���� ������ �ڵ����� GetFocus()�� ��
void CKeyManager::update()
{
	HWND hNowFocus = GetFocus();

	if (hWnd != hNowFocus)						// �ٸ� ������ ���� ������ Ű�Է� X
	{
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			m_arrPrevKey[key] = m_arrCurKey[key];
			m_arrCurKey[key] = false;
		}
		return;
	}

	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];	// ���� ���´� ���� Ű ���·� �־��ְ�

		if (GetAsyncKeyState(key) & 0x8000)
			m_arrCurKey[key] = true;
		else
			m_arrCurKey[key] = false;
	}

	// mouse ��ǥ
	POINT ptPos = { };

	GetCursorPos(&ptPos);			// ����� �»�� ����(��ü ȭ��) ���콺 ��ǥ

	ScreenToClient(hWnd, &ptPos);	// ���� ������ ���� ���콺 ��ǥ

	m_fpCurMousePos.x = (float)ptPos.x;
	m_fpCurMousePos.y = (float)ptPos.y;
}

void CKeyManager::init()
{
}

fPoint CKeyManager::getMousePos()
{
	return m_fpCurMousePos;
}

bool CKeyManager::isKeyHold(const int key)
{
	return (true == m_arrPrevKey[key] && true == m_arrCurKey[key]);
}

bool CKeyManager::isKeyOn(const int key)
{
	return (false == m_arrPrevKey[key] && true == m_arrCurKey[key]);
}

bool CKeyManager::isKeyOff(const int key)
{
	return (true == m_arrPrevKey[key] && false == m_arrCurKey[key]);
}

bool CKeyManager::isKeyNone(const int key)
{
	return (false == m_arrPrevKey[key] && false == m_arrCurKey[key]);
}
