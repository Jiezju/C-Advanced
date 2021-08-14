/*

# 指针作为函数参数传递
## 指针作为参数设计说明
- 传递输入内存，需要提供内存大小（数组到指针无法知道大小），并设置为const
- 传递输出内存，同样需要提供内存大小，防止溢出
- 如果指向函数中创建堆内存，需要传递指针引用或者指向指针的指针
- 通过返回值只能返回堆中空间，比较危险，需要函数中注释说明，防止内存泄漏
*/

#include <iostream>
using namespace std;

/*
 *
 *  指针作为参数传入
 */
/* 直接传入指针， sizeof(data) 获取的是指针的大小 */
void PtrFunction(const char* data, int size)
{
	// sizeof(data) 作为指针传入，计算的是指针常量的大小
	cout << "sizeof(data) = " << sizeof(data) << endl;
}

//经过参数传递 数组转成指针
void PtrFunction(const char data[])
{
	cout << "sizeof(data) = " << sizeof(data) << endl;
}

//传递参数 获取数组大小
template <typename T, size_t Size>
void TestMemArr(T (&data)[Size])
{
	cout << "sizeof(data)=" << sizeof(data) << endl;
}

/*
 *
 * 指针作为参数输出
 */
/* 1 函数中申请栈内存 --- 失败 */
char* TestMem()
{
	//error 不能返回栈中空间，函数结束 栈 释放
	char buf[1024] = "test";
	return buf;
}

/* 2. 函数中申请对内存 --- 成功 （不优：内存泄漏） */
char* TestMem(size_t size)
{
	char* buf = new char[size];
	return buf;
}

/* 3. 使用函数内创建的内存 修改 指针参数 --- 失败 */
void TestMem(char* out)
{
	//修改的局部变量 内存泄漏
	out = new char[1024]; 
}

/* 4. 二级指针传入，返回的空间需要注释，由用户释放 -- 成功 （不优：内存泄漏）*/
int TestMem(char** out)
{
	int size = 1024;
	//修改的局部变量
	*out = new char[size];
	return size;
}

/* 5. 外部传入指针，函数体内部申请，内部释放 --- 成功 */
void TestMem(char* out, const int size)
{
	for (int i=0; i<size; i++)
	{
		char* tmp = new char('1');
		memcpy(out, tmp, sizeof(char));
		delete tmp;
		out++;
	}
}

int main()
{
	/* 1. 数组或者指针作为参数传入，需指定内存大小 */
	{
		char data[] = "test mem ptr";
		char* data_ptr = new char[12];
		cout << "sizeof(data) = " << sizeof(data) << endl;
		PtrFunction(data, sizeof(data)); // sizeof(data) = 13
		PtrFunction(data_ptr);
		
		// 使用模板返回data 对应内存大小的方法
		TestMemArr(data);
		cout << data << endl;
	}

	/* 2. 数组或者指针作为参数,传出内存修改 */
	{
		// 异常空间已经释放，结果不确定
		cout << TestMem() << endl;
		// 堆内存申请
		char* buf = TestMem(1024);
		delete[] buf;
		
		char* out = nullptr;
		TestMem(out);
		cout << "out  " << (int)out << endl;

		// 二级指针传入
		TestMem(&out);
		cout << "out  " << (int)out << endl;
		delete out;
		out = nullptr;

		// 传入指针，函数修改指针内存，内存申请释放在一起
		const int size = 1024;
		char* outptr = new char[size];
		TestMem(outptr, size);
		cout << outptr[0] << endl;
	}

	return 0;
}