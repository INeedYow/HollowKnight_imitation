#include "framework.h"
#include "CTriggerBox_Image.h"
#include "CTexture.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);

CTriggerBox_Image::CTriggerBox_Image()
{
	m_bActive = false;
	m_fpImgOffset = {};
	m_pTex = nullptr;
	m_strAnimName = L"";

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CTriggerBox_Image::~CTriggerBox_Image()
{
}

void CTriggerBox_Image::update()
{
}

void CTriggerBox_Image::render(HDC hDC)
{
	if (m_bActive)
	{
		componentRender(hDC);
		PLAY(m_strAnimName);
	}
}

void CTriggerBox_Image::setImageOffset(fPoint imgOffset)
{
	m_fpImgOffset = imgOffset;
}

void CTriggerBox_Image::setTex(const wstring& strName, const wstring& strPath)
{
	m_pTex = loadTex(strName, strPath);
	m_strAnimName = strName;
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