#include "framework.h"
#include "CCore.h"
#include "CTexture.h"

CCore::CCore()
{
	m_hDC = 0;
	m_arrBrush[0] = {};
	m_arrPen[0] = {};
	m_arrFont[0] = {};

	m_pMemTex = nullptr;
}

CCore::~CCore()
{
	// 해당 윈도우 DC 핸들 반납
	ReleaseDC(hWnd, m_hDC);

	for (int i = 0; i < (int)eBRUSH::SIZE; i++)
	{	// hollow는 stock에서 빌려옴
		if ((int)eBRUSH::HOLLOW == i) continue;
		DeleteObject(m_arrBrush[i]);
	}
	for (int i = 0; i < (int)ePEN::SIZE; i++)
	{	// white ,, stock
		if ((int)ePEN::WHITE == i) continue;
		DeleteObject(m_arrPen[i]);
	}
	for (int i = 0; i < (int)eFONT::SIZE; i++)
	{
		DeleteObject(m_arrFont[i]);
	}
}

void CCore::update()
{
	// 동기화
	CEventManager::getInst()->update();
	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();

	CSceneManager::getInst()->update();
	CCollisionManager::getInst()->update();			//scnMgr 보다 아래
	CGameManager::getInst()->update();				//collMgr 보다 아래
	CCameraManager::getInst()->update();
	CUIManager::getInst()->update();
	CSoundManager::getInst()->update();
}

void CCore::render()
{
	Rectangle(m_pMemTex->getDC(), -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	CSceneManager::getInst()->render(m_pMemTex->getDC());
	CCameraManager::getInst()->render(m_pMemTex->getDC());

	// FPS 출력하기
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"[Hallo Debug Knight] FPS : %d", CTimeManager::getInst()->getFPS());
	SetWindowText(hWnd, szBuffer);

	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_pMemTex->getDC(), 0, 0, SRCCOPY);
}

void CCore::init()
{
	CreateBrushPenFont();
	m_hDC = GetDC(hWnd);

	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CCameraManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();
	CSoundManager::getInst()->init();

	m_hDC = GetDC(hWnd);

	// 이중 버퍼링용 텍스쳐
	m_pMemTex = CResourceManager::getInst()->createTexture(L"BackBuffer", WINSIZEX, WINSIZEY);
}

void CCore::CreateBrushPenFont()
{	
	// brush
	m_arrBrush[(UINT)TYPE_BRUSH::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);	// 자주 쓰는 거 모아놓은 stock이 있음
	m_arrBrush[(UINT)TYPE_BRUSH::MAGENTA] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 255));
	// font
	m_arrFont[(UINT)TYPE_FONT::COMIC24] = CreateFont(24, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	m_arrFont[(UINT)TYPE_FONT::COMIC28] = CreateFont(28, 10, 0, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	m_arrFont[(UINT)TYPE_FONT::COMIC18] = CreateFont(18, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	// pen
	m_arrPen[(UINT)TYPE_PEN::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)TYPE_PEN::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)TYPE_PEN::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)TYPE_PEN::WHITE] = (HPEN)GetStockObject(WHITE_PEN);
}

HBRUSH CCore::getBrush(eBRUSH type)
{
	return m_arrBrush[(UINT)type];
}

HPEN CCore::getPen(ePEN type)
{
	return m_arrPen[(UINT)type];
}

HFONT CCore::getFont(eFONT type)
{
	return m_arrFont[(UINT)type];
}

HDC CCore::getMainDC()
{
	return m_hDC;
}