#pragma once
class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	static const int VKEY_SIZE = 0xFF;		// VKŰ�� ����, #define���� �ص� ��

	bool	m_arrPrevKey[VKEY_SIZE];
	bool	m_arrCurKey[VKEY_SIZE];
	fPoint	m_fpCurMousePos;

public:
	void update();
	void init();

	bool isKeyHold(const int key);
	bool isKeyOn(const int key);
	bool isKeyOff(const int key);
	bool isKeyNone(const int key);

	fPoint getMousePos();
};

