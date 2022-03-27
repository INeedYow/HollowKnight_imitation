#pragma once

class CObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	SWING,
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

	bool		m_bArea;			// ī�޶� ���� ���뿩��
	tCamArea	m_tCamArea;			// ī�޶� ���� ����

private:
	void calculateDiff();

public:
	void init();
	void update();
	void render(HDC hDC);

	void setFocusNow(fPoint focus);
	void setFocusOn(fPoint focus);
	void setTraceObj(CObject* targetObj);

	void setCameraArea(float minX, float minY, float maxX, float maxY);	// WINSIZE ����ؼ� ������
	void setIsArea(bool isOn);		

	fPoint getFocus();
	fPoint getRealPos(fPoint renderPos);
	fPoint getRenderPos(fPoint pos);

	void fadeIn(float dura);
	void fadeOut(float dura);

	void swing(float dura);

	void scroll(fVec2 vec, float spd);
};