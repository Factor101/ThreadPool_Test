#include "ThreadPool.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <algorithm>

ThreadPool::ThreadPool(uint32_t threadNum)
{
	const uint32_t maxThreads = std::max(threadNum, std::thread::hardware_concurrency());

	for(int i = 0; i < maxThreads; i++)
	{
		threads.emplace_back(std::thread(&ThreadPool::taskQueueThread, this));
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(mut);
		shouldTerminate = true;
	}

	mutexCondition.notify_all();

	for(auto& thread : threads)
	{
		thread.join();
	}
}

void ThreadPool::taskQueueThread()
{
	
	while(true)
	{
		std::function<void()> job;

		{
			std::unique_lock<std::mutex> lock(mut);

			mutexCondition.wait(lock, [this] {
				return shouldTerminate || !jobs.empty();
			});

			if(shouldTerminate) {
				return;
			}

			job = jobs.front();
			jobs.pop();
		}

		job();
	}
}

void ThreadPool::addTask(const std::function<void()>& task)
{
	
	{
		std::unique_lock<std::mutex> lock(mut);
		jobs.push(task);
	}

	mutexCondition.notify_one();
}

void ThreadPool::stop()
{
	{
		std::unique_lock<std::mutex> lock(mut);
		shouldTerminate = true;
	}

	mutexCondition.notify_all();

	for(auto& thread : threads)
	{
		thread.join();
	}

	threads.clear();
}

bool ThreadPool::busy()
{
	bool flag = true;
	{
		std::unique_lock<std::mutex> lock(mut);
		flag = !jobs.empty();
	}

	return flag;
}