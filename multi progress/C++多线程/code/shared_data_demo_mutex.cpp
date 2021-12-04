#include <iostream>
#include <thread>
#include <list>
#include <vector>
#include <mutex>

class A
{
public:
	// 把收到的消息（玩家命令）添加到一个队列
	void inMsgRecQueue()
	{
		for (int i=0; i< 10000; ++i)
		{
			std::cout <<  "inMsgRecQueue 执行，插入一个消息 " <<std::endl;
			
			myMut.lock();
			msgRecQueue.push_back(i); // i 表示 玩家发送的消息
			myMut.unlock();
		}
	}
	
	bool outMsgLULProc(int& command)
	{
		myMut.lock();
		if (!msgRecQueue.empty())
		{
			// 消息队列不为空
			command = msgRecQueue.front();
			msgRecQueue.pop_front(); // 移除
			
			myMut.unlock();
			return true;
		}
		myMut.unlock();
		return false;
	}
	
	void outMsgRecQueue()
	{
		int command = 0;
		for (int i=0; i< 10000; ++i)
		{
			bool result = outMsgLULProc(command);
			
			if (result)
			{
				std::cout <<  "outMsgRecQueue 执行，取出一个元素 " <<std::endl;
				// process data
			}
			else
			{
				// 消息队列为空
				std::cout <<  "outMsgRecQueue 执行，但消息队列为空 " <<std::endl;
			}
		}
		
		std::cout << "end" << std::endl;
	}
	
private:
	std::list<int> msgRecQueue; // 容器，专门用于代表玩家给服务器发送的命令
	std::mutex myMut;
};

int main()
{
	A a;
	std::thread tin(&A::inMsgRecQueue, &a);
	std::thread tout(&A::outMsgRecQueue, &a);
	
	tin.join();
	tout.join();
	
	return 0;
}