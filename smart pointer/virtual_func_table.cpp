/*
## �麯���� vfptr_table ������
- ��������Ϊ����ָ����ü̳з���ʱ����������ຯ��ָ�룬
  ʹ�����ܹ���ȷ�����Լ��ķ��������Ǹ���ķ���

- Ҫʹ���麯����ͱ��뽫�̳и���ķ�������Ϊ virtual

- �麯��������������У�Ϊ������Ķ��������У�
  ����ҪΪÿ�����󶼹���һ���麯����

- �麯������һ��ָ�������д洢���� virtual �����ĺ�����ַ

*/

#include <iostream>
using namespace std;

//�麯�������
class Base
{
public:
	// ����̳еĸ��෽��������� virtual ����
	virtual void Test1()
	{
		cout << "B test1" << endl;
	}
	virtual void Test2()
	{
		cout << "B test2" << endl;
	}
};
class A :public Base
{
public:
	void Test1()
	{
		cout << "A test1" << endl;
	}
	void Test2()
	{
		cout << "A test2" << endl;
	}
};


void TestClass(Base* b)
{
	cout << "in TestClass" << endl;
	b->Test1();
}
int main()
{
	Base b;
	b.Test1();
	A a;
	a.Test1();
	TestClass(&a);

	return 0;
}
