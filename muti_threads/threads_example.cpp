#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <time.h>

#define DATACOUNT 100
#define THRESH 0.8
#define REMAIN_FLAG true

static bool more = true;

bool more_data_to_prepare()
{
	return more;
}

struct DataPack
{
	bool is_changed = 0;
	bool is_received = 0;
	static const int count_ = DATACOUNT;
	bool is_dead[count_]; // mask
	float data[count_]; // data
};

std::mutex mut;
std::queue<DataPack*> data_queue;	// 用于线程间通信的队列 
std::condition_variable data_cond;

DataPack g_data_ = DataPack();
DataPack* g_data = &g_data_;

int receice_data()
{
	int dead_count = 0;
	srand(time(NULL));
	for (int i = 0; i < g_data->count_; ++i)
	{
		g_data->data[i] = (rand() % 1000) / 1000.0;
		if ((g_data->data[i] * 1000) > (THRESH * 1000))
		{
			g_data->is_dead[i] = false;
			dead_count++;
		}
	}
	g_data->is_received = 1;
	std::cout << "Recive data complete!" << std::endl;
	return dead_count;
}

void prepare_data(const int num, bool is_dead, float* result)
{
	std::cout << "data_preparation_thread prepare_data" << std::endl;
	char x = 'q';
	std::cin >> x;
	if (x == 'q')
	{
		more = false;
	}
	int idx = 0;
	for (int i = 0; i < num; ++i)
	{
		if (is_dead)
		{
			if (!g_data->is_dead[i])
			{
				result[idx++] = g_data->data[i] > 0.5 ? 1.f : 0.f;
			}
		}
		else
		{
			if (g_data->is_dead[i])
			{
				result[idx++] = g_data->data[i] > 0.5 ? 1.f : 0.f;
			}
		}
	}
	if (idx > 20)
		g_data->is_changed = true;
	std::cout << "数据预处理" << std::endl;
}

void process(float* data, const int count)
{
	std::cout << "===========子线程的线程ID: " << std::this_thread::get_id() << std::endl;

	if (g_data->is_changed)
	{
		std::cout << "获得处理数据： " << std::endl;
		float sum = 0;
		for (int i = 0; i < g_data->count_; ++i)
		{
			if (g_data->is_dead[i])
			{
				sum += g_data->data[i];
				g_data->data[i] = 0;
			}
		}

		for (int i = 0; i < count; ++i)
		{
			std::cout << "data: " << data[i] * sum;
			std::cout << "\n" << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < count; ++i)
		{
			std::cout << "data: " << data[i] / 10;
			std::cout << "\n" << std::endl;
		}
	}

	std::cout << "数据处理完成！" << std::endl;
}

void data_preparation_thread(const int num, bool is_dead, float* result)
{
	while (more_data_to_prepare())
	{
		std::cout << "data_preparation_thread while" << std::endl;
		prepare_data(num, is_dead, result);
		std::lock_guard<std::mutex> lk(mut);
		// 数据准备好后，使用lock_guard来锁定信号量，将数据插入队列之中
		if (g_data->is_changed)
			data_queue.push(g_data);
		std::cout << "data_preparation_thread notify_one" << std::endl;
		// 通过条件变量通知其它等待的线程 
		data_cond.notify_one();
	}
}

void data_processing_thread(float* data, const int count)
{
	while (true)
	{
		std::cout << "data_processing_thread while" << std::endl;
		// 使用unique_lock，因为我们需要在取得数据之后，处理数据之间，解锁mutex 
		std::unique_lock<std::mutex> lk(mut);
		std::cout << "data_processing_thread before wait" << std::endl;
		// 等待条件满足，unique_lock和Lambda函数，判断数据队列是否为空 
		data_cond.wait(lk, [] {return !data_queue.empty(); });
		std::cout << "data_processing_thread pass wait" << std::endl;
		//DataPack* data_ = data_queue.front();
		data_queue.pop();
		// 处理数据需要较多时间，所以先解锁mutex 
		lk.unlock();
		std::cout << "data_processing_thread process data" << std::endl;
		process(data, count);
	}
}

int main()
{
	std::cout << "主线程的线程ID: " << std::this_thread::get_id() << std::endl;
	g_data->is_changed = 0;
	g_data->is_received = 0;
	for (int i = 0; i < g_data->count_; ++i)
	{
		g_data->data[i] = 0;
		g_data->is_dead[i] = true;
	}

	// init g_data
	int dead_count = REMAIN_FLAG ? receice_data() : DATACOUNT - receice_data();
	float* data = new float[dead_count];
	float res = 0.f;
	std::cout << "main" << std::endl;
	std::thread t1(data_preparation_thread, DATACOUNT, REMAIN_FLAG, data);
	std::thread t2(data_processing_thread, data, dead_count);

	t1.join();
	t2.join();

	return 0;
}