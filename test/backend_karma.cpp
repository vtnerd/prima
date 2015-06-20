#include <limits>
#include <utility>

#include <boost/detail/lightweight_test.hpp>

#include "prima/meta/base.hpp"
#include "prima/sprintf.hpp"

namespace
{
    template<char... Characters>
    const char* get_literal(const prima::meta::string<Characters...>&)
    {
        constexpr static const char string_[] = {Characters..., 0};
        return string_;
    }

    template<typename Format, typename... Args>
    std::string generate(const Args&... args)
    {
        std::string output{};
        BOOST_TEST(prima::sprintf<Format>(std::back_inserter(output), args...));
        return output;
    }

    template<typename Format, typename... Args>
    std::string generate_and_system_compare(Args... args)
    {
        const std::string karma_sprintf = generate<Format>(args...);
        {
            std::string system_sprintf{};
            system_sprintf.resize(karma_sprintf.size() + 1);

            BOOST_TEST_EQ(
                karma_sprintf.size(),
                ::snprintf(&system_sprintf[0], system_sprintf.size(), get_literal(Format{}), args...));

            system_sprintf.resize(karma_sprintf.size());
            BOOST_TEST_EQ(system_sprintf, karma_sprintf);
        }
        return karma_sprintf;
    }
}

void float_tests()
{
    BOOST_TEST_EQ("0.000000", generate_and_system_compare<PRIMA_FMT("%f")>(0.0f));
    BOOST_TEST_EQ("1.000000", generate_and_system_compare<PRIMA_FMT("%f")>(1.0f));
    BOOST_TEST_EQ("-1.000000", generate_and_system_compare<PRIMA_FMT("%f")>(-1.0f));
    BOOST_TEST_EQ("1.500000", generate_and_system_compare<PRIMA_FMT("%f")>(1.5f));
    BOOST_TEST_EQ("-1.500000", generate_and_system_compare<PRIMA_FMT("%f")>(-1.5f));
    BOOST_TEST_EQ("0.000", generate_and_system_compare<PRIMA_FMT("%.3f")>(0.0f));
    BOOST_TEST_EQ("1.000", generate_and_system_compare<PRIMA_FMT("%.3f")>(1.0f));
    BOOST_TEST_EQ("-1.000", generate_and_system_compare<PRIMA_FMT("%.3f")>(-1.0f));
    BOOST_TEST_EQ("1.500", generate_and_system_compare<PRIMA_FMT("%.3f")>(1.5f));
    BOOST_TEST_EQ("-1.500", generate_and_system_compare<PRIMA_FMT("%.3f")>(-1.5f));
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%.0f")>(0.0f));
    BOOST_TEST_EQ("1", generate_and_system_compare<PRIMA_FMT("%.0f")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("%.0f")>(-1.0f));
    BOOST_TEST_EQ("2", generate_and_system_compare<PRIMA_FMT("%.0f")>(1.5f));
    BOOST_TEST_EQ("-2", generate_and_system_compare<PRIMA_FMT("%.0f")>(-1.5f));
    BOOST_TEST_EQ("0.", generate_and_system_compare<PRIMA_FMT("%#.0f")>(0.0f));
    BOOST_TEST_EQ("1.", generate_and_system_compare<PRIMA_FMT("%#.0f")>(1.0f));
    BOOST_TEST_EQ("-1.", generate_and_system_compare<PRIMA_FMT("%#.0f")>(-1.0f));
    BOOST_TEST_EQ("2.", generate_and_system_compare<PRIMA_FMT("%#.0f")>(1.5f));
    BOOST_TEST_EQ("-2.", generate_and_system_compare<PRIMA_FMT("%#.0f")>(-1.5f));
    BOOST_TEST_EQ("0.0000000", generate_and_system_compare<PRIMA_FMT("%#.7f")>(0.0f));
    BOOST_TEST_EQ("1.0000000", generate_and_system_compare<PRIMA_FMT("%#.7f")>(1.0f));
    BOOST_TEST_EQ("-1.0000000", generate_and_system_compare<PRIMA_FMT("%#.7f")>(-1.0f));
    BOOST_TEST_EQ("1.5000000", generate_and_system_compare<PRIMA_FMT("%#.7f")>(1.5f));
    BOOST_TEST_EQ("-1.5000000", generate_and_system_compare<PRIMA_FMT("%#.7f")>(-1.5f));
    BOOST_TEST_EQ(" 0.0", generate_and_system_compare<PRIMA_FMT("% .1f")>(0.0f));
    BOOST_TEST_EQ(" 1.0", generate_and_system_compare<PRIMA_FMT("% .1f")>(1.0f));
    BOOST_TEST_EQ("-1.0", generate_and_system_compare<PRIMA_FMT("% .1f")>(-1.0f));
    BOOST_TEST_EQ(" 1.5", generate_and_system_compare<PRIMA_FMT("% .1f")>(1.5f));
    BOOST_TEST_EQ("-1.5", generate_and_system_compare<PRIMA_FMT("% .1f")>(-1.5f));
    BOOST_TEST_EQ("+0.0", generate_and_system_compare<PRIMA_FMT("%+.1f")>(0.0f));
    BOOST_TEST_EQ("+1.0", generate_and_system_compare<PRIMA_FMT("%+.1f")>(1.0f));
    BOOST_TEST_EQ("-1.0", generate_and_system_compare<PRIMA_FMT("%+.1f")>(-1.0f));
    BOOST_TEST_EQ("+1.5", generate_and_system_compare<PRIMA_FMT("%+.1f")>(1.5f));
    BOOST_TEST_EQ("-1.5", generate_and_system_compare<PRIMA_FMT("%+.1f")>(-1.5f));
}

