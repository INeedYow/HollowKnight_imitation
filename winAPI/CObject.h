#pragma once

class CCollider;
class CAnimator;

class CObject
{
	friend class CEventManager;
private:

	OBJNAME		m_eName;			// �浹 ����� ������ �˷��� �ʿ���

	fPoint		m_fptPos;
	fPoint		m_fptSize;

	// ������Ʈ
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool		m_bDead;			// 1������ ����
	void		setDead();			// �̺�Ʈ �Ŵ����� ȣ���� �� �ֵ��� friend, private;

public:
	CObject();
	CObject(const CObject& other);
	virtual ~CObject();
	virtual CObject* clone() = 0;

	void setPos(fPoint pos);
	void setSize(fPoint size);
	void setName(OBJNAME name);

	fPoint	getPos();
	fPoint	getSize();
	OBJNAME	getName();

	bool isDead();

	virtual void update() = 0;
	virtual void finalUpdate() final;	// �������̵� ����
	virtual void render(HDC hDC);
	virtual void componentRender(HDC hDC);

	CCollider* getCollider();
	void createCollider();				// 

	CAnimator* getAnimator();
	void createAnimator();

	virtual void collisionKeep(CCollider* pOther) {}
	virtual void collisionEnter(CCollider* pOther) {}
	virtual void collisionExit(CCollider* pOther) {}

};

