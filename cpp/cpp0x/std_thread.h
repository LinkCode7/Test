#pragma once

#include <mutex>
#include <condition_variable>

#include <queue>




void compete_source();

void test_future();
void test_future_better();

void test_condition_variable();




class ProducerConsumer
{
	std::queue<int> produced_nums_;
	std::mutex mtx_;
	std::condition_variable condition_var_;
	bool notified_ = false; // 通知信号

public:

	void execute();

	// 生产者
	void producer();

	// 消费者
	void consumer();
};
