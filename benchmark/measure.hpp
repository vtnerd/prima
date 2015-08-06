#ifndef PRIMA_BENCHMARK_MEASURE_HPP
#define PRIMA_BENCHMARK_MEASURE_HPP

#include <iostream>

#include "timer.hpp"
#include "prima/printf.hpp"

namespace prima
{
namespace benchmark
{
    namespace detail
    {
        template <typename Benchmark>
        unsigned run(const Benchmark& benchmark, const unsigned long repeats)
        {
            unsigned result{0};
            for (unsigned long iteration{0}; iteration < repeats; ++iteration)
            {
                result += benchmark();
            }

            return result;
        }

        // Measure the time required to hammer accumulators of the given type
        template <typename Benchmark>
        std::pair<timer::duration, unsigned>
        measure(const Benchmark& benchmark, unsigned long const repeats)
        {
            // Run a few times in an attempt to pull code pages into CPU cache
            run(benchmark, repeats);
            run(benchmark, repeats);

            timer::duration elapsed{0};
            unsigned result{0};
            {
                const timer time;
                result = run(benchmark, repeats);
                elapsed = time.elapsed();
            }
            return std::make_pair(elapsed, result);
        }

        template <typename Benchmark>
        unsigned report(const Benchmark& benchmark, unsigned long const repeats)
        {
            namespace karma = boost::spirit::karma;
            using report_duration =
                std::chrono::duration<double, std::chrono::microseconds::period>;

            const auto measured = measure(benchmark, repeats);
            const double average = (std::chrono::duration_cast<report_duration>(
                                        measured.first).count()) /
                                   repeats;

            prima::printf<PRIMA_FMT("%20.20s :%10.6f microseconds per run ")>(
                Benchmark::name(), average);

            prima::printf<PRIMA_FMT("{checksum: %x}")>(measured.second);
            std::cout << std::endl;
            return measured.second;
        }

        template <typename Last>
        unsigned report_all(const unsigned long repeats, const Last& last)
        {
            return report(last, repeats);
        }

        template <typename First, typename Second, typename... Tail>
        unsigned report_all(const unsigned long repeats,
                            const First& first,
                            const Second& second,
                            const Tail&... tail)
        {
            return report(first, repeats) +
                   report_all(repeats, second, tail...);
        }
    } // detail

    //! template<typename... Benchmarks>
    //! unsigned run(
    //!     const unsigned long repeats, const Benchmark&... benchmarks)
    //!
    //! Runs all `benchmarks` for `repeats` times. Timng results of benchmarks
    //! are printed to std::cout.
    //!
    //! \returns The sum of the return values from all of the `benchmarks` runs.
    template <typename... Benchmarks>
    unsigned run(const unsigned long repeats, const Benchmarks&... benchmarks)
    {
        static_assert(sizeof...(Benchmarks) >= 2,
                      "need two entries for benchmarking");
        if (!timer::is_high_resolution())
        {
            std::cout << "--> Not using high resolution timer <--\n";
        }

        prima::printf<PRIMA_FMT("Benchmarking with %u runs each...")>(repeats);
        std::cout << std::endl;

        return detail::report_all(repeats, benchmarks...);
    }
} // benchmark
} // prima

#endif // PRIMA_BENCHMARK_MEASURE_HPP
