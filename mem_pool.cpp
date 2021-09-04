/*
# pool_options 内存池配置
//内存池每块大小，用完则几何倍数增长
+ max_blocks_per_chunk
//超过此大小使用大块内存链表
+ largest_required_pool_block
# memory_resource
+ allocate(_Bytes, _Align) :void* //字节大小要是2的次方
+deallocate(_Ptr, _Bytes, _Align)
#  unsynchronized_pool_resource 线程不安全
- _Intrusive_list<_Oversized_header> _Chunks //大块内存链表
- vector<_Pool> _Pools  //普通大小内存链表
- pool_options _Options  //内存池配置
- +release() //清空内存池所有申请的内存
# do_allocate(_Bytes, _Align) :void*
# do_deallocate(_Ptr, _Bytes, _Align)
## synchronized_pool_resource 线程安全
- _Mtx:mutex  互斥访问线程安全
- lock_guard<mutex> _Guard{ _Mtx }

*/

#include <iostream>
#include <memory_resource>
#include <vector>
#include <thread>
using namespace std;
using namespace pmr;
//C++17 memory_resource内存池
int main(int argc, char *argv[])
{
	std::cout << "cppds.com" << endl;
	pool_options opt;
	opt.largest_required_pool_block = 1024 * 1024 * 10;// 大数据块的字节数
	opt.max_blocks_per_chunk = 1024 * 1024 * 100; //普通数据，每块数据块的大小

	//线程安全的内存池
	synchronized_pool_resource mpool(opt);
	int size = 1024 * 1024;
	std::vector <void*> datas;
	for (int i = 0; i < 500; i++)
	{
		try
		{
			//从内存池申请一块空间
			auto data = mpool.allocate(size);
			datas.push_back(data);
			cout << "+" << flush;
			this_thread::sleep_for(20ms);
		}
		catch (std::exception& ex)
		{
			cerr << "mpool.allocate failed!" << ex.what() << endl;
			exit(0);
		}

	}

	auto b1 = mpool.allocate(1024 * 1024 * 20);//申请大块空间
	mpool.deallocate(b1, 1024 * 1024 * 20);

	for (auto d : datas)
	{
		// 从内存池释放空间
		mpool.deallocate(d, size);
		cout << "-" << flush;
		this_thread::sleep_for(20ms);
	}
	mpool.release(); //是否线程池的所有内存
	getchar();

	return 0;
}