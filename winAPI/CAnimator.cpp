#include "framework.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pCurAni = nullptr;
	m_pOwner = nullptr;
}

CAnimator::~CAnimator()
{
	for (map<wstring, CAnimation*>::iterator iter = m_mapAni.begin();
		iter != m_mapAni.end(); iter++)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}

	m_mapAni.clear();
}

CObject* CAnimator::getOwner()
{
	return m_pOwner;
}

void CAnimator::update()
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->update();
	}
}

void CAnimator::render(HDC hDC)
{
	if (nullptr != m_pCurAni)
	{
		m_pCurAni->render(hDC);
	}
}

void CAnimator::createAnimation(const wstring& strName, CTexture* pTex, fPoint leftTop, fPoint slice,
	fPoint step, float dura, UINT frmCnt, bool isRepeat)
{
	CAnimation* pAni = findAnimation(strName);

	assert(nullptr == pAni);		// 이미 있는 경우 

	pAni = new CAnimation;

	pAni->setName(strName);
	pAni->m_pAnimator = this;
	pAni->create(pTex, leftTop, slice, step, dura, frmCnt, isRepeat);

	m_mapAni.insert(make_pair(strName, pAni));
}

CAnimation* CAnimator::findAnimation(const wstring& strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAni.find(strName);

	if (iter == m_mapAni.end())
		return nullptr;

	return iter->second;
}

void CAnimator::play(const wstring& strName)
{	// 같은 애니메이션 재생하는 경우 아니면 이전 프레임 0으로 해둠
	CAnimation* pNextAni = findAnimation(strName);

	if (pNextAni != m_pCurAni)
	{
		if (nullptr != m_pCurAni)
		{
			m_pCurAni->setFrame(0);
		}
	}
	m_pCurAni = pNextAni;
}
