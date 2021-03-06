#pragma once
class SelectGDI
{
	HDC		m_hDC;
	HBRUSH	m_hDefaultBrush;
	HPEN	m_hDefaultPen;
	HFONT	m_hDefaultFont;

public:
	SelectGDI(HDC hDC, eBRUSH type)
	{
		m_hDC = hDC;
		HBRUSH hBrush = CCore::getInst()->getBrush(type);
		m_hDefaultBrush = (HBRUSH)SelectObject(hDC, hBrush);
		m_hDefaultPen = 0;
		m_hDefaultFont = 0;
	}

	SelectGDI(HDC hDC, eBRUSH typeTrue, eBRUSH typeFalse, bool mode)
	{
		m_hDC = hDC;
		HBRUSH hBrush;

		if (mode)
			hBrush = CCore::getInst()->getBrush(typeTrue);
		else
			hBrush = CCore::getInst()->getBrush(typeFalse);

		m_hDefaultBrush = (HBRUSH)SelectObject(hDC, hBrush);
		m_hDefaultPen = 0;
		m_hDefaultFont = 0;

	}

	SelectGDI(HDC hDC, ePEN type)
	{
		m_hDC = hDC;
		HPEN hPen = CCore::getInst()->getPen(type);
		m_hDefaultPen = (HPEN)SelectObject(hDC, hPen);
		m_hDefaultBrush = 0;
		m_hDefaultFont = 0;

	}

	SelectGDI(HDC hDC, ePEN typeTrue, ePEN typeFalse, bool mode)
	{
		m_hDC = hDC;
		HPEN hPen;

		if (mode)
			hPen = CCore::getInst()->getPen(typeTrue);
		else
			hPen = CCore::getInst()->getPen(typeFalse);

		m_hDefaultPen = (HPEN)SelectObject(hDC, hPen);
		m_hDefaultBrush = 0;
		m_hDefaultFont = 0;

	}

	SelectGDI(HDC hDC, eFONT type)
	{
		m_hDC = hDC;
		HFONT hFont;

		hFont = CCore::getInst()->getFont(type);
		m_hDefaultFont = (HFONT)SelectObject(hDC, hFont);
		m_hDefaultBrush = 0;
		m_hDefaultPen = 0;


	}
	~SelectGDI()
	{
		SelectObject(m_hDC, m_hDefaultBrush);
		SelectObject(m_hDC, m_hDefaultPen);
		SelectObject(m_hDC, m_hDefaultFont);
	}
};

