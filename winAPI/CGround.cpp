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
	//if (g_bDebug) 
	//	componentRender(hDC);
	////
	//fPoint pos = getPos();
	//fPoint size = getSize();
	//Rectangle(hDC,
	//	(int)(pos.x - size.x / 2.f),
	//	(int)(pos.y + size.y / 2.f),
	//	(int)(pos.x - size.x / 2.f),
	//	(int)(pos.y + size.y / 2.f));
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
