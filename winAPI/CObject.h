#pragma once

class CCollider;
class CAnimator;
class CEffector;

class CObject
{
	friend class CEventManager;
private:

	eOBJNAME	m_eName;			// 충돌 대상의 종류를 알려면 필요함

	fPoint		m_fptPos;
	fPoint		m_fptSize;

	// 컴포넌트
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;
	CEffector*	m_pEffector;

	bool		m_bDead;			// 1프레임 유예
	void		setDead();			// 이벤트 매니저만 호출할 수 있도록 friend, private;

public:
	CObject();
	CObject(const CObject& other);
	virtual ~CObject();
	virtual CObject* clone();

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setName(eOBJNAME name);

	fPoint		getPos();
	fPoint		getSize();
	eOBJNAME	getName();

	bool isDead();

	virtual void update() = 0;
	virtual void finalUpdate();
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();

	CAnimator* getAnimator();
	void createAnimator();

	CEffector* getEffector();
	void createEffector();

	virtual void collisionKeep(CCollider* pOther) {}
	virtual void collisionEnter(CCollider* pOther) {}
	virtual void collisionExit(CCollider* pOther) {}

};

