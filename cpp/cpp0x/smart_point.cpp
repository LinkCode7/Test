#include "pch.h"
#include "smart_point.h"

#include <memory>

#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

using namespace std;




void test_smart_point()
{
	_test_smart_point();

	test_smart_point20200811();

	test_smart_point20210808();

	test_shared_ptr_function();

	if (false)
	{
		//test_shared_ptr_counter_thread_safe();
		test_shared_ptr_counter_thread_safe2();
	}
}



void test_smart_point20200811()
{
	test_shared_pointer_init();

	test_shared_ptr();

	test_my_shared_ptr();

	test_shared_ptr_leak();
}



void _test_smart_point()
{
	/*Ptr<char> cp1(new char('a'));
	Ptr<char> cp2(cp1);
	Ptr<char> cp3;
	cp3 = cp2;
	cp3 = cp1;
	cp3 = cp3;
	Ptr<char> cp4(new char('b'));
	cp3 = cp4;*/

	int count(0);
	shared_ptr<int> pHen(new int(4));
	count = pHen.use_count();

	print_pointer(pHen);
	//shared_ptr<int> pEgg = pHen;
	count = pHen.use_count();
	//count = pEgg.use_count();
}

void test_shared_ptr()
{
	shared_ptr<MyObject> pEgg;

	{
		shared_ptr<MyObject> pHen = std::make_shared<MyObject>();
		cout << "get:" << pHen.get() << "	" << "use_count:" << pHen.use_count() << endl;

		pEgg = pHen;
		cout << "get:" << pHen.get() << "	" << "use_count:" << pHen.use_count() << endl;
		cout << "get:" << pEgg.get() << "	" << "use_count:" << pEgg.use_count() << endl;
	}

	cout << "get:" << pEgg.get() << "	" << "use_count:" << pEgg.use_count() << endl;
}

void test_my_shared_ptr()
{
	SharedPtr<MyObject> pEgg;

	{
		SharedPtr<MyObject> pHen(new MyObject);
		cout << "get:" << pHen.get() << "	" << "use_count:" << pHen.use_count() << endl;

		(*pHen).Show();

		pEgg = pHen;
		pEgg->Show();
		cout << "get:" << pHen.get() << "	" << "use_count:" << pHen.use_count() << endl;
		cout << "get:" << pEgg.get() << "	" << "use_count:" << pEgg.use_count() << endl;
	}

	cout << "get:" << pEgg.get() << "	" << "use_count:" << pEgg.use_count() << endl;
}

// shared_ptr的缺陷
void test_shared_ptr_leak()
{
	//_USE_WEAK_PTR_
	if (true)
	{
		shared_ptr<Hen> pHen = std::make_shared<Hen>();
		shared_ptr<Egg> pEgg = std::make_shared<Egg>();
		pEgg->pointer_ = pHen;
		pHen->pointer_ = pEgg;
		cout << pEgg.use_count() << endl;
		cout << pHen.use_count() << endl;

#ifdef _USE_WEAK_PTR_
		if (!pEgg->pointer_.expired())
			std::cout << "pEgg not expired" << std::endl;
#endif
	}
}








void thread_function(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the
								  // shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "\n>> local pointer in a thread:" << " lp.get()=" << lp.get() << ", lp.use_count()=" << lp.use_count() << "\n\n";
	}
}

void test_shared_ptr_counter_thread_safe()
{
	std::shared_ptr<Base> p = std::make_shared<Derived>();

	std::cout << "\nCreated a shared Derived (as a pointer to Base)\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << "\n\n";

	std::thread t1(thread_function, p), t2(thread_function, p), t3(thread_function, p);

	p.reset(); // release ownership from main

	std::cout << "Shared ownership between 3 threads and released\n"
		<< "ownership from main:\n"
		<< "  p.get() = " << p.get()
		<< ", p.use_count() = " << p.use_count() << "\n\n";

	t1.join(); t2.join(); t3.join();

	std::cout << "All threads completed, the last one deleted Derived\n";
}

int g_counter = 0;
void test_thread_safe1()
{
	int i = 100000;
	while (i-- > 0)
		++g_counter;
}
void test_thread_safe2(const std::shared_ptr<Base>& pointer)
{
	int i = 1000 * 10000;
	while (i-- > 0)
	{
		std::shared_ptr<Base> p = pointer;
		auto count = p.use_count();
	}
}
void test_shared_ptr_counter_thread_safe2()
{
	if (false)
	{
		std::shared_ptr<Base> pointer = std::make_shared<Derived>();
		std::thread thread1(test_thread_safe2, pointer);
		std::thread thread2(test_thread_safe2, pointer);

		thread1.join();
		thread2.join();
		std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;
	}
	else
	{
		std::thread thread1(test_thread_safe1);
		std::thread thread2(test_thread_safe1);
		thread1.join();
		thread2.join();
		std::cout << "g_counter = " << g_counter << std::endl;
		//std::atomic
	}
}

void test_shared_pointer_init()
{
	std::shared_ptr<MyObject> pointer;
	MyObject* p = pointer.get();
	cout << "pointer.get() = " << p << endl;

	pointer = std::make_shared<MyObject>();
}

void test_smart_point20210808()
{

}

void test_shared_ptr_function()
{
	auto pointer = std::make_shared<int>(10);
	auto pointer2 = pointer; // 引用计数 +1
	auto pointer3 = pointer; // 引用计数 +1
	int* p = pointer.get(); // 这样不会增加引用计数
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 3
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

	pointer2.reset();
	std::cout << "reset pointer2:" << std::endl;
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 2
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0, pointer2 已 reset
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2

	pointer3.reset();
	std::cout << "reset pointer3:" << std::endl;
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl; // 1
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 0, pointer3 已 reset
}

TEST(smart_point, std_unique_ptr)
{
	UniquePtrTest object;
	auto result = object.returnUniquePtr();
}

TEST(smart_point, shared_from_this)
{
	{
		TestSharedFromThisSp pObject1 = std::make_shared<TestSharedFromThis>();
		pObject1->execute();

		TestSharedFromThisSp pObject2(new TestSharedFromThis);
		pObject2->execute();
	}

#if 0
	// 必须是堆上的内存
	TestSharedFromThis object;
	object.execute(); // shared_from_this()崩溃：bad_weak_ptr
#endif
}