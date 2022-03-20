#include "framework.h"
#include "CEffector.h"

CEffector::CEffector()
{
}

CEffector::~CEffector()
{
}

CObject* CEffector::getOwner()
{
    return nullptr;
}

void CEffector::update()
{
}

void CEffector::render(HDC hDC)
{
}

void CEffector::createEffect(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint slice, fPoint step, float dura, UINT frmCnt)
{
}
