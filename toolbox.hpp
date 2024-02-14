#ifndef INCLUDED_TOOLBOX_HPP
#define INCLUDED_TOOLBOX_HPP

#include <intrin.h>
#include <cstdint>

namespace toolbox
{

template<typename Func, typename... Args>
uint64_t timecycles(Func func, Args&& ...args)
{
    constexpr size_t NUM_ITERATIONS = 10;
    uint64_t begin = __rdtsc();
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    uint64_t elapsed = (__rdtsc() - begin) / NUM_ITERATIONS;
    return elapsed;
}

template<typename Func, typename... Args>
uint64_t timecycles(const size_t iterations, Func func, Args&& ...args)
{
    const size_t NUM_ITERATIONS = iterations;
    uint64_t begin = __rdtsc();
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    uint64_t elapsed = (__rdtsc() - begin) / NUM_ITERATIONS;
    return elapsed;
}

} // namespace toolbox

#endif // INCLUDED_TOOLBOX_HPP