#include "framework.h"
#include "CBackGround.h"
#include "CTexture.h"

CBackGround::CBackGround()
{
	setSize(fPoint(0.f, 0.f));
	setPos(fPoint(0.f, 0.f));

	m_pTex = nullptr;
}

CBackGround::~CBackGround()
{
}

CBackGround* CBackGround::clone()
{
	return new CBackGround(*this);
}

void CBackGround::update()
{
}

// TODO 출력 위치 이상함 
void CBackGround::render(HDC hDC)
{
	fPoint pos = getPos();
	fPoint size = getSize();
	fPoint renderPos = rendPos(pos);

	renderPos = pos + (renderPos - pos) / 10;

	BitBlt(hDC,
		0, 0,
		(int)(m_pTex->getBmpWidth()),
		(int)(m_pTex->getBmpHeight()),
		m_pTex->getDC(),
		(int)renderPos.x,
		(int)renderPos.y,
		SRCCOPY);

	wchar_t bufX[255] = {};
	wchar_t bufY[255] = {};
	wchar_t bufRendX[255] = {};
	wchar_t bufRendY[255] = {};

	swprintf_s(bufX, L"x = %d", (int)pos.x);
	swprintf_s(bufY, L"y = %d", (int)pos.y);
	swprintf_s(bufRendX, L"r_x = %d", (int)renderPos.x);
	swprintf_s(bufRendY, L"r_y = %d", (int)renderPos.y);

	pos = rendPos(pos);

	TextOutW(hDC, 100,	700, bufX, (int)wcslen(bufX));
	TextOutW(hDC, 400,	700, bufY, (int)wcslen(bufY));
	TextOutW(hDC, 600,	700, bufRendX, (int)wcslen(bufRendX));
	TextOutW(hDC, 900,	700, bufRendY, (int)wcslen(bufRendY));
}

void CBackGround::load(const wstring& strKey, const wstring& strPath)
{
	m_pTex = loadTex(strKey, strPath);
	setSize(fPoint((float)(m_pTex->getBmpWidth()), (float)(m_pTex->getBmpHeight())));
}