void int_tests()
{
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%i")>(0));
    BOOST_TEST_EQ("100", generate_and_system_compare<PRIMA_FMT("%i")>(100));
    BOOST_TEST_EQ("-9223372036854775808", generate<PRIMA_FMT("%+i")>(std::numeric_limits<std::int64_t>::min()));
    BOOST_TEST_EQ("+9223372036854775807", generate<PRIMA_FMT("%+i")>(std::numeric_limits<std::int64_t>::max()));
}

void string_tests()
{
    BOOST_TEST_EQ("|report string|", generate_and_system_compare<PRIMA_FMT("|%s|")>("report string"));
    BOOST_TEST_EQ("|repor|", generate_and_system_compare<PRIMA_FMT("|%.5s|")>("report string"));
    BOOST_TEST_EQ("| repor|", generate_and_system_compare<PRIMA_FMT("|%6.5s|")>("report string"));
    BOOST_TEST_EQ("|repo   |", generate_and_system_compare<PRIMA_FMT("|%-6.4s |")>("report string"));
}

void unsigned_tests()
{
    // decimal
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%u")>(0u));
    BOOST_TEST_EQ("100", generate_and_system_compare<PRIMA_FMT("%u")>(100u));
    BOOST_TEST_EQ("18446744073709551615", generate<PRIMA_FMT("%u")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0100", generate_and_system_compare<PRIMA_FMT("%.4u")>(100u));
    BOOST_TEST_EQ(" 0100", generate_and_system_compare<PRIMA_FMT("%5.4u")>(100u));

    // octal
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%o")>(0u));
    BOOST_TEST_EQ("144", generate_and_system_compare<PRIMA_FMT("%o")>(100u));
    BOOST_TEST_EQ("1777777777777777777777", generate<PRIMA_FMT("%o")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0144", generate_and_system_compare<PRIMA_FMT("%.4o")>(100u));
    BOOST_TEST_EQ(" 0144", generate_and_system_compare<PRIMA_FMT("%5.4o")>(100u));

    // lower case hex
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%x")>(0u));
    BOOST_TEST_EQ("64", generate_and_system_compare<PRIMA_FMT("%x")>(100u));
    BOOST_TEST_EQ("ffffffffffffffff", generate<PRIMA_FMT("%x")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0064", generate_and_system_compare<PRIMA_FMT("%.4x")>(100u));
    BOOST_TEST_EQ(" 0064", generate_and_system_compare<PRIMA_FMT("%5.4x")>(100u));
}

int main()
{
    BOOST_TEST_EQ("<-->", generate<PRIMA_FMT("<-->")>());
    float_tests();
    int_tests();
    string_tests();
    unsigned_tests();
    return boost::report_errors();
}
