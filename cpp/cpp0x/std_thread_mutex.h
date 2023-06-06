#ifndef STD_THREAD_RECURSIVE_MUTEX_H
#define STD_THREAD_RECURSIVE_MUTEX_H

#include <shared_mutex>
#include <thread>

class ThreadBase
{
public:
    ThreadBase(int value) : _value(value) {}
    virtual ~ThreadBase() {}

    virtual void execute() = 0;

    void start() { _thread = std::thread(&ThreadBase::execute, this); }
    void stop() { wait(); }
    void wait()
    {
        if (_thread.joinable())
            _thread.join();
    }

protected:
    void read();
    void write();

    int _value;

private:
    std::thread _thread;
};

class MyThread : public ThreadBase
{
public:
    MyThread(int value) : ThreadBase(value) {}
    ~MyThread() {}

    void execute() override;
};

class ThreadSafeCounter
{
public:
    ThreadSafeCounter() = default;

    // Multiple threads/readers can read the counter's value at the same time.
    unsigned int get() const
    {
        std::shared_lock lock(_mutex);
        return _value;
    }

    // Only one thread/writer can increment/write the counter's value.
    void increment()
    {
        std::unique_lock lock(_mutex);
        _value++;
    }

    // Only one thread/writer can reset/write the counter's value.
    void reset()
    {
        std::unique_lock lock(_mutex);
        _value = 0;
    }

private:
    mutable std::shared_mutex _mutex;
    unsigned int              _value = 0;
};

#endif // !STD_THREAD_RECURSIVE_MUTEX_H
