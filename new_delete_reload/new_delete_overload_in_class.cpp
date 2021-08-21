/*
### ���ؾֲ���new��delete
- �������غ�������װ��
### ����placement new��delete,new�Ŀռ�ָ�����еĵ�ַ��
- ��ͨnew����ռ��ǴӶ��з���ռ䣬
һЩ���������Ҫ���ѷ���Ŀռ��д�������
�Ϳ���ʹ�÷���placement new ����
- placement new���ɶ���ȿ�����ջ�ϣ�Ҳ�����ڶ���
- placement new���ɶ�������Ҫ�ֶ�������������
- ʵ���� �����빹�� �ķ���
	- �ⲿ ��ջ�ϻ� ���Ͻ����ڴ�������ڴ�
	- ͨ�������ָ���ڸô���ڴ��Ͻ�����Ĺ���
- placement new��ԭ������
	- ���������ڴ棬�׵�ַָ��ptr
	- new(ptr) ��ptrתΪvoid* ָ��
	- ʹ��void* ���ڴ� ����class �ڴ�
*/

#include <iostream>

class exData
{
public:
	// ������Ķ�����Ҫ8���ֽ�
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

	/* �������� new */
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

	/* �������� delete */
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

	//placement new ���ⲿ�����ڴ�ָ��
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
	/* ex1. ջ���ڴ�� placement new */
	int buf1[1024] = { 0 };
	exData* mem2 = ::new(buf1) exData;
	std::cout << "buf1 addr:" << buf1 << std::endl;
	std::cout << "mem2 addr:" << mem2 << std::endl;
	// ջ���ڴ� ��Ȼ���٣�����Ҫdelete
	mem2->~exData();

	/* ex2. ջ���ڴ�� ��׼ new [] */
	int* buf2 = new int[1024]{ 0 };
	auto mem3 = ::new(buf2) exData[2]; // ��buf2 �ϴ���2��exData����
	std::cout << "buf3 addr:" << buf2 << std::endl;
	std::cout << "mem4 addr:" << mem3 << std::endl;
	delete [] mem3;
	// ����delete buf2 ��Ϊ mem3 �� buf2

	/* ex3. ջ���ڴ�� ������ new */
	int* buf3 = new int[1024]{0};
	auto mem4 = new(buf3) exData;
	std::cout << "buf3 addr:" << buf3 << std::endl;
	std::cout << "mem4 addr:" << mem4 << std::endl;
	mem4->~exData();
	delete[] buf3;

	/* ex4. ջ���ڴ�� ������ new [] */
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
