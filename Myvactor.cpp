#include "Myvactor.h"
#include <assert.h>

void Myvactor::PushBack(int _data)
{
	if (m_iMaxCount <= m_iCount)
	{
		resize(m_iMaxCount * 2);
	}

	m_iData[m_iCount++] = _data;
}

void Myvactor::resize(int _iDataCount)
{
	if (m_iMaxCount >= _iDataCount)
	{
		assert(nullptr);
	}

	int* pNew = new int[_iDataCount];
	
	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_iData[i];
	}

	delete[] m_iData;

	m_iData = pNew;

	m_iMaxCount = _iDataCount;

}

int& Myvactor::operator[](int idx)
{
	return m_iData[idx];
}
