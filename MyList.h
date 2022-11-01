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
			//end���� ++�Ѱ��
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
	//����ó��1
	if (end() == _iter)
	{
		assert(nullptr);
	}

	//����Ʈ�� �߱�Ǵ� �����͸� ������ ��� ����
	tListNode<T>* pNode = new tListNode<T>(_data, nullptr, nullptr);

	//����ó��2 : iterator�� ����Ű�� ��尡 �ص����� ���
	if (_iter.m_pNode == m_pHead)
	{
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;

		m_pHead = pNode;
	}
	else
	{
		//iterator�� ����Ű���ִ� ����� �������� ���� ������� �ּ���Ʈ�� ���� ������ ���� ����
		_iter.m_pNode->pPrev->pNext = pNode;
		pNode->pPrev = _iter.m_pNode->pPrev;
		//iterator�� ����Ű�� �ִ� ����� ������ ���ο� ���� ����
		//���ο� ����� pNext�� iterator�� ����Ű���ִ� ���� ����
		_iter.m_pNode->pPrev = pNode;
		pNode->pNext = _iter.m_pNode;
	}

	//ī��Ʈ ����
	++m_iCount;

	return iterator(this, pNode);
}

