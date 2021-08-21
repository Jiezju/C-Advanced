/*
### 重载局部的new和delete
- 类内重载函数（封装）
### 放置placement new和delete,new的空间指向已有的地址中
- 普通new申请空间是从堆中分配空间，
一些特殊的需求要在已分配的空间中创建对象，
就可以使用放置placement new 操作
- placement new生成对象既可以在栈上，也可以在堆上
- placement new生成对象销毁要手动调用析构函数
- 实现了 分配与构造 的分离
	- 外部 在栈上或 堆上进行内存分配大块内存
	- 通过分配的指针在该大块内存上进行类的构造
- placement new的原理流程
	- 申请数据内存，首地址指针ptr
	- new(ptr) 将ptr转为void* 指针
	- 使用void* 的内存 申请class 内存
*/

#include <iostream>

class exData
{
public:
	// 单个类的定义需要8个字节
	int index = 0;
	int data = 0;
	exData()
	{
		std::cout << "Create exData" << std::endl;
	}
	~exData()
	{
		std::cout << "Drop exData" << std::endl;
	}

	/* 类内重载 new */
	void* operator new (size_t size)
	{
		std::cout << "exData new " << size << std::endl;
		auto mem = malloc(size);
		if (!mem)
		{
			throw std::bad_alloc();
		}
		return mem;
	}

	void* operator new [](size_t size)
	{
		std::cout << "exData new []" << size << std::endl;
		auto mem = malloc(size);
		if (!mem)
		{
			throw std::bad_alloc();
		}
		return mem;
	}

	/* 类内重载 delete */
	void operator delete(void* ptr)
	{
		std::cout << "exData operator delete" << std::endl;
		std::free(ptr);
	}
	void operator delete[](void* ptr)
	{
		std::cout << "exData operator delete[]" << std::endl;
		std::free(ptr);
	}

	//placement new 由外部传入内存指针
	void* operator new (size_t size, void* ptr)
	{
		std::cout << "placement new" << std::endl;
		return ptr;
	}

	void* operator new [](size_t size, void* ptr)
	{
		std::cout << "placement new" << std::endl;
		return ptr;
	}
};

int main(int argc, char *argv[])
{
	/* ex1. 栈上内存的 placement new */
	int buf1[1024] = { 0 };
	exData* mem2 = ::new(buf1) exData;
	std::cout << "buf1 addr:" << buf1 << std::endl;
	std::cout << "mem2 addr:" << mem2 << std::endl;
	// 栈上内存 自然销毁，不需要delete
	mem2->~exData();

	/* ex2. 栈上内存的 标准 new [] */
	int* buf2 = new int[1024]{ 0 };
	auto mem3 = ::new(buf2) exData[2]; // 在buf2 上创建2个exData对象
	std::cout << "buf3 addr:" << buf2 << std::endl;
	std::cout << "mem4 addr:" << mem3 << std::endl;
	delete [] mem3;
	// 不能delete buf2 因为 mem3 和 buf2

	/* ex3. 栈上内存的 类重载 new */
	int* buf3 = new int[1024]{0};
	auto mem4 = new(buf3) exData;
	std::cout << "buf3 addr:" << buf3 << std::endl;
	std::cout << "mem4 addr:" << mem4 << std::endl;
	mem4->~exData();
	delete[] buf3;

	/* ex4. 栈上内存的 类重载 new [] */
	int* buf4 = new int[1024]{ 0 };
	auto mem5 = new(buf4) exData[12];
	std::cout << "buf3 addr:" << buf4 << std::endl;
	std::cout << "mem4 addr:" << mem5 << std::endl;
	for (int i=0; i<12; ++i)
	{
		mem5->~exData();
		mem5++;
	}
	
	delete[] buf4;


	return 0;
}
