/*

# ����ָ����Ϊ������������
- unique_ptr ָ�봫�룬�����������죬��Ҫmove
- unique_ptr ָ�봫����ֱ���ƶ�move ����
*/
#include <iostream>
using namespace std;

//����ָ����Ϊ���������ͷ���ֵ
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
	int index = 0;
};
unique_ptr<XData> TestUnique(unique_ptr<XData> ptr)
{
	cout << "ptr->index=" << ptr->index << endl;
	unique_ptr<XData> re(new XData);
	re->index = 222;
	// �������Ż� 1 �������ֵ֧��move �������Զ�����move,��֧�ֵ��ÿ�������
	return re;
}

int main()
{
	{
		unique_ptr<XData> ptr1(new XData);
		ptr1->index = 111;
		cout << "ptr1->index=" << ptr1->index << endl;
		auto re = TestUnique(move(ptr1));
		cout << "re->index=" << re->index << endl;
		if (!ptr1)
		{
			cout << "ptr1 empty" << endl;
		}
		else
		{
			cout << "ptr1->index=" << ptr1->index << endl;
		}
	}
	return 0;
}
