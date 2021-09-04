/*
# pool_options �ڴ������
//�ڴ��ÿ���С�������򼸺α�������
+ max_blocks_per_chunk
//�����˴�Сʹ�ô���ڴ�����
+ largest_required_pool_block
# memory_resource
+ allocate(_Bytes, _Align) :void* //�ֽڴ�СҪ��2�Ĵη�
+deallocate(_Ptr, _Bytes, _Align)
#  unsynchronized_pool_resource �̲߳���ȫ
- _Intrusive_list<_Oversized_header> _Chunks //����ڴ�����
- vector<_Pool> _Pools  //��ͨ��С�ڴ�����
- pool_options _Options  //�ڴ������
- +release() //����ڴ������������ڴ�
# do_allocate(_Bytes, _Align) :void*
# do_deallocate(_Ptr, _Bytes, _Align)
## synchronized_pool_resource �̰߳�ȫ
- _Mtx:mutex  ��������̰߳�ȫ
- lock_guard<mutex> _Guard{ _Mtx }

*/

#include <iostream>
#include <memory_resource>
#include <vector>
#include <thread>
using namespace std;
using namespace pmr;
//C++17 memory_resource�ڴ��
int main(int argc, char *argv[])
{
	std::cout << "cppds.com" << endl;
	pool_options opt;
	opt.largest_required_pool_block = 1024 * 1024 * 10;// �����ݿ���ֽ���
	opt.max_blocks_per_chunk = 1024 * 1024 * 100; //��ͨ���ݣ�ÿ�����ݿ�Ĵ�С

	//�̰߳�ȫ���ڴ��
	synchronized_pool_resource mpool(opt);
	int size = 1024 * 1024;
	std::vector <void*> datas;
	for (int i = 0; i < 500; i++)
	{
		try
		{
			//���ڴ������һ��ռ�
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

	auto b1 = mpool.allocate(1024 * 1024 * 20);//������ռ�
	mpool.deallocate(b1, 1024 * 1024 * 20);

	for (auto d : datas)
	{
		// ���ڴ���ͷſռ�
		mpool.deallocate(d, size);
		cout << "-" << flush;
		this_thread::sleep_for(20ms);
	}
	mpool.release(); //�Ƿ��̳߳ص������ڴ�
	getchar();

	return 0;
}