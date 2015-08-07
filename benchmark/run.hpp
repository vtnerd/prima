#ifndef PRIMA_BENCHMARK_RUN_HPP
#define PRIMA_BENCHMARK_RUN_HPP

#include <array>
#include <iostream>
#include <tuple>
#include <vector>

#include <boost/array.hpp> // fusion does not support std::array
#include <boost/io/ios_state.hpp>
#include <boost/fusion/include/array.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/make_fused.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/zip.hpp>
#include <boost/phoenix/bind/bind_function_object.hpp>
#include <boost/phoenix/core/argument.hpp>
#include <boost/phoenix/operator/arithmetic.hpp>

#include "benchmark/scenario.hpp"
#include "benchmark/timer.hpp"
#include "prima/printf.hpp"

namespace prima
{
namespace benchmark
{
    namespace detail
    {
        template <typename Input> class run
        {
        private:
            static constexpr const std::size_t duration = 0;
            static constexpr const std::size_t checksum = 1;

        public:
            using results = std::pair<timer::duration, unsigned>;

            run(const Input& input, const unsigned long trials)
                : input_(input), trials_(trials)
            {
            }

            run(const run&) = default;
            run& operator=(const run&) = default;

            template <typename Implementation>
            void operator()(const Implementation& implementation,
                            results& total) const
            {
                namespace fusion = boost::fusion;
                using namespace boost::phoenix::placeholders;

                const results result = measure(implementation);
                print_average{}(implementation, result, trials_);

                using zip =
                    fusion::zip_view<std::tuple<results&, const results&>>;
                fusion::for_each(zip{std::tie(total, result)},
                                 fusion::make_fused(_1 += _2));
            }

            struct print_average
            {
                using result_type = void;

                template <typename Implementation>
                void operator()(const Implementation& implementation,
                                const results& result,
                                const unsigned long trials) const
                {
                    prima::printf<
                        PRIMA_FMT("%20.20s :%10.6f microseconds per run ")>(
                        implementation.name(),
                        average_microseconds(std::get<duration>(result),
                                             trials));

                    prima::printf<PRIMA_FMT("{checksum: %x}")>(
                        std::get<checksum>(result));
                    std::cout << std::endl;
                }
            };

        private:
            static double average_microseconds(const timer::duration time,
                                               const unsigned long trials)
            {
                using report_duration =
                    std::chrono::duration<double,
                                          std::chrono::microseconds::period>;

                return (std::chrono::duration_cast<report_duration>(time)
                            .count()) /
                       trials;
            }

            template <typename Implementation>
            unsigned execute(const Implementation& implementation) const
            {
                unsigned result{0};
                for (unsigned long iteration{0}; iteration < trials_;
                     ++iteration)
                {
                    result += implementation(input_);
                }

                return result;
            }

            // Measure the time required to hammer accumulators of the given
            // type
            template <typename Implementation>
            results measure(const Implementation& implementation) const
            {
                // Run a few times in an attempt to pull code pages into CPU
                // cache
                execute(implementation);
                execute(implementation);

                timer::duration elapsed{0};
                unsigned result{0};
                {
                    const timer time;
                    result = execute(implementation);
                    elapsed = time.elapsed();
                }
                return {elapsed, result};
            }

        private:
            const Input& input_;
            const unsigned long trials_;
        };
    } // detail

    //! template <typename... Implementations, typename Input>
    //! bool run(const std::tuple<Implementations...>& implementations,
    //!          const std::vector<scenario<Input>>& scenarios,
    //!          const unsigned long trials)
    //!
    //! Runs all `implementations` against all `scenarios`, and prints the
    //! averages of the `trials`. The averages of each scenario is displayed,
    //! along with the average runtime of all `scenarios`.
    //!
    //! \requires All `Implementations` to have a function `name()` that returns
    //!     a `const char*` or `std::string`.
    //! \requires All `Implementations` to be a function object that accepts a
    //!     single parameter of type `Input`, and returns an unsigned value
    //!     that represents a checksum of running against `Input`. The
    //!     calculation for the checksum is unspecified, but it must be computed
    //!     during the run so the compiler doesn't optimize away the entire call
    //!     as dead code.
    //!
    //! \effects Writes to std::cout or std::cerr.
    //!
    //! \note Type erasure is _not_ used for `Implementations` so that direct
    //!     function calls can be made during benchmarking. Otherwise, an
    //!     indirect function call would occur in a loop (`trials`) while an
    //!     implementation was being timed. No need to screw with the CPU
    //!     pipeline during a timed benchmark.
    //!
    //! \throws std::ios_base::failure on write errors to std::cout or std::cerr
    //! \throws std::bad_alloc if a necessary memory allocation failed.
    //!
    //! \returns True iff all `implementations` ran all `scenarios`.
    template <typename... Implementations, typename Input>
    bool run(const std::tuple<Implementations...>& implementations,
             const std::vector<scenario<Input>>& scenarios,
             const unsigned long trials)
    {
        namespace fusion = boost::fusion;
        namespace phoenix = boost::phoenix;
        using namespace phoenix::placeholders;
        using run_ = detail::run<Input>;

        const boost::io::ios_exception_saver save_cout{std::cout};
        const boost::io::ios_exception_saver save_cerr{std::cerr};
        std::cout.exceptions(std::ostream::failbit | std::ostream::badbit);
        std::cerr.exceptions(std::ostream::failbit | std::ostream::badbit);

        if ((std::numeric_limits<unsigned long>::max() / trials) <
            scenarios.size())
        {
            std::cerr << "Maximum trials / scenarios exceeded" << std::endl;
            return false;
        }

        const unsigned long total_trials = trials * scenarios.size();

        if (!timer::is_high_resolution())
        {
            std::cout << "--> Not using high resolution timer <--\n";
        }

        constexpr const std::size_t num_implementations =
            sizeof...(Implementations);
        static_assert(num_implementations >= 2,
                      "multiple implementations required");

        using benchmark_results =
            boost::array<typename run_::results, num_implementations>;

        benchmark_results totals{};
        static_assert(sizeof(totals) <= 2048, "beware of stack overflow");

        for (const scenario<Input>& active_scenario : scenarios)
        {
            prima::printf<PRIMA_FMT(
                "Running %s benchmark %u times for each implementation...")>(
                active_scenario.name(), trials);
            std::cout << std::endl;

            using zip = fusion::zip_view<
                std::tuple<const std::tuple<Implementations...>&,
                           benchmark_results&>>;

            fusion::for_each(zip{std::tie(implementations, totals)},
                             fusion::make_fused(
                                 run_{active_scenario.input(), trials}));
        }

        std::cout << "\nBenchmark averages:\n";
        fusion::for_each(
            fusion::zip(implementations, totals),
            fusion::make_fused(phoenix::bind(
                typename run_::print_average{}, _1, _2, total_trials)));
        std::cout << std::flush;
        
        return true;
    }
} // benchmark
} // prima

#endif // PRIMA_BENCHMARK_RUN_HPP
