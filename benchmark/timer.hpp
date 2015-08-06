#ifndef PRIMA_BENCHMARK_TIMER_HPP
#define PRIMA_BENCHMARK_TIMER_HPP

#include <chrono>

#include "prima/meta/funcs.hpp"

namespace prima
{
namespace benchmark
{
    class timer
    {
    public:
        static constexpr bool is_high_resolution()
        {
            return std::chrono::high_resolution_clock::is_steady;
        }

        using clock_type = meta::if_t<
            meta::bool_<std::chrono::high_resolution_clock::is_steady>,
            std::chrono::high_resolution_clock,
            std::chrono::steady_clock>;
        using duration = clock_type::duration;

        timer() : start_time(clock_type::now())
        {
        }

        duration elapsed() const
        {
            return clock_type::now() - start_time;
        }

    private:
        const clock_type::time_point start_time;
    };
}
}

#endif // PRIMA_BENCHMARK_TIMER_HPP
