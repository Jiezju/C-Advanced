//  创建线程

#include <iostream>
#include <thread>
#include <chrono>


void thread_function(int n)
{
	std::thread::id this_id = std::this_thread::get_id();			//获取线程ID

	for (int i = 0; i < 5; i++) {
		std::cout << "Child function thread " << this_id << " running : " << i + 1 << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(n));   	//进程睡眠n秒
	}
}

class Thread_functor
{
public:
	// functor行为类似函数,C++中的仿函数是通过在类中重载()运算符实现，使你可以像使用函数一样来创建类的对象
	void operator()(int n)
	{
		std::thread::id this_id = std::this_thread::get_id();

		for (int i = 0; i < 5; i++) {
			std::cout << "Child functor thread " << this_id << " running: " << i + 1 << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(n));   //进程睡眠n秒
		}
	}
};


int main()
{
	std::thread mythread1(thread_function, 1);      // 传递初始函数作为线程的参数
	if (mythread1.joinable())                  //判断是否可以成功使用join()或者detach()，返回true则可以，返回false则不可以
		mythread1.join();                     // 使用join()函数阻塞主线程直至子线程执行完毕

	Thread_functor thread_functor;			 //函数对象实例化一个对象
	std::thread mythread2(thread_functor, 3);     // 传递初始函数作为线程的参数
	if (mythread2.joinable())
		mythread2.detach();                  // 使用detach()函数让子线程和主线程并行运行，主线程也不再等待子线程

	auto thread_lambda = [](int n) {			//lambda表达式格式：[capture list] (params list) mutable exception-> return type { function body }
		std::thread::id this_id = std::this_thread::get_id();
		for (int i = 0; i < 5; i++)
		{
			std::cout << "Child lambda thread " << this_id << " running: " << i + 1 << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(n));   //进程睡眠n秒
		}
	};

	std::thread mythread3(thread_lambda, 4);     // 传递初始函数作为线程的参数
	if (mythread3.joinable())
		mythread3.join();                     // 使用join()函数阻塞主线程直至子线程执行完毕

	// 主线程
	std::thread::id this_id = std::this_thread::get_id();
	for (int i = 0; i < 5; i++) {
		std::cout << "Main thread " << this_id << " running: " << i + 1 << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	getchar();
	return 0;
}
