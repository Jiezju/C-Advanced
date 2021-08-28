/*
 * 限制栈中创建对象，限制调用delete销毁对象
 * 
 */

#include <iostream>
using namespace std;

class TestMem
{
public:
	static TestMem* Create()
	{
		cout << "static Create " << endl;
		return new TestMem();
	}
	static void Drop(TestMem* tm)
	{
		cout << "static Drop" << endl;
		delete tm;
	}
protected:

	// 不允许外部访问，则无法使用默认构造函数构造
	TestMem()
	{
		cout << "Create TestMem" << endl;
	}
	// 不允许外部访问，则无法使用默认析构函数构造
	virtual ~TestMem()
	{
		cout << "Drop TestMem" << endl;
	}
};

int main()
{

	//  限制栈中创建对象，限制调用delete销毁对象
	//TestMem tm1;
	//auto tm2 = new TestMem();
	TestMem *tm3 = TestMem::Create();
	//delete tm3;
	TestMem::Drop(tm3);

	return 0;
}