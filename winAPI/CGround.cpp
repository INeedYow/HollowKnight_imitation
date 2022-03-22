#include "framework.h"
#include "CGround.h"

CGround::CGround()
{
	setName(eOBJNAME::GROUND);
	setPos(fPoint(1.f, 1.f));
	setSize(fPoint(1.f, 1.f));

	createCollider();
	getCollider()->setShape(eSHAPE::RECT);
}

CGround::~CGround()
{
}

void CGround::update()
{
}

void CGround::render(HDC hDC)
{
	if (g_bDebug) 
		componentRender(hDC);
}

CGround* CGround::create(float left, float top, float right, float bottom)
{	// ÁÂÇ¥°ªÀ¸·Î ¶¥ »ý¼º
	CGround* pNewGrd = new CGround;
	pNewGrd->setPos(fPoint((left + right) / 2.f, (top + bottom) / 2.f));
	pNewGrd->getCollider()->setSize(fPoint(right - left, bottom - top));
	
	return pNewGrd;
}

void CGround::collisionKeep(CCollider* pOther)
{
}

void CGround::collisionEnter(CCollider* pOther)
{
}

void CGround::collisionExit(CCollider* pOther)
{
}
