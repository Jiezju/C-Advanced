/*
* shared_ptr
- 共享所有权的智能指针。多个shared_ptr指向同一对象, 通过引用计数监控shared_ptr指向内存是否失效
- 可复制构造 (CopyConstructible)
- 可复制赋值 (CopyAssignable)
- 数据访问非线程安全
- shared_ptr 的控制块是线程安全
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

	int index1 = 0;
	int idnex2 = 0;
};

// 自定义回收函数
void DelData(XData* p)
{
	cout << "call DelData" << endl;
	delete p;
}

int main(int argc, char *argv[])
{
	// 1. shared_ptr 初始化
	{
		// ex1. 默认构造
		shared_ptr<int> spInt(new int);
		*spInt = 10;
		auto sptr = spInt.get();
		
		shared_ptr<int[]> spInts(new int[1024]);
		spInts[0] = 2;

		// ex2. make_shared构造
		auto spXdata = make_shared<XData>();
		cout << "sp3.use_count() = " << spXdata.use_count() << endl;// 引用计数
	}

	// 2. 复制构造 和 赋值,改变引用计数
	{
		shared_ptr<XData> sp(new XData);
		auto sp_temp = make_shared<XData>();
		sp_temp = sp;
		cout << "sp_temp = sp ; sp.use_count() = " << sp.use_count() << endl;
		cout << "sp_temp.use_count() = " << sp_temp.use_count() << endl;
		{
			shared_ptr<XData> sp1 = sp_temp;
			cout << "sp.use_count() = " << sp.use_count() << endl;
			cout << "sp_temp.use_count() = " << sp_temp.use_count() << endl;
			cout << "sp1.use_count() = " << sp1.use_count() << endl;
		}
		cout << "sp.use_count() = " << sp.use_count() << endl;
		cout << "sp_temp.use_count() = " << sp_temp.use_count() << endl;
	}

	// 3. shared_ptr 清理
	{
		// nullptr reset 方式清理
		shared_ptr<XData> sp(new XData);
		shared_ptr<XData> sp1 = sp;
		shared_ptr<XData> sp2 = sp;
		cout << "sp.use_count() = " << sp.use_count() << endl;
		sp1 = nullptr;
		cout << "sp.use_count() = " << sp.use_count() << endl;

		sp2.reset();
		cout << "sp.use_count() = " << sp.use_count() << endl;

		//  shared_ptr定制删除函数
		{
			shared_ptr<XData> sp7(new XData, DelData);
			shared_ptr<XData> sp8(new XData, [](auto* p) {
				cout << "Call delete lambda" << endl;
				delete p;
				});
		}

		//  shared_ptr智能指针指向同一个对象不同成员
		{
			shared_ptr<XData> sc1(new XData);
			cout << "sc1 use_count=" << sc1.use_count() << endl;
			shared_ptr<int> sc2(sc1, &sc1->idnex2);
			shared_ptr<int> sc3(sc1, &sc1->index1);
			cout << "sc1 use_count=" << sc1.use_count() << endl;
		}
		
	}

	
	return 0;
}