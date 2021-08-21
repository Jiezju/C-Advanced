/*
## 重载new和delete
### 为什么要重载
- 监测内存创建销毁 ，统计和监控泄漏
- 内存对齐的处理
- 特定应用：例如多进程内存共享
### 重载全局的new和delete
- 则使用new和delete会优先使用custom的重载函数
*/

#include <iostream>

/*
 * 重载全局的new 以及 new []
 * 内部调用 c malloc 接口
 */
void* operator new(size_t size)
{
	std::cout << "operator new :" << size << std::endl;
	auto mem = malloc(size);
	if (!mem)
	{
		throw std::bad_alloc();
	}
	return mem;
}

void* operator new [](size_t size)
{
	std::cout << "operator new [] :" << size << std::endl;
	auto mem = malloc(size);
	if (!mem)
	{
		throw std::bad_alloc();
	}
	return mem;
}

/*
 * 重载全局的delete 以及 delete []
 * 内部调用 c free 接口
 */

void operator delete(void* ptr)
{
	std::cout << "operator delete" << std::endl;
	std::free(ptr);
}

void operator delete[](void* ptr)
{
	std::cout << "operator delete[]" << std::endl;
	std::free(ptr);
}

/*
 * 测试demo
 */

// 自定义数据类型（class）
class exData
{
public:
	int index = 0;
	exData()
	{
		std::cout << "Create exData" << std::endl;
	}
	
	~exData()
	{
		std::cout << "Drop exData" << std::endl;
	}
};

int main(int argc, char *argv[])
{
	/* ex1. 固有数据类型的 new 与 delete */
	int* i = new int;
	delete i;

	/* ex2. class数据类型的 new 与 delete */
	auto mem1 = new exData();
	delete mem1;

	/* ex3. 固有数据类型的 new [] 与 delete [] */
	int* arr = new int[1024];
	delete[] arr;

	/* ex4. class数据类型的 new [] 与 delete []*/
	exData* exDatas = new exData[2];
	delete[] exDatas;

	/* ex4. 使用 C++ 默认 new */
	// 全局的new运算符被重载，无法再次使用

	return 0;
}
