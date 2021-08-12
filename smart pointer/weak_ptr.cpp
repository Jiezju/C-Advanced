/*
## weak_ptr
	use_count
		返回管理该对象的 shared_ptr 对象数量
	lock
		创建管理被引用的对象的shared_ptr

	用于解决shared_ptr循环引用导致内存无法回收的问题
	
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
	// shared_ptr循环引用问题原理
	/*
	 * sa 出作用域 sa.use_count - 1 = 1 sa资源不释放 sa.b不释放
	 * sb 出作用域 sb.use_count - 1 = 1s b资源不释放 sb.a 不释放
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
		// a->wb->test(); 无法通过 weak_ptr 直接调用内存对象的成员和方法
		a->wb.lock()->test(); // 通过 weak_ptr 的 lock() 方法获得它的 shared_ptr，然后再调用内存对象的成员和方法。
		cout << "a->b1 = b b.use_count()=" << b.use_count() << endl;

		b->wa = a; //+1 =2
		cout << "b->a1 = a a.use_count()=" << a.use_count() << endl;
	}

	return 0;
}