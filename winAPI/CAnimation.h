#pragma once

class CAnimator;
class CTexture;

struct tAniFrm
{
	fPoint	fpLeftTop;
	fPoint	fpSlice;	// 자르는 영역의 크기
	fPoint	fpOffset;
	float	fDuration;
};

class CAnimation
{
	friend class CAnimator;

	wstring			m_strName;
	CAnimator*		m_pAnimator;

	CTexture*		m_pTex;

	vector<tAniFrm> m_vecFrm;
	UINT			m_uiCurFrm;

	float			m_fTimer;
	bool			m_bRepeat;

	float			m_fPrevTheta;			// 회전 연산 다시 할지 결정하기 위해 필요한 이전 세타값

public:
	CAnimation();
	~CAnimation();

	void setName(const wstring& strName);
	const wstring& getName();

	void setFrame(UINT frmIndex);
	tAniFrm& getFrame(UINT frmIndex);

	void setFrmOffset(UINT frmIdx, fPoint offset);
	void setAllOffset(fPoint offset);

	void setRepeat(bool isRepeat);

	void update();
	void render(HDC hDC, float theta = 0.f, bool rotReverse = false);

	void create(CTexture* pTex, fPoint leftTop, fPoint slice,
		fPoint step, float dura, UINT frmCnt, bool isRepeat = true);
};

#define STD_CAL		0.12f