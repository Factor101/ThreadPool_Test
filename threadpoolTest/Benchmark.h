#pragma once

class Benchmark
{
	public:
	Benchmark();
	~Benchmark();

	inline const int measureTime(void* fn);
	void compareTimes(void* fn1, void* fn2);
	void compareAverageTimes(void* fn1, void* fn2, const int n);
};