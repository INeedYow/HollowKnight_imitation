#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,

	// TODO

	NONE
};

struct tCamEffect
{
	CAM_EFFECT eEffect;
	float fDura;
	float fTimer;
};

// ī�޶� �ּ� �ִ� ����
struct tCamArea
{
	float fMinX;
	float fMinY;
	float fMaxX;
	float fMaxY;
};

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	fPoint		m_fpFocus;
	fPoint		m_fpCurFocus;
	fPoint		m_fpPrevFocus;
	CObject*	m_pTraceObj;

	fPoint		m_fpDiff;			// �ػ� �߽���ǥ�� ī�޶� Focus��ǥ ���̰�

	float		m_fTime;			// trace�� �ɸ��� �ð�
	float		m_fAccTime;
	float		m_fSpeed;

	list<tCamEffect>	m_listCamEffect;	// ����Ʈ�� ī�޶� ȿ�� ���������� ����
	CTexture*			m_pTex;

	// TODO
	tCamArea	m_tCamArea;			// ī�޶� �ִ� �ּ� ��ǥ ����

private:
	void calculateDiff();

public:
	void init();
	void update();
	void render(HDC hDC);

	void setFocusNow(fPoint focus);
	void setFocusOn(fPoint focus);
	void setTraceObj(CObject* targetObj);

	fPoint getFocus();
	fPoint getRealPos(fPoint renderPos);
	fPoint getRenderPos(fPoint pos);

	void fadeIn(float dura);
	void fadeOut(float dura);

	void scroll(fVec2 vec, float spd);
};

// �� ������Ʈ�� ���󰡰ų� Ư�� ��ǥ�� ����
// ������Ʈ�� ������ ��ǥ �������