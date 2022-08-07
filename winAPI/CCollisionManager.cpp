#include "framework.h"
#include "CCollisionManager.h"
#include "CScene.h"
#include "CPlayer.h"
#include "func.h"

CCollisionManager::CCollisionManager()
{
	m_arrCollChk[0] = 0;
}

CCollisionManager::~CCollisionManager()
{

}

// �浹�ϴ� OBJ�׷��� ������Ʈ�� ��θ� ���ؾ� �ϱ� ������ ������Ʈ �迭 �޾ƿ;� �Ѵ�.
// ���� ���� ������Ʈ�鸸 ������ �ǰ� ���� ���� �� �Ŵ����� �˰� �ִ�.
void CCollisionManager::collisionGroupUpdate(eOBJ obj1, eOBJ obj2)
{
	CScene* pCurScene = CSceneManager::getInst()->getCurScene();

	const vector<CObject*> vec1 = pCurScene->getGroupObject(obj1);
	const vector<CObject*> vec2 = pCurScene->getGroupObject(obj2);

	for (int i = 0; i < vec1.size(); i++)
	{
		if (nullptr == vec1[i]->getCollider())	continue;			// �浹ü ���� ���

		for (int j = 0; j < vec2.size(); j++)
		{
			if (nullptr == vec2[j]->getCollider()) continue;		// �浹ü ���� ���

			if (vec1[i] == vec2[j]) continue;						// vec[]�� CObject*�ϱ� �ּҰ� ���� ���(���� ��ü�� ���) ����ó��

			// ID�� Ű��
			COLLIDER_ID id;
			id.left_id = vec1[i]->getCollider()->getID();
			id.right_id = vec2[j]->getCollider()->getID();

			map<ULONGLONG, bool>::iterator iter = m_mapIsColl.find(id.ID);	// �ش� ���̵�� �� �ڷ������� ã��

			if (m_mapIsColl.end() == iter)							// �� ã������ ������ְ� ã��
			{	// map.insert(make_pair(ULONGLONG, bool);
				m_mapIsColl.insert(make_pair(id.ID, false));		// �⺻�� false;
				iter = m_mapIsColl.find(id.ID);
			}	// iter->second�� ���� ������ �浹 ���°� ������ ����



			if (isCollision(vec1[i]->getCollider(), vec1[i]->getCollider()->getShape(),
				vec2[j]->getCollider(), vec2[j]->getCollider()->getShape()))
			{	// ���� �浹 O
				if (iter->second)
				{	// ���� �浹 O // �� �浹ü���� �浹���¿� ���� �ٸ��� �˷��� �ʿ伺 (collider�� �Լ� �߰�)
					if (vec1[i]->isDead() || vec2[j]->isDead())
					{	// ���� O : �浹 ����
						vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
						iter->second = false;
					}
					else
					{	// ���� X : �浹 ���� ��
						vec1[i]->getCollider()->collisionKeep(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionKeep(vec1[i]->getCollider());
					}

				}
				else
				{	// ���� �浹 X
					if (!vec1[i]->isDead() && !vec2[j]->isDead())
					{	// ���� X : �浹 ����
						vec1[i]->getCollider()->collisionEnter(vec2[j]->getCollider());
						vec2[j]->getCollider()->collisionEnter(vec1[i]->getCollider());
						iter->second = true;
					}
					// ���� O : �浹 ���� �� �� (else�� �ƹ� �͵� �� �ʿ����)
				}
			}
			else
			{	// ���� �浹 X
				if (iter->second)
				{	// ���� �浹 O : �浹 ���� (������ �ƴϵ� Ż���ϸ� ��)
					vec1[i]->getCollider()->collisionExit(vec2[j]->getCollider());
					vec2[j]->getCollider()->collisionExit(vec1[i]->getCollider());
					iter->second = false;
				}
				// else �� �浹�� �� ���� �浹�ϰ� ���� ���� ���´ϱ� �ƹ��͵� �� �ʿ� ����
			}
		}
	}
}


bool CCollisionManager::isCollision(CCollider* pColl1, eSHAPE shape1, CCollider* pColl2, eSHAPE shape2)
{
	fPoint pos1 = pColl1->getPos();
	fPoint size1 = pColl1->getSize();
	fPoint pos2 = pColl2->getPos();
	fPoint size2 = pColl2->getSize();

	switch (shape1)
	{
	case eSHAPE::CIRCLE:
		switch (shape2)
		{
		case eSHAPE::CIRCLE:
		{
			return ISCOLLCC(pos1, (int)(size1.x * 0.5f), pos2, (int)(size2.x * 0.5f));
		}
		case eSHAPE::RECT:
		{
			RECT rt = { (int)(pos2.x - size2.x * 0.5f), (int)(pos2.y - size2.y * 0.5f),
						(int)(pos2.x + size2.x * 0.5f), (int)(pos2.y + size2.y * 0.5f) };
			return ISCOLLCR(pos1, (int)(size1.x * 0.5f), rt);
		}
		case eSHAPE::POINT:
		{
			return ISCOLLPC(pos2, pos1, (int)(size1.x * 0.5f));
		}
		}
		break;
		//
	case eSHAPE::RECT:
		switch (shape2)
		{
		case eSHAPE::CIRCLE:
		{
			RECT rt = { (int)(pos1.x - size1.x * 0.5f), (int)(pos1.y - size1.y * 0.5f),
						(int)(pos1.x + size1.x * 0.5f), (int)(pos1.y + size1.y * 0.5f) };
			return ISCOLLCR(pos2, (int)(size2.x * 0.5f), rt);
		}
		break;
		case eSHAPE::RECT:
		{	// obliq�� �������� ���� rect�ε� getRad()�� �Ѵ� 0�� ��� �Ϲ� �浹�Լ�, �ƴ� ��� obb�浹�Լ� ȣ���ϴ� ������
			float rad1 = pColl1->getRad();
			float rad2 = pColl2->getRad();
			fPoint ofs1 = pColl1->getOffset();
			fPoint ofs2 = pColl2->getOffset();

			if (0.f == rad1 && 0.f == rad2)
				return ISCOLLRR(pos1, size1, pos2, size2);
			//else
			//{	// �»�, ���, ���� ��ǥ(��������)
			//	fPoint fpArr1[3] = {
			//		fPoint(size1.x / -2.f,	size1.y / -2.f),
			//		fPoint(size1.x / 2.f,	size1.y / -2.f),
			//		fPoint(size1.x / -2.f,	size1.y / 2.f)
			//	};
			//	fPoint fpArr2[3] = {
			//		fPoint(size2.x / -2.f,	size2.y / -2.f),
			//		fPoint(size2.x / 2.f,	size2.y / -2.f),
			//		fPoint(size2.x / -2.f,	size2.y / 2.f)
			//	};

			//	if (0.f != rad1)
			//	{	// obj1 ȸ��
			//		for (int i = 0; i < 3; i++)
			//		{	// ��ǥ�� ȸ����ķ� ȸ������
			//			fpArr1[i].x = (float)(fpArr1[i].x * cos(rad1) - fpArr1[i].y * sin(rad1));
			//			fpArr1[i].y = (float)(fpArr1[i].x * sin(rad1) + fpArr1[i].y * cos(rad1));
			//		}
			//	}
			//	if (0.f != rad2)
			//	{	// obj2 ȸ��
			//		for (int i = 0; i < 3; i++)
			//		{	// ��ǥ�� ȸ����ķ� ȸ������
			//			fpArr2[i].x = (float)(fpArr2[i].x * cos(rad2) - fpArr2[i].y * sin(rad2));
			//			fpArr2[i].y = (float)(fpArr2[i].x * sin(rad2) + fpArr2[i].y * cos(rad2));
			//		}
			//	}

			//	for (int i = 0; i < 3; i++)
			//	{	// �������� ������ġ��
			//		fpArr1[i] += pos1 + ofs1;
			//	}
			//	for (int i = 0; i < 3; i++)
			//	{
			//		fpArr2[i] += pos2 + ofs2;
			//	}

			//	return isOBB(fpArr1, pos1, size1, rad1, fpArr2, pos2, size2, rad2);
			//}
			else
			{
				SHAPE shape1 = {
					pos1.y - size1.y * 0.5f,
					pos1.x - size1.x * 0.5f,
					size1.y,
					size1.x,
					rad1 * 180 / PI
				};

				SHAPE shape2 = {
					pos2.y - size2.y * 0.5f,
					pos2.x - size2.x * 0.5f,
					size2.y,
					size2.x,
					rad2 * 180 / PI
				};

				return OBB(shape1, shape2);
			}

		}
		case eSHAPE::POINT:
		{
			RECT rt = { (int)(pos1.x - size1.x * 0.5f), (int)(pos1.y - size1.y * 0.5f),
						(int)(pos1.x + size1.x * 0.5f), (int)(pos1.y + size1.y * 0.5f) };
			return ISCOLLPR(pos2, rt);
		}
		}
		//
	case eSHAPE::POINT:
		switch (shape2)
		{
		case eSHAPE::CIRCLE:
		{
			return ISCOLLPC(pos1, pos2, (int)(size2.x * 0.5f));
		}
		case eSHAPE::RECT:
		{
			RECT rt = { (int)(pos2.x - size2.x * 0.5f), (int)(pos2.y - size2.y * 0.5f),
						(int)(pos2.x + size2.x * 0.5f), (int)(pos2.y + size2.y * 0.5f) };
			return ISCOLLPR(pos1, rt);
		}
		case eSHAPE::POINT:
		{
			return (pos1 == pos2);
		}
		}

	}
	return false;
}

void CCollisionManager::init()
{
}

// �浹 ���� üũ�� �׷츸 Ȯ���ϵ��� �з�
void CCollisionManager::update()
{
	for (int i = 0; i < (UINT)eOBJ::SIZE; i++)
	{	// ������ �˻� �� �ص� �Ǵϱ� j = i���� ����
		for (int j = i; j < (UINT)eOBJ::SIZE; j++)
		{	// �浹 ���� ��Ʈ�� ������ UINT m_arrCollChk[]�� 1�̸� ���� 
			if (m_arrCollChk[i] & (0x1 << j))
			{	
				collisionGroupUpdate((eOBJ)i, (eOBJ)j);
			}
		}
	}
}

void CCollisionManager::checkGroup(eOBJ obj1, eOBJ obj2)
{
	UINT groupLow, group;

	groupLow = (UINT)obj1;
	group = (UINT)obj2;

	if ((UINT)obj1 > (UINT)obj2)
	{
		groupLow = (UINT)obj2;
		group = (UINT)obj1;
	}

	m_arrCollChk[(UINT)groupLow] |= (0x1 << group);
}

void CCollisionManager::unCheckGroup(eOBJ obj1, eOBJ obj2)
{
	UINT groupLow, group;

	groupLow = (UINT)obj1;
	group = (UINT)obj2;

	if ((UINT)obj1 > (UINT)obj2)
	{
		groupLow = (UINT)obj2;
		group = (UINT)obj1;
	}

	m_arrCollChk[(UINT)groupLow] &= ~(0x1 << group);
}

void CCollisionManager::resetGroup()
{	// (void* Dst, int Val,  size_t Size)
	memset(m_arrCollChk, 0, sizeof(UINT) * (UINT)eOBJ::SIZE);		// memset �ӵ��� �ſ� ����
}
