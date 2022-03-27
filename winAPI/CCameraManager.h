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

	bool		m_bArea;			// 카메라 범위 적용여부
	tCamArea	m_tCamArea;			// 카메라 범위 지정

private:
	void calculateDiff();

public:
	void init();
	void update();
	void render(HDC hDC);

	void setFocusNow(fPoint focus);
	void setFocusOn(fPoint focus);
	void setTraceObj(CObject* targetObj);

	void setCameraArea(float minX, float minY, float maxX, float maxY);	// WINSIZE 고려해서 맞춰줌
	void setIsArea(bool isOn);		

	fPoint getFocus();
	fPoint getRealPos(fPoint renderPos);
	fPoint getRenderPos(fPoint pos);

	void fadeIn(float dura);
	void fadeOut(float dura);

	void swing(float dura);

	void scroll(fVec2 vec, float spd);
};