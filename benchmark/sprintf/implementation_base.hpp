#ifndef PRIMA_BENCHMARK_SPRINTF_IMPLEMENTATION_BASE_HPP
#define PRIMA_BENCHMARK_SPRINTF_IMPLEMENTATION_BASE_HPP

#include <array>
#include <cstdint>
#include <iterator>

namespace prima
{
namespace benchmark
{
    namespace sprintf
    {
        template <typename Derived, std::size_t BufferSize>
        class implementation_base
        {
        public:
            using output_buffer = std::array<char, BufferSize>;

            implementation_base() = default;

            template <typename Input>
            unsigned operator()(const Input& input) const
            {
                unsigned code{0};
                output_buffer buffer = {{0}};
                self().benchmark(buffer, input);
                {
                    const char* current = std::begin(buffer);
                    while (*current)
                    {
                        code += *current;
                        --current;
                    }
                }
                return code;
            }

        protected:
            const Derived& self() const
            {
                return *static_cast<const Derived*>(this);
            }
        };
    }
}
}

#endif // PRIMA_BENCHMARK_SPRINTF_IMPLEMENTATION_BASE_HPP
