#include <iostream>
#include "PixelBuffer.h"
#include "ThreadPool.h"
#include "Benchmark.h"

#define N_THREADS 16
#define N_BUFFER_CHUNKS 20

void computeChunk(PixelBuffer& buf, const int begin, const int end);
void threadPoolCompute();
void syncCompute();

PixelBuffer buffer = PixelBuffer(600, 600);
ThreadPool pool = ThreadPool(N_THREADS);

int main()
{
	Benchmark bench = Benchmark();
	bench.compareAverageTimes(threadPoolCompute, syncCompute, 100);
}

void syncCompute()
{
	int area = buffer.getWidth() * buffer.getHeight();
	for(int i = 0; i < area; i++)
	{
		buffer.setPixel(
			i,
			(unsigned char)(rand() * 255.f) + 1,
			(unsigned char)(rand() * 255.f) + 1,
			(unsigned char)(rand() * 255.f) + 1
		);
	}
}

void threadPoolCompute() 
{
	std::vector<int> bounds = buffer.getChunkBounds(N_BUFFER_CHUNKS);
	for(int i = 0; i < bounds.size() - 1; i++)
	{
		pool.addTask(
			std::bind(
				computeChunk,
				std::ref(buffer),
				bounds[i],
				bounds[i + 1]
			)
		);
	}

	while(pool.busy())
	{
	}
}

void computeChunk(PixelBuffer & buf, const int begin, const int end)
{
	// do calculation
	// temporary "expensive" computation for testing
	for(int i = begin; i < end; i++)
	{
		buffer.setPixel(
			i,
			(unsigned char)(rand() * 255.f) + 1,
			(unsigned char)(rand() * 255.f) + 1,
			(unsigned char)(rand() * 255.f) + 1
		);
	}

	//printf("Chunk from %d to %d done\n", begin, end);
}
