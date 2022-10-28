class cTest
{
private:

public:
	int m_i;

public:
	//1.클래스간에 대입이 발생하면 자동으로 만들어 진다. 그래서 클래스 끼리 대입이 발생할 수 있었다.
	cTest& operator = (const cTest& _other)
	{
		m_i = _other.m_i;
		return *this;
	}

public:
	//기본생성자
	cTest()
		: m_i(0)
	{

	}

	//2.복사 생성자
	cTest(const cTest& _other) //구현하지 않아도 자동으로 구현, 구현하면 cpp컴파일은 자동으로 구현해주지 않음
		: m_i(_other.m_i)      // 이것을 문제 없이 하려면 기본생성자 만들어 줘야한다(cpp파일 오류)
	{
	}

};





////cpp파일///////////

#include <iostream>

int main()
{
	cTest t1, t2;
	t1 = t2; //1.번이 가능

	//2번
	cTest ta1;
	ta1.m_i = 100;

	cTest ta2; //이걸 아래와 같이 해도된다
	ta2 = ta1; 
	cTest ta2(ta1); //이렇게
					//복사생성자는 객체생성과 대입을 동시에 한다.
	cTest ta3 = ta1;//객체가 생성됨과 동시에 대입을 받으면 컴파일러는 다음과 같이 복사 생성자 호출로 바꿔준다. cTest ta3(ta1);
}