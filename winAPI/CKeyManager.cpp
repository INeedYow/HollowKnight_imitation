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

// 포커스 되고 있는 윈도우창이 현재 윈도우 핸들인지 GetFocus()로 비교
void CKeyManager::update()
{
	HWND hNowFocus = GetFocus();

	if (hWnd != hNowFocus)						// 다른 윈도우 보고 있으면 키입력 X
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
		m_arrPrevKey[key] = m_arrCurKey[key];	// 지금 상태는 예전 키 상태로 넣어주고

		if (GetAsyncKeyState(key) & 0x8000)
			m_arrCurKey[key] = true;
		else
			m_arrCurKey[key] = false;
	}

	// mouse 좌표
	POINT ptPos = { };

	GetCursorPos(&ptPos);			// 모니터 좌상단 기준(전체 화면) 마우스 좌표

	ScreenToClient(hWnd, &ptPos);	// 게임 윈도우 기준 마우스 좌표

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
