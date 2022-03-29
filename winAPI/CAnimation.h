#pragma once

class CAnimator;
class CTexture;

struct tAniFrm
{
	fPoint	fpLeftTop;
	fPoint	fpSlice;	// �ڸ��� ������ ũ��
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

	float			m_fPrevTheta;			// ȸ�� ���� �ٽ� ���� �����ϱ� ���� �ʿ��� ���� ��Ÿ��

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