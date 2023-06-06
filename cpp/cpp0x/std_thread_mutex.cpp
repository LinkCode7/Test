#include "std_thread_mutex.h"

#include <cassert>
#include <iostream>
#include <mutex>

#include "pch.h"
#include "std_thread.h"

using namespace std;

// std::mutex g_mutex; // crash
std::recursive_mutex g_mutex; // 递归锁(同一线程可重复加的互斥锁)

void ThreadBase::read()
{
    g_mutex.lock();
    std::cout << "read()... _value = " << _value << std::endl;
    std::this_thread::sleep_for(1s);
    g_mutex.unlock();
}
void ThreadBase::write()
{
    g_mutex.lock();
    std::cout << "write()... _value++" << std::endl;
    _value++;
    std::this_thread::sleep_for(1s);
    g_mutex.unlock();
}

void MyThread::execute()
{
    for (;;)
    {
        // 如果不是可重入锁，那么得先开锁然后才能执行task1,否则会造成死锁
        // 但是如果开锁，也就是在一个线程执行任务时，另一个线程也进来了，如果另一个线程执行了一会就结束了，肯定会
        // 释放锁，而实际上线程一的任务还没执行完
        g_mutex.lock();
        std::cout << "                                   execute()拿到了锁，_value = " << _value << "" << std::endl;
        read();
        write();
        g_mutex.unlock();
        std::this_thread::sleep_for(1ms);
    }
}

// 可重入锁
void test_thread_recursive_mutex()
{
    MyThread object(100);
    object.start();
    object.wait();

    std::cout << getchar() << std::endl;
}

void test_thread_shared_mutex()
{
#define INCREASE_COUNT 10

    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]() {
        for (int i = 0; i < INCREASE_COUNT; i++)
        {
            counter.increment();
            std::cout << "thread(" << std::this_thread::get_id() << ") " << counter.get() << '\n';
            std::this_thread::sleep_for(300ms);

            // Note: Writing to std::cout actually needs to be synchronized as well
            // by another std::mutex. This has been omitted to keep the example small.
        }
    };

    std::thread thread1(increment_and_print);
    std::thread thread2(increment_and_print);

    thread1.join();
    thread2.join();

    assert(counter.get() == INCREASE_COUNT * 2);
}