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

void CGround::create(float left, float top, float right, float bottom)
{	// ÁÂÇ¥°ªÀ¸·Î ¶¥ »ý¼º
	CGround* pNewGrd = new CGround;
	pNewGrd->setPos(fPoint((left + right) * 0.5f, (top + bottom) * 0.5f));
	pNewGrd->setSize(fPoint(right - left, bottom - top));
	pNewGrd->getCollider()->setSize(fPoint(right - left, bottom - top));

	createObj(pNewGrd, eOBJ::GROUND);
}