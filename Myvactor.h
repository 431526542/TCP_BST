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

	class iterator; //전방선언
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
		Myvactor* m_pVac; //iterator가리키는 데이터를 관리하는 가변배열 주소
		T* m_pData;
		int m_iIdx;
		bool m_bValid;

	public:
		T& operator *()
		{
			//iterator가 알고있는 주소와 가변배열이 알고 있는 주소가 같은지 확인
			//iterator가 end iterator일 경우
			if (m_pVac->m_iData != m_pData || -1==m_iIdx || false == m_bValid)
			{
				assert(nullptr);
			}
			return m_pData[m_iIdx];
		}

		//++ 전위
		iterator& operator ++()
		{
			//<예외처리>
			//end iterator인 경우
			//iterator가 알고있는 주소와 가변배열이 알고 있는 주소가 같지 않은 경우
			if (m_pVac->m_iData != m_pData || -1 == m_iIdx)
			{
				assert(nullptr);
			}

			//iterator가 마지막 데이터를 가리키고 있는 경우
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
		//++ 후위
		iterator operator ++(int) //++(int)이런 방식이 컴파일러가 후위 연산자라고 인식한다.
		{
			iterator copy_iter = *this;
			++(*this);
			return copy_iter;
		}

		//-- 전위
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
		//-- 후위
		iterator operator --(int) //++(int)이런 방식이 컴파일러가 후위 연산자라고 인식한다.
		{
			iterator copy_iter = *this;
			--(*this);
			return copy_iter;
		}

		//비교연산자 ==, !=
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

		friend class Myvactor; //paivate 공유 가능
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
typename Myvactor<T>::iterator Myvactor<T>::begin() //typename을 적어준 이유는 Myvactor<T>::iterator즉, 반환타입이 iterator 클래스안에 선언된 iterator가 특정 타입이라는 것을 알려주기 위함
{
	if (m_iCount == 0)
	{
		return iterator(this, m_iData, -1); //데이터가 없는 경우 begin() = end()
	}
	else
	{
		//시작을 가리키는 iterator를 만들어서 반환해줌
		return iterator(this, m_iData, 0); //iterator(this, m_iData, 0);에서 this는 본인 가변배열 함수이기 때문에 this를 사용한다.
	}
}

template<typename T>
typename Myvactor<T>::iterator Myvactor<T>::end() //typename을 적어준 이유는 Myvactor<T>::iterator즉, 반환타입이 iterator 클래스안에 선언된 iterator가 특정 타입이라는 것을 알려주기 위함
{
	return iterator(this, m_iData, -1);
}

template<typename T>
inline typename Myvactor<T>::iterator Myvactor<T>::erase(iterator& _iter)
{
	//iterator가 다른 가변배열쪽 요소를 가르키는 경우
	//iterator가 end iterator 인경우
	//iterator의 m_iIdx가 m_iCount보다 클경우
	if (this != _iter.m_pVac || end() == _iter || m_iCount <= _iter.m_iIdx)
	{
		assert(nullptr);
	}

	//iterator가 가르키는 데이터를 배열내에서 제거
	int iLoopCount = m_iCount - (_iter.m_iIdx + 1);
	
	for (int i = 0; i < iLoopCount; ++i)
	{
		m_iData[i + _iter.m_iIdx] = m_iData[i + _iter.m_iIdx + 1];
	}

	//유효여부 체크
	_iter.m_bValid = false;

	//카운트 감소
	--m_iCount;

	return iterator(this, m_iData, _iter.m_iIdx);
}
