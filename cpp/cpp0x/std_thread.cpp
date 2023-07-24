#include "std_thread.h"

#include <thread>
//#include <mutex>
#include <future>
//#include <condition_variable>

void test_thread()
{
    // std::thread thread([]() { std::cout << "hello world." << std::endl; });
    // thread.join();

    compete_source();

    test_future();
    test_future_better();

    // test_condition_variable();
}

int  g_value = 1;
void critical_section(int change_value)
{
    // lock和unlock
    std::mutex                  mtx;
    std::lock_guard<std::mutex> lock(mtx);
    g_value = change_value;
}
void critical_section2(int change_value)
{
    static std::mutex            mtx;
    std::unique_lock<std::mutex> lock(mtx);
    g_value = change_value;
    std::cout << g_value << std::endl;
    lock.unlock();
    // 在此期间，任何人都可以抢夺 v 的持有权

    // 开始另一组竞争操作，再次加锁
    lock.lock();
    g_value += 1;
    std::cout << g_value << std::endl;
}
void compete_source()
{
    // 在并发编程中，推荐使用std::unique_lock
    std::thread t1(critical_section2, 2), t2(critical_section2, 3);
    t1.join();
    t2.join();
    std::cout << g_value << std::endl;
}

void test_future()
{
    // 将一个返回值为 7 的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([]() { return 7; });

    // 获得 task 的期物
    std::future<int> result = task.get_future();
    // 在一个线程中执行 task
    std::thread(std::move(task)).detach();

    std::cout << "waiting...";
    result.wait(); // 在此设置屏障，阻塞到期物的完成

    std::cout << "done!" << std::endl << "future result is " << result.get() << std::endl;
}

void test_future_better()
{
    auto result = std::async([]() { return 7; });
    result.wait();
}

void test_condition_variable()
{
    ProducerConsumer object;
    object.execute();
}

void ProducerConsumer::execute()
{
    auto fun_producer = std::bind(&ProducerConsumer::producer, this);
    auto fun_consumer = std::bind(&ProducerConsumer::consumer, this);

    // 分别在不同的线程中运行
    std::thread producer(fun_producer);
    std::thread consumer[2];
    for (int i = 0; i < 2; ++i)
    {
        consumer[i] = std::thread(fun_consumer);
    }
    producer.join();

    for (int i = 0; i < 2; ++i)
    {
        consumer[i].join();
    }
}

// 生产者
void ProducerConsumer::producer()
{
    for (int i = 0;; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(900));
        std::unique_lock<std::mutex> lock(mtx_);
        std::cout << "producing " << i << std::endl;
        produced_nums_.push(i);
        notified_ = true;
        condition_var_.notify_all(); // 此处也可以使用 notify_one
    }
}

// 消费者
void ProducerConsumer::consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx_);
        while (!notified_)
        { // 避免虚假唤醒
            condition_var_.wait(lock);
        }
        // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 消费者慢于生产者
        lock.lock();

        while (!produced_nums_.empty())
        {
            std::cout << "consuming " << produced_nums_.front() << std::endl;
            produced_nums_.pop();
        }
        notified_ = false;
    }
}