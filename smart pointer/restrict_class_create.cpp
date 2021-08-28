/*
 * ����ջ�д����������Ƶ���delete���ٶ���
 * 
 */

#include <iostream>
using namespace std;

class TestMem
{
public:
	static TestMem* Create()
	{
		cout << "static Create " << endl;
		return new TestMem();
	}
	static void Drop(TestMem* tm)
	{
		cout << "static Drop" << endl;
		delete tm;
	}
protected:

	// �������ⲿ���ʣ����޷�ʹ��Ĭ�Ϲ��캯������
	TestMem()
	{
		cout << "Create TestMem" << endl;
	}
	// �������ⲿ���ʣ����޷�ʹ��Ĭ��������������
	virtual ~TestMem()
	{
		cout << "Drop TestMem" << endl;
	}
};

int main()
{

	//  ����ջ�д����������Ƶ���delete���ٶ���
	//TestMem tm1;
	//auto tm2 = new TestMem();
	TestMem *tm3 = TestMem::Create();
	//delete tm3;
	TestMem::Drop(tm3);

	return 0;
}