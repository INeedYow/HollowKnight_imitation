#include "framework.h"
#include "CTriggerBox_Image.h"
#include "CTexture.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);

CTriggerBox_Image::CTriggerBox_Image()
{
	m_bActive = false;
	m_pTex = nullptr;

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CTriggerBox_Image::~CTriggerBox_Image()
{
}

void CTriggerBox_Image::update()
{
	if (m_bActive)
	{
		getAnimator()->update();
	}
}

void CTriggerBox_Image::render(HDC hDC)
{
	if (g_bDebug)
	{
		getCollider()->render(hDC);
	}

	if (m_bActive && nullptr != getAnimator())
	{
		//PLAY(m_strAnimName);
		getAnimator()->render(hDC);
	}
}

void CTriggerBox_Image::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
}

CTexture* CTriggerBox_Image::getTex()
{
	return m_pTex;
}

void CTriggerBox_Image::collisionEnter(CCollider* pOther)
{	// 어차피 플레이어랑만 충돌하게 할거니까 불필요한 getName등 생략
	m_bActive = true;
}

void CTriggerBox_Image::collisionExit(CCollider* pOther)
{
	m_bActive = false;
}