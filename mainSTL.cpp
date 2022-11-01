#include <iostream>

#include "Myvactor.h"
#include "MyList.h"


int main()
{
	MyList<int> list;
	Myvactor<int> vac;

	for (int i = 0; i < 4; ++i)
	{
		list.push_back(i);
	}

	vac.PushBack(100);
	vac.PushBack(200);
	vac.PushBack(300);
	vac.PushBack(400);
	vac.PushBack(500);
	vac.PushBack(600);
	Myvactor<int>::iterator vaciter = vac.begin();
	vaciter = vac.erase(++vaciter);
	vaciter = vac.begin();

	for (vaciter = vac.begin(); vaciter != vac.end(); ++vaciter)
	{
		std::cout << *vaciter << std::endl;
	}
	
	//배열 클리어
	vac.clear();

	//값입력
	for (int i = 0; i < 11; ++i)
	{
		vac.PushBack(i+1);
	}
	vaciter = vac.begin();
	//짝수만 제거
	/*for (; vaciter != vac.end(); ++vaciter)
	{
		if (0 == *vaciter % 2)
		{
			vaciter = vac.erase(vaciter);
		}
	}*/
	//1~5숫자제거
	for (; vaciter != vac.end();)
	{
		if (1 <= *vaciter && *vaciter <= 5)
		{
			vaciter = vac.erase(vaciter);
		}
		else
		{
			++vaciter;
		}
	}
	//출력
	for (int i = 0; i < vac.size(); ++i)
	{
		std::cout << vac[i] << std::endl;
	}


	////////////////////////////////////////////
	MyList<int> mylist;
	mylist.push_back(100);
	mylist.push_back(300);
	mylist.push_back(400);

	MyList<int>::iterator listiter = mylist.begin();
	++listiter;
	listiter = mylist.insert(listiter, 200);

	std::cout << "===================" << std::endl;
	std::cout << "List iterator test!" << std::endl;
	std::cout << "==================" << std::endl;
	for (listiter = mylist.begin(); listiter != mylist.end(); ++listiter)
	{
		std::cout << *listiter << std::endl;
	}
	


	return 0;
}