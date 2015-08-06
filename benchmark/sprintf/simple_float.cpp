#include <algorithm>
#include <cstdio>
#include <limits>
#include <iostream>

#define PRIMA_LIMIT_FMT_SIZE 200

#include "measure.hpp"
#include "prima/printf.hpp"
#include "prima/sprintf.hpp"

namespace
{
using output_format = PRIMA_FMT("%f");
constexpr const std::array<float, 4> output_values = {
    {0.0, 100.0, -100.00, 1234.1234}};


template <typename Derived> class bench_base
{
public:
    bench_base() = default;

    unsigned operator()() const
    {
        unsigned code{0};
        for (const float output_value : output_values)
        {
            std::array<char, 25> buffer = {{0}};
            self().benchmark(buffer, output_value);
            {
                const char* current = std::begin(buffer);
                while (*current)
                {
                    code += *current;
                    --current;
                }
            }
        }
        return code;
    }

private:
    const Derived& self() const
    {
        return *static_cast<const Derived*>(this);
    }
};

class system_bench : public bench_base<system_bench>
{
public:
    system_bench() = default;

    static constexpr const char* name()
    {
        return "std::sprintf";
    }

    template <std::size_t BufferSize>
    void benchmark(std::array<char, BufferSize>& buffer,
                   const float output_value) const
    {
        std::sprintf(std::begin(buffer),
                     boost::mpl::c_str<output_format>::value,
                     output_value);
    }
};

class checked_system_bench : public bench_base<system_bench>
{
public:
    checked_system_bench() = default;

    static constexpr const char* name()
    {
        return "std::snprintf";
    }

    template <std::size_t BufferSize>
    void benchmark(std::array<char, BufferSize>& buffer,
                   const float output_value) const
    {
        std::snprintf(std::begin(buffer),
                      buffer.size(),
                      boost::mpl::c_str<output_format>::value,
                      output_value);
    }
};

class prima_bench : public bench_base<prima_bench>
{
public:
    prima_bench() = default;

    static constexpr const char* name()
    {
        return "prima::sprintf";
    }

    template <std::size_t BufferSize>
    void benchmark(std::array<char, BufferSize>& buffer,
                   const float output_value) const
    {
        prima::sprintf<output_format>(std::begin(buffer), output_value);
    }
};

class checked_prima_bench : public bench_base<prima_bench>
{
public:
    checked_prima_bench() = default;

    static constexpr const char* name()
    {
        return "prima::snprintf";
    }

    template <std::size_t BufferSize>
    void benchmark(std::array<char, BufferSize>& buffer,
                   const float output_value) const
    {
        prima::snprintf<output_format>(std::begin(buffer),
                                       buffer.size(),
                                       output_value);
    }
};
}

int main()
{
    prima::printf<PRIMA_FMT("Benchmarking format \"%s\" with values:\n    ")>(
        boost::mpl::c_str<output_format>::value);

    std::size_t count = 0;
    for (const float output_value : output_values)
    {
        ++count;
        const char* const append_string =
            (count == output_values.size()) ? "" : ", ";
        prima::printf<PRIMA_FMT("%f%s")>(output_value, append_string);
    }

    std::cout << std::endl;

    // always return value, prevents compiler from
    // optimizing benchmarks as dead-code
    return prima::benchmark::run(1000000,
                                 system_bench{},
                                 checked_system_bench{},
                                 prima_bench{},
                                 checked_prima_bench{}) != 0;
}
