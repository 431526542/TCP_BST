#pragma once
#include <assert.h>

template<typename T>
class Myvactor
{
private:
	T* m_iData;
	int m_iCount;
	int m_iMaxCount;

public:
	void PushBack(const T& _data);
	void resize(int _iDataCount);

	T& operator[] (int idx);
	T* data() { return m_iData; }
	int size() { return m_iCount; }
	int capacity() { return m_iMaxCount; }
	void clear() { m_iCount = 0; }

	class iterator; //���漱��
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);

public:
	Myvactor<T>()
		: m_iData(nullptr)
		, m_iCount(0)
		, m_iMaxCount(2)
	{
		m_iData = new T[2];
	}

	~Myvactor<T>()
	{
		delete[] m_iData;
		m_iCount = 0;
		m_iMaxCount = 0;
	}

	class iterator
	{
	private:
		Myvactor* m_pVac; //iterator����Ű�� �����͸� �����ϴ� �����迭 �ּ�
		T* m_pData;
		int m_iIdx;
		bool m_bValid;

	public:
		T& operator *()
		{
			//iterator�� �˰��ִ� �ּҿ� �����迭�� �˰� �ִ� �ּҰ� ������ Ȯ��
			//iterator�� end iterator�� ���
			if (m_pVac->m_iData != m_pData || -1==m_iIdx || false == m_bValid)
			{
				assert(nullptr);
			}
			return m_pData[m_iIdx];
		}

		//++ ����
		iterator& operator ++()
		{
			//<����ó��>
			//end iterator�� ���
			//iterator�� �˰��ִ� �ּҿ� �����迭�� �˰� �ִ� �ּҰ� ���� ���� ���
			if (m_pVac->m_iData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//iterator�� ������ �����͸� ����Ű�� �ִ� ���
			if (m_pVac->size() - 1 == m_iIdx)
			{
				m_iIdx = -1;
			}
			else
			{
				++m_iIdx;
			}

			return *this;
		}
		//++ ����
		iterator operator ++(int) //++(int)�̷� ����� �����Ϸ��� ���� �����ڶ�� �ν��Ѵ�.
		{
			iterator copy_iter = *this;
			++(*this);
			return copy_iter;
		}

		//-- ����
		iterator& operator --()
		{
			if (m_pVac->m_iData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			if (m_pVac->size() == 0)
			{
				m_iIdx = -1;
			}
			else
			{
				--m_iIdx;
			}
			return *this;
		}
		//-- ����
		iterator operator --(int) //++(int)�̷� ����� �����Ϸ��� ���� �����ڶ�� �ν��Ѵ�.
		{
			iterator copy_iter = *this;
			--(*this);
			return copy_iter;
		}

		//�񱳿����� ==, !=
		bool operator == (const iterator& _otheriter)
		{
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
			{
				return true;
			}
			return false;
		}
		bool operator != (const iterator& _otheriter)
		{
			if (m_pData == _otheriter.m_pData && m_iIdx == _otheriter.m_iIdx)
			{
				return false;
			}
			return true;
		}


	public:
		iterator()
			: m_pVac(nullptr)
			, m_pData(nullptr)
			, m_iIdx(-1)
			, m_bValid(false)
		{
		}

		iterator(Myvactor* _Myvac, T* _pData, int _iIdx)
			: m_pVac(_Myvac)
			, m_pData(_pData)
			, m_iIdx(_iIdx)
			, m_bValid(false)
		{
			if (nullptr != m_pVac && 0 <= _iIdx)
			{
				m_bValid = true;
			}
		}

		~iterator()
		{

		}

		friend class Myvactor; //paivate ���� ����
	};

};

template<typename T>
void Myvactor<T>::PushBack(const T& _data)
{
	if (m_iMaxCount <= m_iCount)
	{
		resize(m_iMaxCount * 2);
	}

	m_iData[m_iCount++] = _data;
}

template<typename T>
void Myvactor<T>::resize(int _iDataCount)
{
	if (m_iMaxCount >= _iDataCount)
	{
		assert(nullptr);
	}

	T* pNew = new T[_iDataCount];

	for (int i = 0; i < m_iCount; ++i)
	{
		pNew[i] = m_iData[i];
	}

	delete[] m_iData;

	m_iData = pNew;

	m_iMaxCount = _iDataCount;

}

template<typename T>
T& Myvactor<T>::operator[](int idx)
{
	return m_iData[idx];
}

template<typename T>
typename Myvactor<T>::iterator Myvactor<T>::begin() //typename�� ������ ������ Myvactor<T>::iterator��, ��ȯŸ���� iterator Ŭ�����ȿ� ����� iterator�� Ư�� Ÿ���̶�� ���� �˷��ֱ� ����
{
	if (m_iCount == 0)
	{
		return iterator(this, m_iData, -1); //�����Ͱ� ���� ��� begin() = end()
	}
	else
	{
		//������ ����Ű�� iterator�� ���� ��ȯ����
		return iterator(this, m_iData, 0); //iterator(this, m_iData, 0);���� this�� ���� �����迭 �Լ��̱� ������ this�� ����Ѵ�.
	}
}

template<typename T>
typename Myvactor<T>::iterator Myvactor<T>::end() //typename�� ������ ������ Myvactor<T>::iterator��, ��ȯŸ���� iterator Ŭ�����ȿ� ����� iterator�� Ư�� Ÿ���̶�� ���� �˷��ֱ� ����
{
	return iterator(this, m_iData, -1);
}

template<typename T>
inline typename Myvactor<T>::iterator Myvactor<T>::erase(iterator& _iter)
{
	//iterator�� �ٸ� �����迭�� ��Ҹ� ����Ű�� ���
	//iterator�� end iterator �ΰ��
	//iterator�� m_iIdx�� m_iCount���� Ŭ���
	if (this != _iter.m_pVac || end() == _iter || m_iCount <= _iter.m_iIdx)
	{
		assert(nullptr);
	}

	//iterator�� ����Ű�� �����͸� �迭������ ����
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1);
	
	for (int i = 0; i < iLoopCount; ++i)
	{
		m_iData[i + _iter.m_iIdx] = m_iData[i + _iter.m_iIdx + 1];
	}

	//��ȿ���� üũ
	_iter.m_bValid = false;

	//ī��Ʈ ����
	--m_iCount;

	return iterator(this, m_iData, _iter.m_iIdx);
}
