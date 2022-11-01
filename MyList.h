#pragma once

template<typename T>
struct tListNode
{
	T data;
	tListNode<T>* pPrev;
	tListNode<T>* pNext;

	tListNode()
		: data()
		, pPrev(nullptr)
		, pNext(nullptr)
	{
	}

	tListNode(const T& _data, tListNode<T>* _pPrev, tListNode<T>* _pNext)
		: data(_data)
		, pPrev(_pPrev)
		, pNext(_pNext)
	{
	}

	~tListNode()
	{
	}
};

template<typename T>
class MyList
{
private:
	tListNode<T>* m_pHead;
	tListNode<T>* m_pTail;
	int m_iCount;

public:
	void push_back(const T& _data);
	void push_front(const T& _data);

	int size() { return m_iCount; }

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator erase(iterator& _iter);
	iterator insert(const iterator& _iter, const T& _data);

public:
	MyList()
		: m_pHead(nullptr)
		, m_pTail(nullptr)
		, m_iCount(0)
	{

	}

	~MyList()
	{
		tListNode<T>* pDeleteNode = m_pHead; 

		while (pDeleteNode)
		{
			tListNode<T>* pNode = pDeleteNode->pNext;
			delete pDeleteNode;
			pDeleteNode = pNode;
		}
	}

	class iterator
	{
	private:
		MyList<T>* m_pList;
		tListNode<T>* m_pNode;
		bool m_bValid;

	public:
		T& operator* ()
		{
			return m_pNode->data;
		}

		bool operator == (const iterator& _otheriter)
		{
			if (m_pList == _otheriter.m_pList && m_pNode == _otheriter.m_pNode)
			{
				return true;
			}
			return false;
		}

		bool operator != (const iterator& _otheriter)
		{
			return !(*this == _otheriter);
		}

		iterator& operator ++()
		{
			//end에서 ++한경우
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}

			m_pNode = m_pNode->pNext;

			return *this;
		}

		iterator operator ++(int)
		{
			iterator copyiter = (*this);
			++(*this);
			return copyiter;
		}

		iterator& operator --()
		{
			if (nullptr == m_pNode || !m_bValid)
			{
				assert(nullptr);
			}

			m_pNode = m_pNode->pPrev;

			return *this;
		}

		iterator operator --(int)
		{
			iterator copyiter = (*this);
			--(*this);
			return copyiter;
		}

	public:
		iterator()
			:m_pList(nullptr)
			, m_pNode(nullptr)
			, m_bValid(false)
		{}

		iterator(MyList<T>* _pList, tListNode<T>* _pNode)
			:m_pList(_pList)
			, m_pNode(_pNode)
		{
			if (nullptr != _pList && nullptr != _pNode)
			{
				m_bValid = true;
			}
		}

		~iterator()
		{}

		friend class MyList;
	};
};

template<typename T>
inline void MyList<T>::push_back(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, nullptr);

	if (m_pHead == nullptr)
	{
		m_pHead = pNewNode;
		m_pTail = pNewNode;
	}
	else
	{
		m_pTail->pNext = pNewNode;
		pNewNode->pPrev = m_pTail;
		m_pTail = pNewNode;
	}

	++m_iCount;
}

template<typename T>
inline void MyList<T>::push_front(const T& _data)
{
	tListNode<T>* pNewNode = new tListNode<T>(_data, nullptr, m_pHead);

	m_pHead->pPrev = pNewNode;

	m_pHead = pNewNode;

	++m_iCount;
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::begin()
{
	return iterator(this, m_pHead);
}

template<typename T>
inline  typename MyList<T>::iterator MyList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::erase(iterator& _iter)
{
	return iterator();
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::insert(const iterator& _iter, const T& _data)
{
	//예외처리1
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//리스트에 추기되는 데이터를 저장할 노드 생성
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	//예외처리2 : iterator가 가르키는 노드가 해드노드인 경우
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;

		m_pHead = pNode;
	}
	else
	{
		//iterator가 가르키고있는 노드의 이전으로 가서 다음노드 주소파트를 새로 생성한 노드로 지정
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;
		//iterator가 가르키고 있는 노드의 이전을 새로운 노드로 지정
		//새로운 노드의 pNext를 iterator가 가리키고있는 노드로 지정
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
	}

	//카운트 증가
	++m_iCount;

	return iterator(this, pNode);
}

