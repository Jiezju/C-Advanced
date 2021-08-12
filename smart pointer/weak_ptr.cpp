/*
## weak_ptr
	use_count
		���ع���ö���� shared_ptr ��������
	lock
		�����������õĶ����shared_ptr

	���ڽ��shared_ptrѭ�����õ����ڴ��޷����յ�����
	
*/

#include <iostream>
using namespace std;

class B;
class A
{
public:
	A() { cout << "Construct A" << endl; };
	~A() { cout << " Deconstruct A." << endl; }
	void test() { cout << "A test." << endl; }
	shared_ptr<B> b;
	weak_ptr<B> wb;
};
class B
{
public:
	B() { cout << "Construct B" << endl; };
	~B() { cout << " Deconstruct B." << endl; }
	void test() { cout << "B test." << endl; }
	shared_ptr<A> a;
	weak_ptr<A> wa;
};


int main(int argc, char* argv[])
{
	cout << "cppds.com" << endl;
	// shared_ptrѭ����������ԭ��
	/*
	 * sa �������� sa.use_count - 1 = 1 sa��Դ���ͷ� sa.b���ͷ�
	 * sb �������� sb.use_count - 1 = 1s b��Դ���ͷ� sb.a ���ͷ�
	 */
	{
		shared_ptr<A> sa = make_shared<A>();
		shared_ptr<B> sb = make_shared<B>();
		sa->b = sb;
		sb->a = sa;
		cout << "a->b1 = b b.use_count()=" << sb.use_count() << endl;
		cout << "b->a1 = a a.use_count()=" << sa.use_count() << endl;
	}

	cout << "after AB " << endl;
	{
		auto a = make_shared<A>();
		auto b = make_shared<B>();
		a->wb = b; //=1
		// a->wb->test(); �޷�ͨ�� weak_ptr ֱ�ӵ����ڴ����ĳ�Ա�ͷ���
		a->wb.lock()->test(); // ͨ�� weak_ptr �� lock() ����������� shared_ptr��Ȼ���ٵ����ڴ����ĳ�Ա�ͷ�����
		cout << "a->b1 = b b.use_count()=" << b.use_count() << endl;

		b->wa = a; //+1 =2
		cout << "b->a1 = a a.use_count()=" << a.use_count() << endl;
	}

	return 0;
}