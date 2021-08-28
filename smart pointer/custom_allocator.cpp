//## �Զ��������
//- ����ʵ���ڴ湲���ڴ�й©̽�⣬Ԥ�������洢���ڴ��
//- �Զ���vector��list������

#include <iostream>
#include <vector>
#include <list>

using namespace std;
class XData
{
public:
	XData()
	{
		cout << "Create XData" << endl;
	}
	XData(const XData& d)
	{
		this->index = d.index;
		cout << "Copy XData " << index << endl;
	}
	~XData()
	{
		cout << "Drop XData " << index << endl;
	}
	int index = 0;
};

template <typename Ty>
class MyAllocator
{
public:
	using value_type = Ty;

	MyAllocator() {}

	template<class Other>
	MyAllocator(const MyAllocator<Other>&) {}

	//�ڴ��ͷ�
	void deallocate(Ty* const ptr, const size_t count)
	{
		cout << "deallocate " << count << endl;
		free(ptr);
	}

	//�ڴ����
	Ty* allocate(const size_t count)
	{
		cout << "allocate " << count << endl;
		cout << typeid(Ty).name() << endl;
		return static_cast<Ty*> (malloc(sizeof(Ty) * count));
	}
};

int main(int argc, char *argv[])
{
	std::vector<XData, MyAllocator<XData> > vd;
	XData d;
	d.index = 111;
	vd.push_back(d);
	d.index = 222;
	vd.push_back(d);
	d.index = 333;
	vd.push_back(d);
	for (auto &xd : vd)
	{
		cout << xd.index << std::endl;
	}
	cout << "==================== list =======================" << std::endl;
	list<XData, MyAllocator<XData>> datas;
	d.index = 444;
	datas.push_back(d);
	d.index = 555;
	datas.push_back(d);
	d.index = 666;
	datas.push_back(d);
	for (auto &d : datas)
	{
		cout << d.index << endl;
	}
	getchar();


	return 0;
}