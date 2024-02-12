#ifndef INCLUDED_TOOLBOX_HPP
#define INCLUDED_TOOLBOX_HPP

#include <intrin.h>

namespace toolbox
{

template<typename... Args1, typename... Args2>
void timeit(uint64_t& elapsed, void(*func)(Args1...), Args2&& ...args)
{
    constexpr int NUM_ITERATIONS = 1;
    uint64_t begin = __rdtsc();
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(args...);
    }
    elapsed = (__rdtsc() - begin) / NUM_ITERATIONS;
}

template<typename... Args1, typename... Args2>
void timeit(size_t iters, uint64_t& elapsed, void(*func)(Args1...), Args2&& ...args)
{
    size_t NUM_ITERATIONS = iters;
    uint64_t begin = __rdtsc();
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(args...);
    }
    elapsed = (__rdtsc() - begin) / NUM_ITERATIONS;
}

} // namespace toolbox

#endif // INCLUDED_TOOLBOX_HPP