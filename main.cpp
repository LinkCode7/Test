#include "pch.h"

//#define TEST_STD_THREAD // 多线程测试
#ifdef TEST_STD_THREAD
    #include "cpp/cpp0x/std_thread.h"
#endif

int main()
{
#ifdef TEST_STD_THREAD
    // test_thread_recursive_mutex();
    test_thread_shared_mutex();
#else
    RUN_ALL_TESTS();
#endif

    return 0;
}
