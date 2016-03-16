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
        const char* get_literal(prima::meta::string<Characters...> const&)
        {
            constexpr static const char string_[] = {Characters..., 0};
            return string_;
        }
    }

    template <typename Backend, typename Format, typename... Args>
    std::string generate(Format const& format, Args const&... args)
    {
        std::string output{};
        prima::sprintf<Backend>(std::back_inserter(output), format, args...);
        {
            const std::size_t buffer_size = output.size() ? output.size() : 1;
            const std::unique_ptr<char[]> buffer(new char[buffer_size]);
            char* const buffer_iterator = buffer.get();

            buffer[buffer_size - 1] = 3;
            BOOST_TEST_EQ(output.size(),
                          (prima::snprintf<Backend>(buffer_iterator,
                                                    format,
                                                    buffer_size - 1,
                                                    args...)));
            BOOST_TEST_EQ(buffer.get(), buffer_iterator);
            BOOST_TEST_EQ(3, buffer[buffer_size - 1]);
        }
        {
            std::string duplicate{};
            duplicate.resize(output.size());
            BOOST_TEST_EQ(output.size(),
                          (prima::snprintf<Backend>(&duplicate[0],
                                                    format,
                                                    duplicate.size(),
                                                    args...)));
            BOOST_TEST_EQ(output, duplicate);
        }
        {
            std::stringstream duplicate{};
            BOOST_TEST((prima::fprintf<Backend>(duplicate, format, args...)));
            BOOST_TEST_EQ(output, duplicate.str());
        }
        {
            std::wstringstream duplicate{};
            BOOST_TEST((prima::fprintf<Backend>(duplicate, format, args...)));
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
                          (prima::snprintf<Backend>(
                              pointer, format, duplicate.size(), args...)));
            BOOST_TEST_EQ(3, *pointer);
            duplicate.pop_back();
            BOOST_TEST_EQ(output, duplicate);
        }
        return output;
    }

    template <typename Backend, typename Format, typename... Args>
    std::string generate_and_system_compare(Format const& format, Args... args)
    {
        const std::string prima_sprintf = generate<Backend>(format, args...);
        {
            std::string system_sprintf{};
            system_sprintf.resize(prima_sprintf.size() + 1);

            BOOST_TEST_EQ(::snprintf(&system_sprintf[0],
                                     system_sprintf.size(),
                                     detail::get_literal(format),
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
