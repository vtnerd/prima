#include <limits>
#include <utility>

#include <boost/detail/lightweight_test.hpp>

#include "prima/sprintf.hpp"

namespace
{
    template<typename Format, typename... Args>
    std::string generate(Args&&... args)
    {
        std::string output{};
        prima::sprintf<Format>(std::back_inserter(output), std::forward<Args>(args)...);
        return output;
    }
}

int main()
{
//    BOOST_TEST_EQ("<-->", generate<PRIMA_FMT("<-->")>());

    BOOST_TEST_EQ("0", generate<PRIMA_FMT("%u")>(0u));
    BOOST_TEST_EQ("100", generate<PRIMA_FMT("%u")>(100u));
    BOOST_TEST_EQ("+18446744073709551615", generate<PRIMA_FMT("%+u")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0100", generate<PRIMA_FMT("%.4u")>(100u));
    BOOST_TEST_EQ("+0100", generate<PRIMA_FMT("%+.4u")>(100u));
    BOOST_TEST_EQ(" 0100", generate<PRIMA_FMT("% .4u")>(100u));

/*    BOOST_TEST_EQ("0", generate<PRIMA_FMT("%x")>(0u));
    BOOST_TEST_EQ("100", generate<PRIMA_FMT("%x")>(100));
    BOOST_TEST_EQ("+18446744073709551615", generate<PRIMA_FMT("%+x")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0100", generate<PRIMA_FMT("%.4x")>(100u));
    BOOST_TEST_EQ("+0100", generate<PRIMA_FMT("%+.4x")>(100u));
    BOOST_TEST_EQ(" 0100", generate<PRIMA_FMT("% .4x")>(100u)); */

    BOOST_TEST_EQ("0", generate<PRIMA_FMT("%i")>(0));
    BOOST_TEST_EQ("100", generate<PRIMA_FMT("%i")>(100));
    BOOST_TEST_EQ("-9223372036854775808", generate<PRIMA_FMT("%+i")>(std::numeric_limits<std::int64_t>::min()));
    BOOST_TEST_EQ("+9223372036854775807", generate<PRIMA_FMT("%+i")>(std::numeric_limits<std::int64_t>::max()));

    BOOST_TEST_EQ("|report string|", generate<PRIMA_FMT("|%s|")>("report string"));
    BOOST_TEST_EQ("|repor|", generate<PRIMA_FMT("|%.5s|")>("report string"));
    BOOST_TEST_EQ("| repor|", generate<PRIMA_FMT("|%6.5s|")>("report string"));
    BOOST_TEST_EQ("|repo   |", generate<PRIMA_FMT("|%-6.4s |")>("report string"));

    return boost::report_errors();
}
