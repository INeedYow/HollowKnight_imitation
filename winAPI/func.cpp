#include "framework.h"
#include "func.h"

class CCollider;



bool isTopExit(CCollider* coll1, CCollider* coll2)
{	// �̹� �浹�� ���¿���
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getOwner()->getSize();

	return (pos1.y <= pos2.y - size2.y * 0.5f);
}

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

bool isTopCollOnly(CCollider* coll1, CCollider* coll2)
{	// GROUND Ÿ���̶� �浹 �� ���� ����
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getSize();

	if (pos1.y < pos2.y && abs(pos1.x - pos2.x) <= size2.x / 2.f)
		return true;

	return false;
}

bool isBottomCollOnly(CCollider* coll1, CCollider* coll2)
{	// �Ʒ���
	fPoint pos1 = coll1->getPos();
	fPoint pos2 = coll2->getPos();
	fPoint size2 = coll2->getSize();

	if (pos1.y > pos2.y && abs(pos1.x - pos2.x) <= size2.x / 2.f)
		return true;

	return false;
}

bool isLeftColl(CCollider* coll1, CCollider* coll2)
{	// WALL Ÿ���̶� �浹 �� �¿츸 ����
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

bool isCollisionObliqueRect(fPoint leftTop1, fPoint centerPos1, fPoint size1, float rad1, fPoint leftTop2, fPoint centerPos2, fPoint size2, float rad2)
{								//	�»�� ��ǥ,	�߽���ǥ,		������,	ȸ������
	return false;
}


wstring addStrIDNumber(const wstring& str)
{
	return str + to_wstring(g_IDNumbering++);
}


float dotVector(fVec2 vec1, fVec2 vec2)
{
	return abs(vec1.x * vec2.x + vec1.y * vec2.y);
}


//enum pt { lt, rt, lb };
//// fpArr[0] : �»���ǥ, [1] : �����ǥ, [2] : ���� ��ǥ
//bool isOBB(fPoint* fpArr1, fPoint pos1, fPoint sz1, float rad1, 
//	fPoint* fpArr2, fPoint pos2, fPoint sz2, float rad2)
//{	
//	// obj1 �� ������, ���� ����
//	fVec2 rVec1 = ((fpArr1[rt] - fpArr1[lt]) / 2.f).normalize();
//	fVec2 uVec1 = ((fpArr1[lt] - fpArr1[lb]) / 2.f).normalize();
//
//	// obj2 �� ������, ���� ����
//	fVec2 rVec2 = ((fpArr2[rt] - fpArr2[lt]) / 2.f).normalize();
//	fVec2 uVec2 = ((fpArr2[lt] - fpArr2[lb]) / 2.f).normalize();
//
//	// �Ÿ�����
//	fVec2 distVec = pos2 - pos1;
//
//	fVec2 unitVec, projA, projB, projC;
//	float sum = 0.f;
//	float dist = 0.f;
//
//		// # cycle 1-1
//	// 
//	projA = fpArr1[lt] - pos1;
//	projB = uVec2 * dotVector(fpArr2[lt] - pos2, uVec2);
//	projC = rVec2 * dotVector(fpArr2[lt] - pos2, rVec2);
//	
//	// ��������
//	unitVec = rVec1;
//	
//	// �������Ϳ� ���翵 ���� �� vs ����
//	sum = dotVector(projA, unitVec) 
//		+ dotVector(projB, unitVec) 
//		+ dotVector(projC, unitVec);
//	dist = dotVector(distVec, unitVec);
//
//	if (sum < dist)
//		return false;
//
//		// # cycle 1-2
//	unitVec = uVec1;
//
//	sum = dotVector(projA, unitVec)
//		+ dotVector(projB, unitVec)
//		+ dotVector(projC, unitVec);
//	dist = dotVector(distVec, unitVec);
//
//	if (sum < dist)
//		return false;
//
//		// # cycle 2-1
//	projA = uVec1 * dotVector(fpArr1[lt] - pos1, uVec1);
//	projB = rVec1 * dotVector(fpArr1[lt] - pos1, rVec1);
//	projC = fpArr2[lt] - pos2;
//
//	unitVec = rVec2;
//	
//	sum = dotVector(projA, unitVec)
//		+ dotVector(projB, unitVec)
//		+ dotVector(projC, unitVec);
//	dist = dotVector(distVec, unitVec);
//
//
//	if (sum < dist)
//		return false;
//
//		// # cycle 2-2
//	unitVec = uVec2;
//
//	sum = dotVector(projA, unitVec)
//		+ dotVector(projB, unitVec)
//		+ dotVector(projC, unitVec);
//	dist = dotVector(distVec, unitVec);
//
//	if (sum < dist)
//		return false;
//
//	return true;
//}


enum pt { lt, rt, lb };
// fpArr[0] : �»���ǥ, [1] : �����ǥ, [2] : ���� ��ǥ
bool isOBB(fPoint* fpArr1, fPoint pos1, fPoint sz1, float rad1,
	fPoint* fpArr2, fPoint pos2, fPoint sz2, float rad2)
{
	// obj1 �� ������, ���� ����
	fVec2 rVec1 = ((fpArr1[rt] - fpArr1[lt]) / 2.f);
	fVec2 uVec1 = ((fpArr1[lt] - fpArr1[lb]) / 2.f);

	// obj2 �� ������, ���� ����
	fVec2 rVec2 = ((fpArr2[rt] - fpArr2[lt]) / 2.f);
	fVec2 uVec2 = ((fpArr2[lt] - fpArr2[lb]) / 2.f);

	// �Ÿ�����
	fVec2 distVec = pos2 - pos1;

	fVec2 unitVec, projA, projB, projC;
	float sum = 0.f;
	float dist = 0.f;
	float max = 0.f;

	UINT cnt = 0;

	// # cycle 1-1
	unitVec = rVec1.normalize();

	dist = dotVector(distVec, unitVec);

	max = max(
		max(dotVector((rVec2 + uVec2), unitVec), dotVector((rVec2 + uVec2 * -1.f), unitVec)),
		max(dotVector((rVec2 * -1.f + uVec2), unitVec), dotVector((rVec2 * -1.f + uVec2 * -1.f), unitVec)));

	sum = dotVector(rVec1, unitVec) + max;	// rVec2 + uVec2�� ��� ����ĵ��� �ٸ�

	if (sum < dist) return false;

	// # cycle 1-2
	unitVec = uVec1.normalize();

	dist = dotVector(distVec, unitVec);
	
	max = max(
		max(dotVector((rVec2 + uVec2), unitVec), dotVector((rVec2 + uVec2 * -1.f), unitVec)),
		max(dotVector((rVec2 * -1.f + uVec2), unitVec), dotVector((rVec2 * -1.f + uVec2 * -1.f), unitVec)));

	sum = dotVector(uVec1, unitVec) + max;

	if (sum < dist) return false;

	// # cycle 2-1
	unitVec = rVec2.normalize();

	dist = dotVector(distVec, unitVec);

	max = max(
		max(dotVector((rVec2 + uVec2), unitVec), dotVector((rVec2 + uVec2 * -1.f), unitVec)),
		max(dotVector((rVec2 * -1.f + uVec2), unitVec), dotVector((rVec2 * -1.f + uVec2 * -1.f), unitVec)));

	sum = dotVector(rVec2, unitVec) + max;

	if (sum < dist) return false;

	// # cycle 2-2
	unitVec = uVec2.normalize();

	dist = dotVector(distVec, unitVec);

	max = max(
		max(dotVector((rVec2 + uVec2), unitVec), dotVector((rVec2 + uVec2 * -1.f), unitVec)),
		max(dotVector((rVec2 * -1.f + uVec2), unitVec), dotVector((rVec2 * -1.f + uVec2 * -1.f), unitVec)));

	sum = dotVector(uVec2, unitVec) + max;

	if (sum < dist) return false;

	return true;

}

fVec2 addVector(fVec2 a, fVec2 b) { //vector plus
	fVec2 ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return ret;
}

float absDotVector(fVec2 a, fVec2 b) { // dot product �� ���е��� ���� ��
	return abs(a.x * b.x + a.y * b.y);
}

float Deg2Rad(float deg) { //deg -> rad
	return deg / 180 * 3.141592f;
}

fVec2 getDistanceVector(SHAPE a, SHAPE b) { //distance vector
	fVec2 ret;
	ret.x = (a.left + a.width / 2) - (b.left + b.width / 2);
	ret.y = (a.top + a.height / 2) - (b.top + b.height / 2);
	return ret;
}

fVec2 getHeightVector(SHAPE a) { //height vector
	fVec2 ret;
	ret.x = (float)(a.height * cos(Deg2Rad(a.rot - 90)) / 2.f);
	ret.y = (float)(a.height * sin(Deg2Rad(a.rot - 90)) / 2.f);
	return ret;
}

fVec2 getWidthVector(SHAPE a) { //width vector
	fVec2 ret;
	ret.x = (float)(a.width * cos(Deg2Rad(a.rot)) / 2.f);
	ret.y = (float)(a.width * sin(Deg2Rad(a.rot)) / 2.f);
	return ret;
}

fVec2 getUnitVector(fVec2 a) { // �������� (�� �簢�� �� ������ ���� �� ���� �������Ϳ� ����)
	fVec2 ret;
	float size;
	size = (float)sqrt(pow(a.x, 2) + pow(a.y, 2));
	ret.x = a.x / size;
	ret.y = a.y / size;
	return ret;
}

bool OBB(SHAPE a, SHAPE b) { // �� ȸ���� �࿡ ������ ���̷� �Ǻ�
	fVec2 dist = getDistanceVector(a, b);
	fVec2 vec[4] = { getHeightVector(a), getHeightVector(b), getWidthVector(a), getWidthVector(b) };
	fVec2 unit;
	for (int i = 0; i < 4; i++) {
		float sum = 0;
		unit = getUnitVector(vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += absDotVector(vec[j], unit);
		}
		if (absDotVector(dist, unit) > sum) {
			return false;
		}
	}
	return true;
}