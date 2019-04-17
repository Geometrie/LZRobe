#ifndef CPOOL_H
#define CPOOL_H
#include <string.h>
#include "CGameBase.h"
template <typename T>
class CPool
{
public:
	CPool()
	{
		m_lptData = NULL;
	}
	void init(int nCapicity)
	{
		m_lptData = new T[nCapicity];
		m_lptEnd = m_lptData + nCapicity;
		m_lptFirstEmpty = m_lptData;
	}
	void release()
	{
		if (m_lptData != NULL)
		{
			delete[]m_lptData;
			m_lptData = NULL;
		}
	}
	T* m_fnApplySpace(int nLen)
	{
		int iAcc;
		T *lptVisitor, *lptResult, *lptSearchEnd;
		lptSearchEnd = m_lptEnd - nLen + 1;
		lptVisitor = m_lptData;
		lptResult = NULL;
		iAcc = 0;
		if (m_lptFirstEmpty < lptSearchEnd)
		{
			for (lptVisitor = m_lptFirstEmpty; (lptVisitor != lptSearchEnd && (lptResult == NULL)); ++lptVisitor)
			{
				if (lptVisitor->empty())
				{
					++iAcc;
				}
				else
				{
					iAcc = 0;
				}
				if (iAcc == nLen)
				{
					lptResult = lptVisitor - (nLen - 1);
				}
				++lptVisitor;
			}
		}
		return lptResult;
	}
	T* m_fnWriteData(T *lptData, int nLen)
	{
		T *lptPosition;
		lptPosition = m_fnApplySpace(nLen);
		if (lptPosition != NULL)
		{
			memcpy(lptPosition, lptData, nLen * sizeof(T));
			if (m_lptFirstEmpty == lptPosition + nLen)
			{
				while (m_lptFirstEmpty != m_lptEnd && !m_lptFirstEmpty->empty())
				{
					++m_lptFirstEmpty;
				}
			}
		}
		return lptPosition;
	}
	void m_fnDropData(T *lptPosition, int nLen)
	{
		T *lptVisitor, *lptEnd;
		lptEnd = lptPosition + nLen;
		for (lptVisitor = lptPosition; lptVisitor != lptEnd; ++lptVisitor)
		{
			lptVisitor->release();
		}
		if (lptPosition < m_lptFirstEmpty)
		{
			m_lptFirstEmpty = lptPosition;
		}
	}
	~CPool()
	{
		release();
	}
	void m_fnClear()
	{
		T *lptVisitor;
		for (lptVisitor = m_lptData; lptVisitor != m_lptEnd; ++lptVisitor)
		{
			lptVisitor->release();
		}
		m_lptFirstEmpty = m_lptData;
	}
private:
	T *m_lptData, *m_lptEnd, *m_lptFirstEmpty;
};
#endif
