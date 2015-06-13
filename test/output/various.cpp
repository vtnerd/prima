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
    BOOST_TEST_EQ("100", generate<PRIMA_FMT("%u")>(100u));
//    BOOST_TEST(test_format<PRIMA_FMT("%+u")>  ("+100" , 100u));
//    BOOST_TEST(test_format<PRIMA_FMT("%.4u")> ("0100" , 100u));
//    BOOST_TEST(test_format<PRIMA_FMT("%+.4u")>("+0100", 100u));
    return boost::report_errors();
}
