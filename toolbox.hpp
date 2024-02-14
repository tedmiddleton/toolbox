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

template<size_t Iterations, typename Func, typename... Args>
uint64_t timecycles(Func func, Args&& ...args)
{
    constexpr size_t NUM_ITERATIONS = Iterations;
    uint64_t begin = __rdtsc();
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    uint64_t elapsed = (__rdtsc() - begin) / NUM_ITERATIONS;
    return elapsed;
}

inline int64_t qpfreq = -1;
uint64_t get_qpfreq()
{
    if (qpfreq == -1)
    {
        BOOL result = QueryPerformanceFrequency((LARGE_INTEGER*)&qpfreq);
        assert(result);
        assert(qpfreq>0);
    }
    return static_cast<uint64_t>(qpfreq);
}

#ifdef _WIN32
template<typename Func, typename... Args>
double timeus(Func func, Args&& ...args)
{
    constexpr size_t NUM_ITERATIONS = 10;
    int64_t before, after;
    QueryPerformanceCounter((LARGE_INTEGER*) &before);
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    QueryPerformanceCounter((LARGE_INTEGER*) &after);
    int64_t delta = after - before;
    int64_t qpfreq = get_qpfreq();
    double delta_d = static_cast<double>(delta);
    double elapsed_all_us = delta_d / qpfreq;
    double elapsed_us = elapsed_all_us / NUM_ITERATIONS;

    return elapsed_us;
}

template<size_t Iterations, typename Func, typename... Args>
double timeus(Func func, Args&& ...args)
{
    constexpr size_t NUM_ITERATIONS = Iterations;
    int64_t before, after;
    QueryPerformanceCounter((LARGE_INTEGER*) &before);
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    QueryPerformanceCounter((LARGE_INTEGER*) &after);
    int64_t delta = after - before;
    int64_t qpfreq = get_qpfreq();
    double delta_d = static_cast<double>(delta);
    double elapsed_all_us = delta_d / qpfreq;
    double elapsed_us = elapsed_all_us / NUM_ITERATIONS;

    return elapsed_us;
}
#else
template<typename Func, typename... Args>
double timeus(Func func, Args&& ...args)
{
    constexpr size_t NUM_ITERATIONS = 10;
    timespec before, after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    double elapsedus_total = (after.tv_sec - before.tv_sec) * 1e6 + (after.tv_nsec - before.tv_nsec) / 1e3;
    double elapsedus = elapsedus_total / NUM_ITERATIONS;

    return elapsedus;
}

template<size_t Iterations, typename Func, typename... Args>
double timeus(Func func, Args&& ...args)
{
    constexpr size_t NUM_ITERATIONS = Iterations;
    timespec before, after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (size_t i = 0; i < NUM_ITERATIONS; ++i)
    {
        func(std::forward<Args>(args)...);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    double elapsedus_total = (after.tv_sec - before.tv_sec) * 1e6 + (after.tv_nsec - before.tv_nsec) / 1e3;
    double elapsedus = elapsedus_total / NUM_ITERATIONS;

    return elapsedus;
}
#endif

} // namespace toolbox

#endif // INCLUDED_TOOLBOX_HPP