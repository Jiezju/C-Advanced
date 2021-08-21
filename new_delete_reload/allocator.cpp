/*
## ������allocator
- ����������ʵ�������㷨ʱ��������洢ϸ�ڸ���Ӷ�����ϡ�
- �������ṩ�洢�������ͷŵı�׼����
- �����ڴ����͹������

std::allocator
address (C++17 ������)(C++20 ���Ƴ�)
allocate ����δ��ʼ���Ĵ洢
deallocate �����洢
max_size(C++17 ������)(C++20 ���Ƴ�)
construct (C++17 ������)(C++20 ���Ƴ�)
destroy(C++17 ������)(C++20 ���Ƴ�)
*/

#include <iostream>
using namespace std;
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
};
int main(int argc, char *argv[])
{
	allocator<XData> xdata_allco;
	int size = 3;

	//�������ռ� �����ù���
	auto dataarr = xdata_allco.allocate(size);

	for (int i = 0; i < size; i++)
	{
		//allocator_traits ��ģ���ṩ���ʷ����� (Allocator) �������Եı�׼����ʽ
		//allocator_traits< allocator<XData> >

		//���ù���
		allocator_traits< decltype(xdata_allco)>::construct(xdata_allco, &dataarr[i]);

		//������������
		allocator_traits< decltype(xdata_allco)>::destroy(xdata_allco, &dataarr[i]);
	}

	//�ͷŶ����ڴ� ����������
	xdata_allco.deallocate(dataarr, size);

	return 0;
}