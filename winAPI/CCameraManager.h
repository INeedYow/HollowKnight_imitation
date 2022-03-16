#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,

	NONE
};

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	fPoint		m_fpFocus;
	fPoint		m_fpCurFocus;
	fPoint		m_fpPrevFocus;
	CObject*	m_pTraceObj;

	fPoint		m_fpDiff;

	float		m_fTime;
	float		m_fAccTime;
	float		m_fSpeed;

	CAM_EFFECT	m_eEffect;
	CTexture*	m_pTex;

private:
	void calculateDiff();

public:
	void init();
	void update();
	void render(HDC hDC);

	void setFocusOn(fPoint focus);
	void setTraceObj(CObject* targetObj);

	fPoint getFocus();
	fPoint getRealPos(fPoint renderPos);
	fPoint getRenderPos(fPoint pos);

	void scroll(fVec2 vec, float spd);
};

// �� ������Ʈ�� ���󰡰ų� Ư�� ��ǥ�� ����
// ������Ʈ�� ������ ��ǥ �������