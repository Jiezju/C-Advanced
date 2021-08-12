#include <iostream>

using namespace std;

class Data
{
public:
    static int count;
    int index = 0;
    Data() 
    { 
        count++; 
        index = count; 
        cout << index << ":Create Data" << endl; 
    }
    ~Data() 
    { 
        cout << index << ":Drop Data" << endl; 
    }

	void func()
    {
		cout << "func: ==============" << endl;
    }
};

int Data::count = 0;
int main(int argc,char *argv[])
{
 
    //example 1. unique_ptr 初始化, 出大括号作用域自行释放
    {
        unique_ptr<int> p1(new int);
        unique_ptr<Data> p2(new Data);
        auto p3 = make_unique<Data>();

        //空智能指针
        unique_ptr<Data> p4;
        unique_ptr<int[]> pa1 = make_unique<int[]>(1024);
        unique_ptr<int[]> pa2(new int[1024]);
        unique_ptr<Data[]> pa3(new Data[3]);
    }
	
	//example 2. unique_ptr智能指针访问和移动构造赋值
    {
		unique_ptr<int> iptr(new int);
		*iptr = 10;

		auto dptr = new Data;
		unique_ptr<Data> dsptr(dptr);
		dsptr->func();

		// unique_ptr智能指针数组访问
		unique_ptr<int[]> array_ptr(new int[10]);
    	for (int i=0;i<10;i++)
    	{
			array_ptr[i] = i;
			cout << array_ptr[i] << endl;
    	}
    }

	//example 3. 重置和移动内存资源
    {
		unique_ptr<Data> p6(new Data());
		//unique_ptr<Data> p7 = p6; 不可复制构造
		//p7 = p6; 不可以赋值
    	unique_ptr<Data> p7 = move(p6);//支持移动构造 p6释放所有权 转移到p7

    	unique_ptr<Data> p8(new Data());

		//支持移动赋值
		p7 = move(p8);

		//重置空间，原空间清理
		p7.reset(new Data());
    }

	//example 4. 释放所有权和自定义空间删除方法
    {
		unique_ptr<int> iptr(new int);

    	// 主动释放空间
		iptr = nullptr;

		//释放所有权
		unique_ptr<Data> p9(new Data);
		auto ptr9 = p9.release();
		delete ptr9;

		// 自定义空间删除方法
		{
			struct XPacket
			{
				unsigned char* data = nullptr;
				int size = 0;
			};
			class PacketDelete
			{
			public:
				void Close()
				{
					cout << "Call PakcetDelete Close!" << endl;
				}
				void operator()(XPacket* p) const
				{
					cout << "call PacketDelete()" << endl;
					delete p->data;
					delete p;
				}
			};

			unique_ptr<XPacket, PacketDelete> pd1(new XPacket);
			unique_ptr<XPacket, PacketDelete> pd2(new XPacket);
			pd2.get_deleter().Close();
			pd2.get_deleter()(pd2.get());
			pd2.release();
		}
    }

	
	
 
    return 0;
}