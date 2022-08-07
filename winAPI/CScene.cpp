#include "framework.h"
#include "CScene.h"
#include "CTile.h"

CScene::CScene()
{
	m_strName = L"";

	m_uiTileX = 0;
	m_uiTileY = 0;
}
CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)eOBJ::SIZE; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
			delete m_arrObj[i][j];
	}
}

void CScene::setName(const wstring& strName)
{
	m_strName = strName;
}

wstring CScene::getName()
{
	return m_strName;
}

UINT CScene::getTileX()
{
	return m_uiTileX;
}

UINT CScene::getTileY()
{
	return m_uiTileY;
}

void CScene::addObject(CObject* pObj, eOBJ objType)
{
	m_arrObj[(UINT)objType].push_back(pObj);
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)eOBJ::SIZE; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->isDead())					// 유예 중이면 업데이트 x
				m_arrObj[i][j]->update();
		}
	}
}

void CScene::finalUpdate()
{
	for (UINT i = 0; i < (UINT)eOBJ::SIZE; i++)
	{
		for (UINT j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->finalUpdate();
		}
	}

	//for (UINT i = 0; i < m_arrObj[(UINT)eOBJ::PLAYER].size(); i++)
	//{	// 플레이어 이전좌표 갱신용
	//	m_arrObj[(UINT)eOBJ::PLAYER][i]->finalUpdate();
	//}
}

void CScene::render(HDC hDC)
{
	for (UINT i = 0; i < (UINT)eOBJ::SIZE; i++)
	{
		if ((UINT)eOBJ::TILE == i)
		{
			renderTile(hDC);
			continue;
		}

		for (vector<CObject*>::iterator iter = m_arrObj[i].begin(); iter != m_arrObj[i].end();)
		{
			if (!(*iter)->isDead())
				(*iter++)->render(hDC);
			else										// 유예 중이면 erase
				iter = m_arrObj[i].erase(iter);
		}
	}
}

void CScene::renderTile(HDC hDC)
{
	const vector<CObject*>& vecTile = getGroupObject(eOBJ::TILE);

	fPoint fptCamLook = CCameraManager::getInst()->getFocus();
	fPoint fptLeftTop = fptCamLook - fPoint(WINSIZEX, WINSIZEY) * 0.5f;

	int iLTCol = (int)fptLeftTop.x / CTile::SIZE_TILE;
	int iLTRow = (int)fptLeftTop.y / CTile::SIZE_TILE;
	int iLTIdx = m_uiTileX * iLTRow + iLTCol;

	int iClientWidth = (int)WINSIZEX / CTile::SIZE_TILE;
	int iClientHeight = (int)WINSIZEY / CTile::SIZE_TILE;
	for (int iCurRow = iLTRow; iCurRow <= (iLTRow + iClientHeight); ++iCurRow)
	{
		for (int iCurCol = iLTCol; iCurCol <= (iLTCol + iClientWidth); ++iCurCol)
		{
			if (iCurCol < 0 || (int)m_uiTileX <= iCurCol ||
				iCurRow < 0 || (int)m_uiTileY <= iCurRow)
				continue;

			int iIdx = (m_uiTileX * iCurRow) + iCurCol;

			vecTile[iIdx]->render(hDC);
		}
	}
}

const vector<CObject*>& CScene::getGroupObject(eOBJ group)
{
	return m_arrObj[(UINT)group];
}

vector<CObject*>& CScene::getUIGroup()
{
	return m_arrObj[(UINT)eOBJ::UI];
}

void CScene::deleteObjectGroup(eOBJ objGroup)
{
	for (UINT i = 0; i < m_arrObj[(UINT)objGroup].size(); i++)
		delete m_arrObj[(UINT)objGroup][i];

	m_arrObj[(UINT)objGroup].clear();
}

void CScene::deleteObjectAll()
{
	CGameManager::getInst()->unRegistPlayer();		// 오브젝트 모두 지울 때 gameMgr에 등록된 플레이어도 리셋

	for (UINT i = 0; i < (UINT)eOBJ::SIZE; i++)
		deleteObjectGroup((eOBJ)i);
}

void CScene::createTile(UINT xSize, UINT ySize)
{
	deleteObjectGroup(eOBJ::TILE);

	m_uiTileX = xSize;
	m_uiTileY = ySize;

	CTexture* pTex = loadTex(L"Tile", L"map\\testTile.bmp");

	for (UINT i = 0; i < ySize; i++)
	{
		for (UINT j = 0; j < xSize; j++)
		{
			CTile* pTile = new CTile();
			pTile->setPos(fPoint((float)(j * CTile::SIZE_TILE), (float)(i * CTile::SIZE_TILE)));
			pTile->setTexture(pTex);
			addObject(pTile, eOBJ::TILE);
		}
	}
}

void CScene::loadTile(const wstring& strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // r : read, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;

	// save했던 x,y순서대로 해야 함
	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	createTile(xCount, yCount);

	// 
	const vector<CObject*>& vecTile = getGroupObject(eOBJ::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
		((CTile*)vecTile[i])->load(pFile);

	fclose(pFile);
}
