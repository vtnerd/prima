#ifndef PRIMA_BENCHMARK_SCENARIO_HPP
#define PRIMA_BENCHMARK_SCENARIO_HPP

namespace prima
{
namespace benchmark
{
    template <typename Input> class scenario
    {
    public:
        scenario(std::string name, Input input)
            : name_(std::move(name)), input_(std::move(input))
        {
        }

        scenario(scenario&&) = default;

        const std::string& name() const
        {
          return name_;
        }

        const Input& input() const
        {
            return input_;
        }

    private:
        scenario(const scenario&) = delete;
        scenario& operator=(const scenario&) = delete;
        scenario& operator=(scenario&&) = delete;

    private:
        const std::string name_;
        const Input input_;
    };
}
}

#endif // PRIMA_BENCHMARK_SCENARIO_HPP
