#include "framework.h"
#include "func.h"

class CCollider;



// TODO �浹 ���� �˻� �Լ��� ���� ���� ������ �ʹ� �̻���

eDIR collRect2Rect(CCollider* coll1, CCollider* coll2)
{
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size1 = coll1->getOwner()->getSize();
	fPoint size2 = coll2->getOwner()->getSize();

	float distY = (size2.y + size1.y) / 2.f;
	float distX = (size2.x + size1.x) / 2.f;

	if (pos2.y - distY < pos1.y && pos1.y < pos2.y + distY)
	{
		if (pos1.x < pos2.x - size2.x / 2.f)
			return eDIR::LEFT;
		if (pos1.x > pos2.x + size2.x / 2.f)
			return eDIR::RIGHT;
	}
	else if (pos2.x - distX < pos1.x && pos1.x < pos2.x + distX)
	{
		if (pos1.y < pos2.y - size2.y / 2.f)
			return eDIR::TOP;
		if (pos1.y > pos2.y + size2.y / 2.f)
			return eDIR::BOTTOM;
	}
	return eDIR::NONE;
}


// == COLLRR
eDIR collisionRectToRect(CCollider* coll1, CCollider* coll2)
{	// Ÿ�ϰ� ���� ������ �� ��� 
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getOwner()->getSize();

	if (pos2.y - size2.y / 2 <= pos1.y && pos1.y <= pos2.y + size2.y / 2)
	{
		if (pos1.x <= pos2.x + size2.x / 2) return eDIR::LEFT;
		if (pos1.x >= pos2.x - size2.x / 2) return eDIR::RIGHT;
	}
	else
	{
		if (pos1.y <= pos2.y + size2.y / 2) return eDIR::TOP;
		if (pos1.y >= pos2.y - size2.y / 2) return eDIR::BOTTOM;
	}
	return eDIR::NONE;
}

// == COLLRRW
eDIR collisionRectToRectWide(CCollider* coll1, CCollider* coll2)
{ // Ÿ��, ���� �¿� �˻翡 �뽬 �ӵ� �����ؼ� �� �� �����Ӱ� ����(COLL enter(), keep() ���¿��� �˻��� �� �� ��)
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size1 = coll1->getOwner()->getSize();
	fPoint size2 = coll2->getOwner()->getSize();

	if (pos2.y - (size2.y + size1.y) / 2.f + 2 < pos1.y && 
		pos1.y < pos2.y + (size2.y + size1.y) / 2.f - 2)
	{
		if (pos1.x < pos2.x) return eDIR::LEFT;
		else return eDIR::RIGHT;
	}
	else
	{
		if (pos1.y <= pos2.y) return eDIR::TOP;
		else return eDIR::BOTTOM;
	}
	//return eDIR::NONE;
}

// == ISTOPEXIT
// ���������� �ߴ� ��ó�� leftSpd, rightSpd ������ ���� �ذ��� �� ���� ��
bool isTopColl(CCollider* coll1, CCollider* coll2)
{	// ���� exit() ���¿��� ���ݸ� �������� left, right�������� x��ġ �����ż� 
	// exit()���� ��Ÿ�ϰ� ���Ʒ� �浹 �˻縸 �� ��������
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getOwner()->getSize();

	return pos1.y <= pos2.y - size2.y / 2.f;
}

bool isLeftColl(CCollider* coll1, CCollider* coll2)
{
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();

	return pos1.x < pos2.x;
}

bool isCollisionRectToRect(const fPoint& pos1, const fPoint& size1, const fPoint& pos2, const fPoint& size2)
{	// == ISCOLLRR					// �簢��1 ��ǥ, ������				// �簢��2 ��ǥ, ������
	return ((abs(pos1.x - pos2.x) < (size1.x + size2.x) / 2.f) &&
		(abs(pos1.y - pos2.y) < (size1.y + size2.y) / 2.f));
}

bool isCollisionPointToRect(const fPoint& point, const RECT& rt)
{	// == ISCOLLPR						// ��ǥ		// �簢��
	return ((rt.left <= point.x && point.x <= rt.right) &&
		(rt.top <= point.y && point.y <= rt.bottom));
}	// ��ǥ������ �簢���� ���ԵǴ��� Ȯ��

