#include <iostream>
#include <thread>
#include <mutex>

/*
 * ������������������������̬֮һ�ı����������ͼ���
 * ����״̬���Ա�֤��Դ���ʵĴ���
 */
std::mutex mtx;

void print_block(int n, char c)
{
	/*
	 * mtx�����ĳ���ֻ���� �����̷߳���
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
	 * ���߳� main �ȴ����߳� th1 ���н���
	 * �����������̣߳��������������е����߳� ���� th2
	 */
	th1.join(); 
	th2.join();

	return 0;
}

