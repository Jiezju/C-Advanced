/*
* shared_ptr
- ��������Ȩ������ָ�롣���shared_ptrָ��ͬһ����, ͨ�����ü������shared_ptrָ���ڴ��Ƿ�ʧЧ
- �ɸ��ƹ��� (CopyConstructible)
- �ɸ��Ƹ�ֵ (CopyAssignable)
- ���ݷ��ʷ��̰߳�ȫ
- shared_ptr �Ŀ��ƿ����̰߳�ȫ
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

	int index1 = 0;
	int idnex2 = 0;
};

// �Զ�����պ���
void DelData(XData* p)
{
	cout << "call DelData" << endl;
	delete p;
}

int main(int argc, char *argv[])
{
	// 1. shared_ptr ��ʼ��
	{
		// ex1. Ĭ�Ϲ���
		shared_ptr<int> spInt(new int);
		*spInt = 10;
		auto sptr = spInt.get();
		
		shared_ptr<int[]> spInts(new int[1024]);
		spInts[0] = 2;

		// ex2. make_shared����
		auto spXdata = make_shared<XData>();
		cout << "sp3.use_count() = " << spXdata.use_count() << endl;// ���ü���
	}

	// 2. ���ƹ��� �� ��ֵ,�ı����ü���
	{
		shared_ptr<XData> sp(new XData);
		auto sp_temp = make_shared<XData>();
		sp_temp = sp;
		cout << "sp_temp = sp ; sp.use_count() = " << sp.use_count() << endl;
		cout << "sp_temp.use_count() = " << sp_temp.use_count() << endl;
		{
			shared_ptr<XData> sp1 = sp_temp;
			cout << "sp.use_count() = " << sp.use_count() << endl;
			cout << "sp_temp.use_count() = " << sp_temp.use_count() << endl;
			cout << "sp1.use_count() = " << sp1.use_count() << endl;
		}
		cout << "sp.use_count() = " << sp.use_count() << endl;
		cout << "sp_temp.use_count() = " << sp_temp.use_count() << endl;
	}

	// 3. shared_ptr ����
	{
		// nullptr reset ��ʽ����
		shared_ptr<XData> sp(new XData);
		shared_ptr<XData> sp1 = sp;
		shared_ptr<XData> sp2 = sp;
		cout << "sp.use_count() = " << sp.use_count() << endl;
		sp1 = nullptr;
		cout << "sp.use_count() = " << sp.use_count() << endl;

		sp2.reset();
		cout << "sp.use_count() = " << sp.use_count() << endl;

		//  shared_ptr����ɾ������
		{
			shared_ptr<XData> sp7(new XData, DelData);
			shared_ptr<XData> sp8(new XData, [](auto* p) {
				cout << "Call delete lambda" << endl;
				delete p;
				});
		}

		//  shared_ptr����ָ��ָ��ͬһ������ͬ��Ա
		{
			shared_ptr<XData> sc1(new XData);
			cout << "sc1 use_count=" << sc1.use_count() << endl;
			shared_ptr<int> sc2(sc1, &sc1->idnex2);
			shared_ptr<int> sc3(sc1, &sc1->index1);
			cout << "sc1 use_count=" << sc1.use_count() << endl;
		}
		
	}

	
	return 0;
}