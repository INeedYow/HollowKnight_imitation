#pragma once

class CCollider;
class CAnimator;
class CEffector;

class CObject
{
	friend class CEventManager;
private:

	eOBJNAME	m_eName;			// �浹 ����� ������ �˷��� �ʿ���

	fPoint		m_fptPos;
	fPoint		m_fptSize;

	// ������Ʈ
	CCollider*	m_pCollider;
	CAnimator*	m_pAnimator;
	CEffector*	m_pEffector;

	bool		m_bDead;			// 1������ ����
	void		setDead();			// �̺�Ʈ �Ŵ����� ȣ���� �� �ֵ��� friend, private;

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

