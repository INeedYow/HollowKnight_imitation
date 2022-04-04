#pragma once
#include "CTriggerBox.h"

//typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
class CTexture;

class CTriggerBox_Image : public CTriggerBox
{
	bool	m_bActive;

	CTexture*	m_pTex;

public:
	CTriggerBox_Image();
	virtual ~CTriggerBox_Image();

	virtual void update();
	virtual void render(HDC hDC);

	void setTex(const wstring& strName, const wstring& strPath);

	CTexture* getTex();

	virtual void collisionEnter(CCollider* pOther);		//keep�� ��� �Լ������� �Լ� ����ϵ��� �ϴ� �θ��Լ� ȣ��
	virtual void collisionExit(CCollider* pOther);

};