#include <iostream>
using namespace std;

//虚函数表分析
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
	//测试虚函数表，只用于验证原理，不可工程化

	{
		A a1;
		A a2;
		//虚函数表的指针
		int* vftable1 = nullptr;
		vftable1 = (int*)(*((int*)&a1));
		int *vftable2 = (int*)(*((int*)&a2));

		//同一个类的不同对象，虚函数表指向同一个
		cout << "a1 = " << (long long)&a1 << endl;
		cout << "vftable1 = " << (long long)vftable1 << endl;

		cout << "a2 = " << (long long)&a2 << endl;
		cout << "vftable2 = " << (long long)vftable2 << endl;

		// 定义函数指针
		typedef void(*VFunc)();

		auto test1 = (VFunc)vftable1[0];
		auto test2 = (VFunc)vftable1[1];
		test1();
		test2();

	}

	return 0;
}