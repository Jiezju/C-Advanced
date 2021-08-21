/*
## ����new��delete
### ΪʲôҪ����
- ����ڴ洴������ ��ͳ�ƺͼ��й©
- �ڴ����Ĵ���
- �ض�Ӧ�ã����������ڴ湲��
### ����ȫ�ֵ�new��delete
- ��ʹ��new��delete������ʹ��custom�����غ���
*/

#include <iostream>

/*
 * ����ȫ�ֵ�new �Լ� new []
 * �ڲ����� c malloc �ӿ�
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
 * ����ȫ�ֵ�delete �Լ� delete []
 * �ڲ����� c free �ӿ�
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
 * ����demo
 */

// �Զ����������ͣ�class��
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
	/* ex1. �����������͵� new �� delete */
	int* i = new int;
	delete i;

	/* ex2. class�������͵� new �� delete */
	auto mem1 = new exData();
	delete mem1;

	/* ex3. �����������͵� new [] �� delete [] */
	int* arr = new int[1024];
	delete[] arr;

	/* ex4. class�������͵� new [] �� delete []*/
	exData* exDatas = new exData[2];
	delete[] exDatas;

	/* ex4. ʹ�� C++ Ĭ�� new */
	// ȫ�ֵ�new����������أ��޷��ٴ�ʹ��

	return 0;
}
