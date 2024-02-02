#include "Benchmark.h"
#include <chrono>

Benchmark::Benchmark()
{
}

Benchmark::~Benchmark()
{
}

inline const int Benchmark::measureTime(void* fn)
{
	auto start = std::chrono::high_resolution_clock::now();
	((void(*)())fn)();
	auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void Benchmark::compareTimes(void* fn1, void* fn2)
{
	auto time1 = measureTime(fn1);
	printf("Time 1: %d\n", time1);
	auto time2 = measureTime(fn2);
	printf("Time 2: %d\n", time2);
}

void Benchmark::compareAverageTimes(void* fn1, void* fn2, const int n)
{
	int time1 = 0;
	int time2 = 0;

	for(int i = 0; i < n; i++)
	{
		time1 += measureTime(fn1);
	}

	for(int i = 0; i < n; i++)
	{
		time2 += measureTime(fn2);
	}

	printf("AVG Time 1: %d ms\n", time1 / n);
	printf("AVG Time 2: %d ms\n", time2 / n);

	printf("Function 1 is %f times faster than function 2\n", (float)time2 / time1);
}