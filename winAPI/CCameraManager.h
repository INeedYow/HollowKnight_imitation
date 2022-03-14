#pragma once

class CObject;

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

	void calculateDiff();

public:
	void update();

	void setFocusOn(fPoint focus);
	void setTraceObj(CObject* targetObj);

	fPoint getFocus();
	fPoint getRealPos(fPoint renderPos);
	fPoint getRenderPos(fPoint pos);


};

// 한 오브젝트만 따라가거나 특정 좌표를 보게
// 오브젝트가 렌더될 좌표 구해줘야