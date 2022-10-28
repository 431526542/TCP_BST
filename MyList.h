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

