/*
## 分配器allocator
- 分配器用于实现容器算法时，将其与存储细节隔离从而解耦合。
- 分配器提供存储分配与释放的标准方法
- 对象内存分配和构造分离

std::allocator
address (C++17 中弃用)(C++20 中移除)
allocate 分配未初始化的存储
deallocate 解分配存储
max_size(C++17 中弃用)(C++20 中移除)
construct (C++17 中弃用)(C++20 中移除)
destroy(C++17 中弃用)(C++20 中移除)
*/

#include <iostream>
using namespace std;
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
};
int main(int argc, char *argv[])
{
	allocator<XData> xdata_allco;
	int size = 3;

	//分配对象空间 不调用构造
	auto dataarr = xdata_allco.allocate(size);

	for (int i = 0; i < size; i++)
	{
		//allocator_traits 类模板提供访问分配器 (Allocator) 各种属性的标准化方式
		//allocator_traits< allocator<XData> >

		//调用构造
		allocator_traits< decltype(xdata_allco)>::construct(xdata_allco, &dataarr[i]);

		//调用析构函数
		allocator_traits< decltype(xdata_allco)>::destroy(xdata_allco, &dataarr[i]);
	}

	//释放对象内存 不调用析构
	xdata_allco.deallocate(dataarr, size);

	return 0;
}