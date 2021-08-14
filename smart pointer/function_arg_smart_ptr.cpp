/*

# 智能指针作为函数参数传递
- unique_ptr 指针传入，不允许拷贝构造，需要move
- unique_ptr 指针传出，直接移动move 传出
*/
#include <iostream>
using namespace std;

//智能指针作为函数参数和返回值
class XData
{
public:
	XData()
	{
		cout << "Create XData" << endl;
	}
	~XData()
	{
		cout << "Drop XData" << endl;
	}
	int index = 0;
};
unique_ptr<XData> TestUnique(unique_ptr<XData> ptr)
{
	cout << "ptr->index=" << ptr->index << endl;
	unique_ptr<XData> re(new XData);
	re->index = 222;
	// 编译器优化 1 如果返回值支持move 编译器自动调用move,不支持调用拷贝构造
	return re;
}

int main()
{
	{
		unique_ptr<XData> ptr1(new XData);
		ptr1->index = 111;
		cout << "ptr1->index=" << ptr1->index << endl;
		auto re = TestUnique(move(ptr1));
		cout << "re->index=" << re->index << endl;
		if (!ptr1)
		{
			cout << "ptr1 empty" << endl;
		}
		else
		{
			cout << "ptr1->index=" << ptr1->index << endl;
		}
	}
	return 0;
}