bool isCollisionPointToCircle(const fPoint& point, const fPoint& cp, int cr)
{	// == ISCOLLPC						// ��ǥ //	�� �߽���ǥ,	 �� ������ ����
	// x, y ����
	float x = point.x - cp.x;
	float y = point.y - cp.y;

	// ��ǥ�� �� �߽ɱ��� �Ÿ�
	float distance = (float)sqrt((double)x * x + (double)y * y);

	// �Ÿ��� ���������� �۰ų� ������ �浹
	return (distance <= cr);
}

bool isCollisionCircleToRect(const fPoint& cp, int cr, const RECT& rt)
{	// == ISCOLLCR				// �� �߽���ǥ, �� ������ ���� // �簢��
	// ���� ������ ��ŭ Ȯ���Ų �簢���� ���� ����
	RECT rect = {
		(int)rt.left - cr,
		(int)rt.top - cr,
		(int)rt.right + cr,
		(int)rt.bottom + cr };

	// Ȯ���� �簢�� �ȿ� ���� �߽��� �ִٸ� �浹 (������ �浹�� ����)
	if ((rect.left <= cp.x && cp.x <= rect.right) && (rect.top <= cp.y && cp.y <= rect.bottom))
		return true;

	// ������ �浹 Ȯ�� (Ȯ���� �簢���� �� ������ ��ǥ�� �� �ȿ� �ִ��� Ȯ��)
	else
	{
		if (ISCOLLPC(fPoint((float)rect.left, (float)rect.top), cp, cr))			return true;
		if (ISCOLLPC(fPoint((float)rect.right, (float)rect.top), cp, cr))			return true;
		if (ISCOLLPC(fPoint((float)rect.right, (float)rect.bottom), cp, cr))		return true;
		if (ISCOLLPC(fPoint((float)rect.left, (float)rect.bottom), cp, cr))			return true;
	}
	return false;
}

bool isCollisionCircleToCircle(const fPoint& cp1, int cr1, const fPoint& cp2, int cr2)
{	// == ISCOLLCC					// ��1 �߽���ǥ, ������		// ��2 �߽���ǥ, ������
	// �� �߽ɳ��� �Ÿ� ���ؼ� �������� �պ��� ������ �浹
	float x = cp1.x - cp2.x;
	float y = cp1.y - cp2.y;

	float distance = (float)sqrt((double)x * x + (double)y * y);

	return (distance <= cr1 + cr2);
}

//bool isCollisionObliqueRect(const fPoint& cp1, int cr1, float theta1, const fPoint& cp2, int cr2, float theta2)
//{	//						// �簢��1 �߽���ǥ, size 1/2, ȸ����			// �簢��2 
//	
//	fPoint lt1 = ((cp1.x - cr1), (cp1.y - cr1));
//	
//	
//	
//	
//	
//	// lt, rt, lb, rb
//	fPoint arr1[4] = {
//		fPoint( -cr1, -cr2),
//		fPoint(cr1, -cr1),
//		fPoint(-cr1,  cr1),
//		fPoint(-cr1,  cr1),
//	};
//
//	for (int i = 0; i < 4; i++)
//	{
//		arr1[i].x = -(LONG)(arr1[i].x * cos(theta1) - arr1[i].y * sin(theta1));
//		arr1[i].y = -(LONG)(arr1[i].x * sin(theta1) + arr1[i].y * cos(theta1));
//	}
//
//	for (int i = 0; i < 4; i++)
//	{
//		arr1[i].x += (LONG)cp1.x;
//		arr1[i].y += (LONG)cp1.y;
//	}
//
//	// obj1�� �������� ����
//	fVec2 uVec = arr1[1] - arr1[0];
//	uVec = uVec.normalize();
//
//	// obj1�� �߽ɿ��� �� ������������ ����
//	fVec2 vec1 = arr1[1] - cp1;
//	fVec2 iVec1 = sqrt((arr1[1].x - cp1.x) * (arr1[1].x - cp1.x) + arr1)
//}




wstring addStrIDNumber(const wstring& str)
{
	return str + to_wstring(g_IDNumbering++);
}