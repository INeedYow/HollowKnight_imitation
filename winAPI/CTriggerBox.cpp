#include "framework.h"
#include "CTriggerBox.h"
#include "CTexture.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);

CTriggerBox::CTriggerBox()
{
	setName(eOBJNAME::TRIGGERBOX);

	m_pFunc = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;
	m_pParam3 = 0;

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CTriggerBox::~CTriggerBox()
{
}

void CTriggerBox::update()
{
}

void CTriggerBox::render(HDC hDC)
{
	if (g_bDebug)
		componentRender(hDC);
}


void CTriggerBox::collisionEnter(CCollider* pOther)
{	// 플레이어랑만 충돌하게
	
}

void CTriggerBox::collisionKeep(CCollider* pOther)
{
	m_pFunc(m_pParam1, m_pParam2, m_pParam3);
}

void CTriggerBox::collisionExit(CCollider* pOther)
{
	
}

void CTriggerBox::setCallBack(BTN_FUNC pFunc, DWORD_PTR param1, DWORD_PTR param2, DWORD_PTR param3)
{
	m_pFunc = pFunc;
	m_pParam1 = param1;
	m_pParam2 = param2;
	m_pParam3 = param3;
}
