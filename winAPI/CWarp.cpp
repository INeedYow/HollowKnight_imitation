#include "framework.h"
#include "CWarp.h"
#include "CTexture.h"

void changeScene(DWORD_PTR param1, DWORD_PTR param2);

CWarp::CWarp()
{
	m_bActive = false;
	m_fpImgOffset = {};

	m_eDestScn = eSCENE::TITLE;

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CWarp::~CWarp()
{
}

void CWarp::update()
{
}

void CWarp::render(HDC hDC)
{
	if (g_bDebug)
		componentRender(hDC);

	if (m_bActive)
	{
		fPoint pos = getPos();
		pos += m_fpImgOffset;
		pos = rendPos(pos);
		fPoint size = getSize();

		TransparentBlt(hDC,
			(int)(pos.x - size.x / 2.f),
			(int)(pos.y - size.y / 2.f),
			(int)size.x,
			(int)size.y,
			getTex()->getDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			RGB(255, 0, 255));
	}
}

void CWarp::setDestScene(eSCENE eScn)
{
	m_eDestScn = eScn;
}

void CWarp::setImageOffset(fPoint imgOffset)
{
	m_fpImgOffset = imgOffset;
}

void CWarp::collisionEnter(CCollider* pOther)
{	// 어차피 플레이어랑만 충돌하게 할거니까 불필요한 getName등 생략
	m_bActive = true;
}

void CWarp::collisionKeep(CCollider* pOther)
{
	if (KEY_ON(VK_UP))
	{
		changeScene((DWORD_PTR)m_eDestScn, 0);
	}
}

void CWarp::collisionExit(CCollider* pOther)
{
	m_bActive = false;
}