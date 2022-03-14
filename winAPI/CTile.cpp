#include "framework.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
{
	m_pTex = nullptr;
	m_iIndex = 0;
	setSize(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render(HDC hDC)
{
	if (nullptr == m_pTex) return;

	// �ؽ��� ���� ���� ����
	UINT iWidth = m_pTex->getBmpWidth();
	UINT iHeight = m_pTex->getBmpHeight();

	// ���� ���� �ε��� ��
	UINT iMaxX = iWidth / SIZE_TILE;
	UINT iMaxY = iHeight / SIZE_TILE;

	// ���� x,y �ε��� ���� ������ ���� Ȱ�� (Ÿ���� lefttop ��ǥ)
		// ���� X = index�� �ִ� X������ŭ ���� �� �� ���Ҵ���
	UINT iCurX = m_iIndex % iMaxX;
	// ���� Y = index�� �ִ� x������ŭ�� �� �� ä������
	UINT iCurY = (m_iIndex / iMaxX) % iMaxY;

	fPoint rendPos = rendPos(getPos());
	fPoint size = getSize();

	BitBlt(hDC,
		(int)(rendPos.x),
		(int)(rendPos.y),
		(int)(size.x),
		(int)(size.y),
		m_pTex->getDC(),
		(int)(iCurX * SIZE_TILE),
		(int)(iCurY * SIZE_TILE),
		SRCCOPY);

}

void CTile::setTexture(CTexture* pTex)
{
	m_pTex = pTex;
}

void CTile::setImageIndex(UINT idx)
{
	m_iIndex = idx;
}

void CTile::save(FILE* pFile)
{
	fwrite(&m_iIndex, sizeof(int), 1, pFile);
}

void CTile::load(FILE* pFile)
{
	fread(&m_iIndex, sizeof(int), 1, pFile);
}
