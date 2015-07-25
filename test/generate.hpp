#ifndef PRIMA_TEST_GENERATE_HPP
#define PRIMA_TEST_GENERATE_HPP

#include <cstdio>
#include <memory>
#include <functional>
#include <sstream>
#include <string>
#include <utility>

#include "prima/fprintf.hpp"
#include "prima/sprintf.hpp"

namespace prima
{
namespace test
{
    namespace detail
    {
        template <char... Characters>
        const char* get_literal(const prima::meta::string<Characters...>&)
        {
            constexpr static const char string_[] = {Characters..., 0};
            return string_;
        }
    }

    template <typename Format, typename Backend, typename... Args>
    std::string generate(const Args&... args)
    {
        std::string output{};
        prima::sprintf<Format, Backend>(std::back_inserter(output), args...);
        {
            const std::size_t buffer_size = output.size() ? output.size() : 1;
            const std::unique_ptr<char[]> buffer(new char[buffer_size]);
            char* const buffer_iterator = buffer.get();

            buffer[buffer_size - 1] = 3;
            BOOST_TEST_EQ(output.size(),
                          (prima::snprintf<Format, Backend>(
                              buffer_iterator, buffer_size - 1, args...)));
            BOOST_TEST_EQ(buffer.get(), buffer_iterator);
            BOOST_TEST_EQ(3, buffer[buffer_size - 1]);
        }
        {
            std::string duplicate{};
            duplicate.resize(output.size());
            BOOST_TEST_EQ(output.size(),
                          (prima::snprintf<Format, Backend>(
                              &duplicate[0], duplicate.size(), args...)));
            BOOST_TEST_EQ(output, duplicate);
        }
        {
            std::stringstream duplicate{};
            BOOST_TEST((prima::fprintf<Format, Backend>(duplicate, args...)));
            BOOST_TEST_EQ(output, duplicate.str());
        }
        {
            std::wstringstream duplicate{};
            BOOST_TEST((prima::fprintf<Format, Backend>(duplicate, args...)));
            const std::wstring duplicate_ = duplicate.str();
            if (output.size() == duplicate_.size())
            {
                BOOST_TEST(std::equal(output.begin(),
                                      output.end(),
                                      duplicate_.begin()));
            }
            else
            {
                BOOST_ERROR("wstringstream did not produce proper duplicate");
            }
        }
        if (output.size() < output.max_size())
        {
            std::string duplicate{};
            duplicate.resize(output.size() + 1);
            duplicate[output.size()] = 3;
            auto pointer = &duplicate[0];
            BOOST_TEST_EQ(output.size(),
                          (prima::snprintf<Format, Backend>(
                              pointer, duplicate.size(), args...)));
            BOOST_TEST_EQ(3, *pointer);
            duplicate.pop_back();
            BOOST_TEST_EQ(output, duplicate);
        }
        return output;
    }

    template <typename Format, typename Backend, typename... Args>
    std::string generate_and_system_compare(Args... args)
    {
        const std::string prima_sprintf = generate<Format, Backend>(args...);
        {
            std::string system_sprintf{};
            system_sprintf.resize(prima_sprintf.size() + 1);

            BOOST_TEST_EQ(::snprintf(&system_sprintf[0],
                                     system_sprintf.size(),
                                     detail::get_literal(Format{}),
                                     args...),
                          prima_sprintf.size());

            system_sprintf.resize(prima_sprintf.size());
            BOOST_TEST_EQ(system_sprintf, prima_sprintf);
        }
        return prima_sprintf;
    }
}
}

#endif // PRIMA_TEST_GENERATE_HPP
