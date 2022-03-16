#include "framework.h"
#include "CBackGround_Stg1.h"

CBackGround_Stg1::CBackGround_Stg1()
{
	m_pTexFront = loadTex(L"BG_Stg1F", L"texture\\background\\stage1_front.bmp");
	m_pTexBack = loadTex(L"BG_Stg1B", L"texture\\background\\stage1_back.bmp");
}

CBackGround_Stg1::~CBackGround_Stg1()
{
}

CBackGround_Stg1* CBackGround_Stg1::clone()
{
	return new CBackGround_Stg1(*this);
}

void CBackGround_Stg1::update()
{
}

void CBackGround_Stg1::render(HDC hDC)
{
}
