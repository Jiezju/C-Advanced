#include <iostream>
using namespace std;

//�麯�������
class B
{
public:
	virtual void Test1()
	{
		cout << "B test1" << endl;
	}
	virtual void Test2()
	{
		cout << "B test2" << endl;
	}
};
class A :public B
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
class C :public B
{
	void Test1()
	{
		cout << "C test1" << endl;
	}
	void Test2()
	{
		cout << "C test2" << endl;
	}
};
void TestClass(B* b)
{
	cout << "in TestClass" << endl;
	b->Test1();
}
int main()
{
	//�����麯����ֻ������֤ԭ�����ɹ��̻�

	{
		A a1;
		A a2;
		//�麯�����ָ��
		int* vftable1 = nullptr;
		vftable1 = (int*)(*((int*)&a1));
		int *vftable2 = (int*)(*((int*)&a2));

		//ͬһ����Ĳ�ͬ�����麯����ָ��ͬһ��
		cout << "a1 = " << (long long)&a1 << endl;
		cout << "vftable1 = " << (long long)vftable1 << endl;

		cout << "a2 = " << (long long)&a2 << endl;
		cout << "vftable2 = " << (long long)vftable2 << endl;

		// ���庯��ָ��
		typedef void(*VFunc)();

		auto test1 = (VFunc)vftable1[0];
		auto test2 = (VFunc)vftable1[1];
		test1();
		test2();

	}

	return 0;
}