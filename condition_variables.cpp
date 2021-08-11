//���������������ѯ�������

#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

std::deque<int> q;						//˫�˶��б�׼����ȫ�ֱ���
std::mutex mu;							//������ȫ�ֱ���
std::condition_variable cond;           //ȫ����������

//�����ߣ������з�������
void produce() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);			//�������������
		std::cout << "t1 produce a value: " << count << std::endl;
		locker.unlock();

		cond.notify_one();              // ��һ���ȴ��̷߳��������������㡱��֪ͨ
		std::cout << "t1 �� t2 ���� a value: " << count << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));		//��ʱ1��
		count--;
	}
}
//�����ߣ��Ӷ�����ȡ����
void cusume() {
	int data = 0;
	while (data != 1) {
		std::unique_lock<std::mutex> locker(mu);

		while (q.empty())        //�ж϶����Ƿ�Ϊ��
			cond.wait(locker); // ���������������������Եȴ�֪ͨ�����ѣ������Ѻ�����Ա�����������

		data = q.back();
		q.pop_back();			//���ݳ���������
		locker.unlock();
		std::cout << "t2 got a value from t1: " << data << std::endl;
	}
}

int main() {
	std::thread t1(produce);
	std::thread t2(cusume);
	t1.join();
	t2.join();

	getchar();
	return 0;
}
