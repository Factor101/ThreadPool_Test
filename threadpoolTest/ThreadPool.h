#pragma once
#include <functional>
#include <mutex>
#include <queue>

class ThreadPool
{
	public:
	ThreadPool(uint32_t threadNum = 0);
	~ThreadPool();
	void addTask(const std::function<void()>& task);
	void stop();
	bool busy();

	private:
	bool shouldTerminate = false;
	std::mutex mut;
	std::condition_variable mutexCondition;
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> jobs;

	void taskQueueThread();
};