/*
 * C++ 的指针类型转换更安全，但前提是使用者本身需要知道转换的安全性
 * C 的指针类型转换不会考虑转换是否安全，都会默认强制类型转换
 */

#include <iostream>

int main()
{
	//void 指针和指针类型转换
	void* ptr1 = malloc(1024); // C malloc 默认分配 (void*) 指针， 可以转换成任意需要的指针类型
	free(ptr1);

	/*
	 * example 1. C (int*) 与 static_cast<int*> 的等价写法
	 */
	{
		int num = 1;
		void* ptr = &num;

		int* ptr2 = static_cast<int*>(ptr); // C++ static_cast  (void*) -> (int*) 
		int* ptr3 = (int*)ptr; // C (void*) -> (int*)
	}
	
	/*
	 * example 2. const 指针的转换
	 */
	{
		const int* cptr1 = new int[1024];

		//int* ptr4 = static_cast<int*>(cptr1); 转换报错，不允许转换const类型指针，需要先去掉const
		int* ptr6 = const_cast<int*>(cptr1); //去掉const

		int* ptr4 = (int*)(cptr1); // C 强转

		delete[]cptr1;
	}
	
	
	/*
	 * example 3. 范围不一致的不安全指针的转换
	 */
	{
		unsigned char* ucptr = new unsigned char[1024];
		//int* ptr5 = static_cast<int*>(ucptr); // static_cast 转换出错
		auto ptr7 = reinterpret_cast<int*>(ucptr); // 无视编译类型，直接强转
		
		auto ptr5 = (int*)ucptr;

		delete[]ucptr;
	}

	/*
	 * example 4. 常量指针与指针常量
	 * 
	 */
	{
		int i = 10;
		const int* cptr1 = &i;
		// *cptr1++; 指针指向常量不允许修改

		int j = 8;
		int const* cptr2 = &j;
		*cptr2++;
		// *cptr2 = &i; 指针为常量不允许更改指向

		const int* const cptr3 = &i;
	}
	

	return 0;
}
