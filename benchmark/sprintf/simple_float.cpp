#include <cstdio>
#include <iterator>
#include <tuple>

#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>

#define PRIMA_LIMIT_FMT_SIZE 200

#include "benchmark/run.hpp"
#include "benchmark/scenario.hpp"
#include "benchmark/sprintf/implementation_base.hpp"
#include "prima/printf.hpp"
#include "prima/sprintf.hpp"

namespace
{
//
// Benchmark Configuration
//
constexpr const unsigned long trials = 1000000;
constexpr const std::array<float, 4> inputs{{-100.0, 0.0, 100.0, 1234.1234}};
using output_format = decltype(PRIMA_FMT("%f"));


//
// Benchmark Code
//
template <typename Derived>
using simple_float_base =
    prima::benchmark::sprintf::implementation_base<Derived, 16>;

class system_impl : public simple_float_base<system_impl>
{
public:
    system_impl() = default;

    static constexpr const char* name()
    {
        return "std::sprintf";
    }

    void benchmark(output_buffer& buffer, const float input) const
    {
        std::sprintf(std::begin(buffer),
                     boost::mpl::c_str<output_format>::value,
                     input);
    }
};

class checked_system_impl : public simple_float_base<system_impl>
{
public:
    checked_system_impl() = default;

    static constexpr const char* name()
    {
        return "std::snprintf";
    }

    void benchmark(output_buffer& buffer, const float input) const
    {
        std::snprintf(std::begin(buffer),
                      buffer.size(),
                      boost::mpl::c_str<output_format>::value,
                      input);
    }
};

class prima_impl : public simple_float_base<prima_impl>
{
public:
    prima_impl() = default;

    static constexpr const char* name()
    {
        return "prima::sprintf";
    }

    void benchmark(output_buffer& buffer, const float input) const
    {
        prima::sprintf(std::begin(buffer), output_format{}, input);
    }
};

class checked_prima_impl : public simple_float_base<prima_impl>
{
public:
    checked_prima_impl() = default;

    static constexpr const char* name()
    {
        return "prima::snprintf";
    }

    void benchmark(output_buffer& buffer, const float input) const
    {
        prima::snprintf(
            std::begin(buffer), output_format{}, buffer.size(), input);
    }
};

struct MakeScenario
{
    using result_type = prima::benchmark::scenario<float>;

    MakeScenario() = default;

    result_type operator()(const float input) const
    {
        std::string name{};
        prima::sprintf(std::back_inserter(name),
                       PRIMA_FMT("\"%s\" with input %f"),
                       boost::mpl::c_str<output_format>::value,
                       input);
        return {std::move(name), input};
    }
};
}

int main()
{
    namespace adaptors = boost::adaptors;
    namespace range = boost::range;

    std::vector<prima::benchmark::scenario<float>> scenarios{};
    scenarios.reserve(inputs.size());
    range::copy(inputs | adaptors::transformed(MakeScenario{}),
                std::back_inserter(scenarios));

    using implementations = std::
        tuple<system_impl, checked_system_impl, prima_impl, checked_prima_impl>;
    return !prima::benchmark::run(implementations{},
                                  std::move(scenarios),
                                  trials);
}
