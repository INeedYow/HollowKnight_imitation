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

// 카메라 최소 최대 범위
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

	fPoint		m_fpDiff;			// 해상도 중심좌표와 카메라 Focus좌표 차이값

	float		m_fTime;			// trace에 걸리는 시간
	float		m_fAccTime;
	float		m_fSpeed;

	list<tCamEffect>	m_listCamEffect;	// 리스트로 카메라 효과 순차적으로 실행
	CTexture*			m_pTex;

	// TODO
	tCamArea	m_tCamArea;			// 카메라 최대 최소 좌표 범위

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

// 한 오브젝트만 따라가거나 특정 좌표를 보게
// 오브젝트가 렌더될 좌표 구해줘야