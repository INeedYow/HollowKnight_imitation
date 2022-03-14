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

// �� ������Ʈ�� ���󰡰ų� Ư�� ��ǥ�� ����
// ������Ʈ�� ������ ��ǥ �������