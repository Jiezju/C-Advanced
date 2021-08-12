#include <iostream>
#include <thread>
#include <mutex>

/*
 * 互斥量（互斥锁），处于两态之一的变量：解锁和加锁
 * 两个状态可以保证资源访问的串行
 */
std::mutex mtx;

void print_block(int n, char c)
{
	/*
	 * mtx锁定的程序只允许 单个线程访问
	 */
	mtx.lock();
	for(int i=0;i<n;++i)
		std::cout << c;

	std::cout << "\n";
	mtx.unlock();
}

int main()
{
	std::thread th1(print_block, 50, '*');
	std::thread th2(print_block, 50, '$');

	/*
	 * 主线程 main 等待子线程 th1 运行结束
	 * 阻塞的是主线程，但不是阻塞并列的子线程 比如 th2
	 */
	th1.join(); 
	th2.join();

	return 0;
}

