#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CObject.h"
#include "CTexture.h"

#include "SelectGDI.h"

CAnimation::CAnimation()
{
	m_strName = L"";
	m_pAnimator = nullptr;
	m_pTex = nullptr;
	m_uiCurFrm = 0;
	m_fTimer = 0.f;
}

CAnimation::~CAnimation()
{
}

void CAnimation::setName(const wstring& strName)
{
	m_strName = strName;
}

const wstring& CAnimation::getName()
{
	return m_strName;
}

void CAnimation::setFrame(UINT frmIndex)
{
	m_uiCurFrm = frmIndex;
}

tAniFrm& CAnimation::getFrame(UINT frmIndex)
{
	return m_vecFrm[frmIndex];
}

void CAnimation::setRepeat(bool isRepeat)
{
	m_bRepeat = isRepeat;
}

void CAnimation::update()
{
	m_fTimer += fDT;

	if (m_vecFrm[m_uiCurFrm].fDuration < m_fTimer)
	{
		m_uiCurFrm++;

		if (m_bRepeat)
		{	// 반복 O (나머지 연산 활용)
			m_uiCurFrm %= m_vecFrm.size();
		}
		else
		{	// 반복 X (frm고정)
			if (m_uiCurFrm >= m_vecFrm.size())
				m_uiCurFrm = (UINT)(m_vecFrm.size() - 1);
		}

		m_fTimer = 0.f;
	}
}

void CAnimation::render(HDC hDC, float theta)
{
	fPoint pos = m_pAnimator->getOwner()->getPos();
	tAniFrm frm = m_vecFrm[m_uiCurFrm];
	pos += frm.fpOffset;
	pos = rendPos(pos);

	if (0.f == theta)
	{
		TransparentBlt(hDC,
			(int)(pos.x - frm.fpSlice.x / 2.f),
			(int)(pos.y - frm.fpSlice.y / 2.f),
			(int)(frm.fpSlice.x),
			(int)(frm.fpSlice.y),
			m_pTex->getDC(),
			(int)(frm.fpLeftTop.x),
			(int)(frm.fpLeftTop.y),
			(int)(frm.fpSlice.x),
			(int)(frm.fpSlice.y),
			RGB(255, 0, 255));
	}
	else
	{
		POINT pointArr[3];
		UINT texSize = m_pAnimator->getMemTex()->getMaxSize();
		HDC hMemDC = m_pAnimator->getMemTex()->getDC();

		// 좌상, 우상, 좌하 좌표 3개
		fPoint arr[3] = {
			fPoint(frm.fpSlice.x / -2.f,	frm.fpSlice.y / -2.f),
			fPoint(frm.fpSlice.x / 2.f,		frm.fpSlice.y / -2.f),
			fPoint(frm.fpSlice.x / -2.f,	frm.fpSlice.y / 2.f)
		};

		for (int i = 0; i < 3; i++)
		{	// 좌표에 회전행렬로 회전적용
			pointArr[i].x = -(LONG)(arr[i].x * cos(theta) - arr[i].y * sin(theta));
			pointArr[i].y = -(LONG)(arr[i].x * sin(theta) + arr[i].y * cos(theta));
		}

		for (int i = 0; i < 3; i++)
		{	// memDC 중앙 좌표로 이동
			pointArr[i].x += (LONG)(texSize / 2);
			pointArr[i].y += (LONG)(texSize / 2);
		}

		// memDC 마젠타로 채움
		SelectGDI brush(hMemDC, eBRUSH::MAGENTA);
		Rectangle(hMemDC, -1, -1, texSize + 1, texSize + 1);

		// 회전
		PlgBlt(hMemDC,
			pointArr,
			m_pTex->getDC(),
			(int)(frm.fpLeftTop.x),
			(int)(frm.fpLeftTop.y),
			(int)(frm.fpSlice.x),
			(int)(frm.fpSlice.y),
			NULL,
			0, 0
		);

		// 마젠타 제거
		TransparentBlt(hDC,
			(int)(pos.x - texSize / 2),
			(int)(pos.y - texSize / 2),
			texSize,
			texSize,
			hMemDC,
			0,
			0,
			texSize,
			texSize,
			RGB(255, 0, 255)
		);
	}
}

void CAnimation::create(CTexture* pTex, fPoint leftTop, fPoint slice,
	fPoint step, float dura, UINT frmCnt, bool isRepeat)
{
	m_pTex = pTex;

	tAniFrm frm = {};
	for (UINT i = 0; i < frmCnt; i++)
	{
		frm.fDuration = dura;
		frm.fpSlice = slice;
		frm.fpLeftTop = leftTop + step * i;

		m_vecFrm.push_back(frm);
	}

	m_bRepeat = isRepeat;
}