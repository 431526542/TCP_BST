class cTest
{
private:

public:
	int m_i;

public:
	//1.Ŭ�������� ������ �߻��ϸ� �ڵ����� ����� ����. �׷��� Ŭ���� ���� ������ �߻��� �� �־���.
	cTest& operator = (const cTest& _other)
	{
		m_i = _other.m_i;
		return *this;
	}

public:
	//�⺻������
	cTest()
		: m_i(0)
	{

	}

	//2.���� ������
	cTest(const cTest& _other) //�������� �ʾƵ� �ڵ����� ����, �����ϸ� cpp�������� �ڵ����� ���������� ����
		: m_i(_other.m_i)      // �̰��� ���� ���� �Ϸ��� �⺻������ ����� ����Ѵ�(cpp���� ����)
	{
	}

};





////cpp����///////////

#include <iostream>

int main()
{
	cTest t1, t2;
	t1 = t2; //1.���� ����

	//2��
	cTest ta1;
	ta1.m_i = 100;

	cTest ta2; //�̰� �Ʒ��� ���� �ص��ȴ�
	ta2 = ta1; 
	cTest ta2(ta1); //�̷���
					//��������ڴ� ��ü������ ������ ���ÿ� �Ѵ�.
	cTest ta3 = ta1;//��ü�� �����ʰ� ���ÿ� ������ ������ �����Ϸ��� ������ ���� ���� ������ ȣ��� �ٲ��ش�. cTest ta3(ta1);
}