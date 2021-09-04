/*
## 虚函数表 vfptr_table 的作用
- 当子类作为父类指针调用继承方法时，保存的子类函数指针，
  使子类能够正确调用自己的方法而不是父类的方法

- 要使用虚函数表就必须将继承父类的方法声明为 virtual

- 虚函数表仅仅产生类中，为所有类的对象所共有，
  不需要为每个对象都构建一个虚函数表

- 虚函数表是一个指针数组中存储的是 virtual 方法的函数地址

*/

#include <iostream>
using namespace std;

//虚函数表分析
class Base
{
public:
	// 子类继承的父类方法必须加上 virtual 声明
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
