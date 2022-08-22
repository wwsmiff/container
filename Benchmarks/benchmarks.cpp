#include "../Container.hpp"
#include <benchmark/benchmark.h>
#include <cmath>

const auto LOOPS = std::pow(10, 5);

static void BM_ContainerBenchmark(benchmark::State &state)
{
	for(auto _ : state)
	{
		Container<int32_t> container;
		for(size_t i = 0; i < LOOPS; ++i)
		{
			container.Append(utils::rand<int32_t>(1, 1000));
		}
	}
}

static void BM_VectorBenchmark(benchmark::State &state)
{
	for(auto _ : state)
	{
		std::vector<int32_t> vector;
		for(size_t i = 0; i < LOOPS; ++i)
		{
			vector.push_back(utils::rand<int32_t>(1, 1000));
		}
	}
}

BENCHMARK(BM_ContainerBenchmark)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_VectorBenchmark)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
