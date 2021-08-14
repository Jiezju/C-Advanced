/*

# ָ����Ϊ������������
## ָ����Ϊ�������˵��
- ���������ڴ棬��Ҫ�ṩ�ڴ��С�����鵽ָ���޷�֪����С����������Ϊconst
- ��������ڴ棬ͬ����Ҫ�ṩ�ڴ��С����ֹ���
- ���ָ�����д������ڴ棬��Ҫ����ָ�����û���ָ��ָ���ָ��
- ͨ������ֵֻ�ܷ��ض��пռ䣬�Ƚ�Σ�գ���Ҫ������ע��˵������ֹ�ڴ�й©
*/

#include <iostream>
using namespace std;

/*
 *
 *  ָ����Ϊ��������
 */
/* ֱ�Ӵ���ָ�룬 sizeof(data) ��ȡ����ָ��Ĵ�С */
void PtrFunction(const char* data, int size)
{
	// sizeof(data) ��Ϊָ�봫�룬�������ָ�볣���Ĵ�С
	cout << "sizeof(data) = " << sizeof(data) << endl;
}

//������������ ����ת��ָ��
void PtrFunction(const char data[])
{
	cout << "sizeof(data) = " << sizeof(data) << endl;
}

//���ݲ��� ��ȡ�����С
template <typename T, size_t Size>
void TestMemArr(T (&data)[Size])
{
	cout << "sizeof(data)=" << sizeof(data) << endl;
}

/*
 *
 * ָ����Ϊ�������
 */
/* 1 ����������ջ�ڴ� --- ʧ�� */
char* TestMem()
{
	//error ���ܷ���ջ�пռ䣬�������� ջ �ͷ�
	char buf[1024] = "test";
	return buf;
}

/* 2. ������������ڴ� --- �ɹ� �����ţ��ڴ�й©�� */
char* TestMem(size_t size)
{
	char* buf = new char[size];
	return buf;
}

/* 3. ʹ�ú����ڴ������ڴ� �޸� ָ����� --- ʧ�� */
void TestMem(char* out)
{
	//�޸ĵľֲ����� �ڴ�й©
	out = new char[1024]; 
}

/* 4. ����ָ�봫�룬���صĿռ���Ҫע�ͣ����û��ͷ� -- �ɹ� �����ţ��ڴ�й©��*/
int TestMem(char** out)
{
	int size = 1024;
	//�޸ĵľֲ�����
	*out = new char[size];
	return size;
}

/* 5. �ⲿ����ָ�룬�������ڲ����룬�ڲ��ͷ� --- �ɹ� */
void TestMem(char* out, const int size)
{
	for (int i=0; i<size; i++)
	{
		char* tmp = new char('1');
		memcpy(out, tmp, sizeof(char));
		delete tmp;
		out++;
	}
}

int main()
{
	/* 1. �������ָ����Ϊ�������룬��ָ���ڴ��С */
	{
		char data[] = "test mem ptr";
		char* data_ptr = new char[12];
		cout << "sizeof(data) = " << sizeof(data) << endl;
		PtrFunction(data, sizeof(data)); // sizeof(data) = 13
		PtrFunction(data_ptr);
		
		// ʹ��ģ�巵��data ��Ӧ�ڴ��С�ķ���
		TestMemArr(data);
		cout << data << endl;
	}

	/* 2. �������ָ����Ϊ����,�����ڴ��޸� */
	{
		// �쳣�ռ��Ѿ��ͷţ������ȷ��
		cout << TestMem() << endl;
		// ���ڴ�����
		char* buf = TestMem(1024);
		delete[] buf;
		
		char* out = nullptr;
		TestMem(out);
		cout << "out  " << (int)out << endl;

		// ����ָ�봫��
		TestMem(&out);
		cout << "out  " << (int)out << endl;
		delete out;
		out = nullptr;

		// ����ָ�룬�����޸�ָ���ڴ棬�ڴ������ͷ���һ��
		const int size = 1024;
		char* outptr = new char[size];
		TestMem(outptr, size);
		cout << outptr[0] << endl;
	}

	return 0;
}