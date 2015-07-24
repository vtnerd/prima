#include <limits>
#include <utility>

#include <boost/detail/lightweight_test.hpp>
#include <boost/version.hpp>

#include "prima/meta/base.hpp"
#include "prima/sprintf.hpp"

#define PRIMA_BOOST_MAJOR (BOOST_VERSION / 100000)
#define PRIMA_BOOST_MINOR ((BOOST_VERSION / 100) % 1000)

#if (PRIMA_BOOST_MAJOR > 1) || (PRIMA_BOOST_MAJOR == 1 && PRIMA_BOOST_MINOR >= 59)
  #define PRIMA_NO_LEFT_ALIGN_BUG
#endif

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
                ::snprintf(&system_sprintf[0], system_sprintf.size(), get_literal(Format{}), args...),
                karma_sprintf.size());

            system_sprintf.resize(karma_sprintf.size());
            BOOST_TEST_EQ(system_sprintf, karma_sprintf);
        }
        return karma_sprintf;
    }
}

void float_tests()
{
    // fixed format
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
    BOOST_TEST_EQ("0.1", generate_and_system_compare<PRIMA_FMT("%.1f")>(0.05f));
    BOOST_TEST_EQ("-0.1", generate_and_system_compare<PRIMA_FMT("%.1f")>(-0.05f));
    BOOST_TEST_EQ("nan", generate<PRIMA_FMT("%f")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("inf", generate<PRIMA_FMT("%f")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("+nan", generate<PRIMA_FMT("%+f")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("+inf", generate<PRIMA_FMT("%+f")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ(" nan", generate<PRIMA_FMT("% f")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ(" inf", generate<PRIMA_FMT("% f")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("-nan", generate<PRIMA_FMT("%f")>(-std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("-inf", generate<PRIMA_FMT("%f")>(-std::numeric_limits<float>::infinity()));

    // fixed format (upper case)
    BOOST_TEST_EQ("0.000000", generate_and_system_compare<PRIMA_FMT("%F")>(0.0f));
    BOOST_TEST_EQ("1.000000", generate_and_system_compare<PRIMA_FMT("%F")>(1.0f));
    BOOST_TEST_EQ("-1.000000", generate_and_system_compare<PRIMA_FMT("%F")>(-1.0f));
    BOOST_TEST_EQ("1.500000", generate_and_system_compare<PRIMA_FMT("%F")>(1.5f));
    BOOST_TEST_EQ("-1.500000", generate_and_system_compare<PRIMA_FMT("%F")>(-1.5f));
    BOOST_TEST_EQ("0.000", generate_and_system_compare<PRIMA_FMT("%.3F")>(0.0f));
    BOOST_TEST_EQ("1.000", generate_and_system_compare<PRIMA_FMT("%.3F")>(1.0f));
    BOOST_TEST_EQ("-1.000", generate_and_system_compare<PRIMA_FMT("%.3F")>(-1.0f));
    BOOST_TEST_EQ("1.500", generate_and_system_compare<PRIMA_FMT("%.3F")>(1.5f));
    BOOST_TEST_EQ("-1.500", generate_and_system_compare<PRIMA_FMT("%.3F")>(-1.5f));
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%.0F")>(0.0f));
    BOOST_TEST_EQ("1", generate_and_system_compare<PRIMA_FMT("%.0F")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("%.0F")>(-1.0f));
    BOOST_TEST_EQ("2", generate_and_system_compare<PRIMA_FMT("%.0F")>(1.5f));
    BOOST_TEST_EQ("-2", generate_and_system_compare<PRIMA_FMT("%.0F")>(-1.5f));
    BOOST_TEST_EQ("0.", generate_and_system_compare<PRIMA_FMT("%#.0F")>(0.0f));
    BOOST_TEST_EQ("1.", generate_and_system_compare<PRIMA_FMT("%#.0F")>(1.0f));
    BOOST_TEST_EQ("-1.", generate_and_system_compare<PRIMA_FMT("%#.0F")>(-1.0f));
    BOOST_TEST_EQ("2.", generate_and_system_compare<PRIMA_FMT("%#.0F")>(1.5f));
    BOOST_TEST_EQ("-2.", generate_and_system_compare<PRIMA_FMT("%#.0F")>(-1.5f));
    BOOST_TEST_EQ("0.0000000", generate_and_system_compare<PRIMA_FMT("%#.7F")>(0.0f));
    BOOST_TEST_EQ("1.0000000", generate_and_system_compare<PRIMA_FMT("%#.7F")>(1.0f));
    BOOST_TEST_EQ("-1.0000000", generate_and_system_compare<PRIMA_FMT("%#.7F")>(-1.0f));
    BOOST_TEST_EQ("1.5000000", generate_and_system_compare<PRIMA_FMT("%#.7F")>(1.5f));
    BOOST_TEST_EQ("-1.5000000", generate_and_system_compare<PRIMA_FMT("%#.7F")>(-1.5f));
    BOOST_TEST_EQ(" 0.0", generate_and_system_compare<PRIMA_FMT("% .1F")>(0.0f));
    BOOST_TEST_EQ(" 1.0", generate_and_system_compare<PRIMA_FMT("% .1F")>(1.0f));
    BOOST_TEST_EQ("-1.0", generate_and_system_compare<PRIMA_FMT("% .1F")>(-1.0f));
    BOOST_TEST_EQ(" 1.5", generate_and_system_compare<PRIMA_FMT("% .1F")>(1.5f));
    BOOST_TEST_EQ("-1.5", generate_and_system_compare<PRIMA_FMT("% .1F")>(-1.5f));
    BOOST_TEST_EQ("+0.0", generate_and_system_compare<PRIMA_FMT("%+.1F")>(0.0f));
    BOOST_TEST_EQ("+1.0", generate_and_system_compare<PRIMA_FMT("%+.1F")>(1.0f));
    BOOST_TEST_EQ("-1.0", generate_and_system_compare<PRIMA_FMT("%+.1F")>(-1.0f));
    BOOST_TEST_EQ("+1.5", generate_and_system_compare<PRIMA_FMT("%+.1F")>(1.5f));
    BOOST_TEST_EQ("-1.5", generate_and_system_compare<PRIMA_FMT("%+.1F")>(-1.5f));
    BOOST_TEST_EQ("0.1", generate_and_system_compare<PRIMA_FMT("%.1F")>(0.05f));
    BOOST_TEST_EQ("-0.1", generate_and_system_compare<PRIMA_FMT("%.1F")>(-0.05f));
    BOOST_TEST_EQ("NAN", generate<PRIMA_FMT("%F")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("INF", generate<PRIMA_FMT("%F")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("+NAN", generate<PRIMA_FMT("%+F")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("+INF", generate<PRIMA_FMT("%+F")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ(" NAN", generate<PRIMA_FMT("% F")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ(" INF", generate<PRIMA_FMT("% F")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("-NAN", generate<PRIMA_FMT("%F")>(-std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("-INF", generate<PRIMA_FMT("%F")>(-std::numeric_limits<float>::infinity()));

    // scientific format
    BOOST_TEST_EQ("0.000000e+00", generate_and_system_compare<PRIMA_FMT("%e")>(0.0f));
    BOOST_TEST_EQ("1.000000e+00", generate_and_system_compare<PRIMA_FMT("%e")>(1.0f));
    BOOST_TEST_EQ("-1.000000e+00", generate_and_system_compare<PRIMA_FMT("%e")>(-1.0f));
    BOOST_TEST_EQ("1.500000e+00", generate_and_system_compare<PRIMA_FMT("%e")>(1.5f));
    BOOST_TEST_EQ("-1.500000e+00", generate_and_system_compare<PRIMA_FMT("%e")>(-1.5f));
    BOOST_TEST_EQ("0.000e+00", generate_and_system_compare<PRIMA_FMT("%.3e")>(0.0f));
    BOOST_TEST_EQ("1.000e+00", generate_and_system_compare<PRIMA_FMT("%.3e")>(1.0f));
    BOOST_TEST_EQ("-1.000e+00", generate_and_system_compare<PRIMA_FMT("%.3e")>(-1.0f));
    BOOST_TEST_EQ("1.500e+00", generate_and_system_compare<PRIMA_FMT("%.3e")>(1.5f));
    BOOST_TEST_EQ("-1.500e+00", generate_and_system_compare<PRIMA_FMT("%.3e")>(-1.5f));
    BOOST_TEST_EQ("0e+00", generate_and_system_compare<PRIMA_FMT("%.0e")>(0.0f));
    BOOST_TEST_EQ("1e+00", generate_and_system_compare<PRIMA_FMT("%.0e")>(1.0f));
    BOOST_TEST_EQ("-1e+00", generate_and_system_compare<PRIMA_FMT("%.0e")>(-1.0f));
    BOOST_TEST_EQ("2e+00", generate_and_system_compare<PRIMA_FMT("%.0e")>(1.5f));
    BOOST_TEST_EQ("-2e+00", generate_and_system_compare<PRIMA_FMT("%.0e")>(-1.5f));
    BOOST_TEST_EQ("0.e+00", generate_and_system_compare<PRIMA_FMT("%#.0e")>(0.0f));
    BOOST_TEST_EQ("1.e+00", generate_and_system_compare<PRIMA_FMT("%#.0e")>(1.0f));
    BOOST_TEST_EQ("-1.e+00", generate_and_system_compare<PRIMA_FMT("%#.0e")>(-1.0f));
    BOOST_TEST_EQ("2.e+00", generate_and_system_compare<PRIMA_FMT("%#.0e")>(1.5f));
    BOOST_TEST_EQ("-2.e+00", generate_and_system_compare<PRIMA_FMT("%#.0e")>(-1.5f));
    BOOST_TEST_EQ("0.0000000e+00", generate_and_system_compare<PRIMA_FMT("%#.7e")>(0.0f));
    BOOST_TEST_EQ("1.0000000e+00", generate_and_system_compare<PRIMA_FMT("%#.7e")>(1.0f));
    BOOST_TEST_EQ("-1.0000000e+00", generate_and_system_compare<PRIMA_FMT("%#.7e")>(-1.0f));
    BOOST_TEST_EQ("1.5000000e+00", generate_and_system_compare<PRIMA_FMT("%#.7e")>(1.5f));
    BOOST_TEST_EQ("-1.5000000e+00", generate_and_system_compare<PRIMA_FMT("%#.7e")>(-1.5f));
    BOOST_TEST_EQ(" 0.0e+00", generate_and_system_compare<PRIMA_FMT("% .1e")>(0.0f));
    BOOST_TEST_EQ(" 1.0e+00", generate_and_system_compare<PRIMA_FMT("% .1e")>(1.0f));
    BOOST_TEST_EQ("-1.0e+00", generate_and_system_compare<PRIMA_FMT("% .1e")>(-1.0f));
    BOOST_TEST_EQ(" 1.5e+00", generate_and_system_compare<PRIMA_FMT("% .1e")>(1.5f));
    BOOST_TEST_EQ("-1.5e+00", generate_and_system_compare<PRIMA_FMT("% .1e")>(-1.5f));
    BOOST_TEST_EQ("+0.0e+00", generate_and_system_compare<PRIMA_FMT("%+.1e")>(0.0f));
    BOOST_TEST_EQ("+1.0e+00", generate_and_system_compare<PRIMA_FMT("%+.1e")>(1.0f));
    BOOST_TEST_EQ("-1.0e+00", generate_and_system_compare<PRIMA_FMT("%+.1e")>(-1.0f));
    BOOST_TEST_EQ("+1.5e+00", generate_and_system_compare<PRIMA_FMT("%+.1e")>(1.5f));
    BOOST_TEST_EQ("-1.5e+00", generate_and_system_compare<PRIMA_FMT("%+.1e")>(-1.5f));
    BOOST_TEST_EQ("5.0e-02", generate_and_system_compare<PRIMA_FMT("%.1e")>(0.05f));
    BOOST_TEST_EQ("-5.0e-02", generate_and_system_compare<PRIMA_FMT("%.1e")>(-0.05f));
    BOOST_TEST_EQ("1.000050e+05", generate_and_system_compare<PRIMA_FMT("%e")>(100005.0f));
    BOOST_TEST_EQ("-1.000050e+05", generate_and_system_compare<PRIMA_FMT("%e")>(-100005.0f));
    BOOST_TEST_EQ("nan", generate<PRIMA_FMT("%e")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("inf", generate<PRIMA_FMT("%e")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("+nan", generate<PRIMA_FMT("%+e")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("+inf", generate<PRIMA_FMT("%+e")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ(" nan", generate<PRIMA_FMT("% e")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ(" inf", generate<PRIMA_FMT("% e")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("-nan", generate<PRIMA_FMT("%e")>(-std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("-inf", generate<PRIMA_FMT("%e")>(-std::numeric_limits<float>::infinity()));

    // scientific format (upper case)
    BOOST_TEST_EQ("0.000000E+00", generate_and_system_compare<PRIMA_FMT("%E")>(0.0f));
    BOOST_TEST_EQ("1.000000E+00", generate_and_system_compare<PRIMA_FMT("%E")>(1.0f));
    BOOST_TEST_EQ("-1.000000E+00", generate_and_system_compare<PRIMA_FMT("%E")>(-1.0f));
    BOOST_TEST_EQ("1.500000E+00", generate_and_system_compare<PRIMA_FMT("%E")>(1.5f));
    BOOST_TEST_EQ("-1.500000E+00", generate_and_system_compare<PRIMA_FMT("%E")>(-1.5f));
    BOOST_TEST_EQ("0.000E+00", generate_and_system_compare<PRIMA_FMT("%.3E")>(0.0f));
    BOOST_TEST_EQ("1.000E+00", generate_and_system_compare<PRIMA_FMT("%.3E")>(1.0f));
    BOOST_TEST_EQ("-1.000E+00", generate_and_system_compare<PRIMA_FMT("%.3E")>(-1.0f));
    BOOST_TEST_EQ("1.500E+00", generate_and_system_compare<PRIMA_FMT("%.3E")>(1.5f));
    BOOST_TEST_EQ("-1.500E+00", generate_and_system_compare<PRIMA_FMT("%.3E")>(-1.5f));
    BOOST_TEST_EQ("0E+00", generate_and_system_compare<PRIMA_FMT("%.0E")>(0.0f));
    BOOST_TEST_EQ("1E+00", generate_and_system_compare<PRIMA_FMT("%.0E")>(1.0f));
    BOOST_TEST_EQ("-1E+00", generate_and_system_compare<PRIMA_FMT("%.0E")>(-1.0f));
    BOOST_TEST_EQ("2E+00", generate_and_system_compare<PRIMA_FMT("%.0E")>(1.5f));
    BOOST_TEST_EQ("-2E+00", generate_and_system_compare<PRIMA_FMT("%.0E")>(-1.5f));
    BOOST_TEST_EQ("0.E+00", generate_and_system_compare<PRIMA_FMT("%#.0E")>(0.0f));
    BOOST_TEST_EQ("1.E+00", generate_and_system_compare<PRIMA_FMT("%#.0E")>(1.0f));
    BOOST_TEST_EQ("-1.E+00", generate_and_system_compare<PRIMA_FMT("%#.0E")>(-1.0f));
    BOOST_TEST_EQ("2.E+00", generate_and_system_compare<PRIMA_FMT("%#.0E")>(1.5f));
    BOOST_TEST_EQ("-2.E+00", generate_and_system_compare<PRIMA_FMT("%#.0E")>(-1.5f));
    BOOST_TEST_EQ("0.0000000E+00", generate_and_system_compare<PRIMA_FMT("%#.7E")>(0.0f));
    BOOST_TEST_EQ("1.0000000E+00", generate_and_system_compare<PRIMA_FMT("%#.7E")>(1.0f));
    BOOST_TEST_EQ("-1.0000000E+00", generate_and_system_compare<PRIMA_FMT("%#.7E")>(-1.0f));
    BOOST_TEST_EQ("1.5000000E+00", generate_and_system_compare<PRIMA_FMT("%#.7E")>(1.5f));
    BOOST_TEST_EQ("-1.5000000E+00", generate_and_system_compare<PRIMA_FMT("%#.7E")>(-1.5f));
    BOOST_TEST_EQ(" 0.0E+00", generate_and_system_compare<PRIMA_FMT("% .1E")>(0.0f));
    BOOST_TEST_EQ(" 1.0E+00", generate_and_system_compare<PRIMA_FMT("% .1E")>(1.0f));
    BOOST_TEST_EQ("-1.0E+00", generate_and_system_compare<PRIMA_FMT("% .1E")>(-1.0f));
    BOOST_TEST_EQ(" 1.5E+00", generate_and_system_compare<PRIMA_FMT("% .1E")>(1.5f));
    BOOST_TEST_EQ("-1.5E+00", generate_and_system_compare<PRIMA_FMT("% .1E")>(-1.5f));
    BOOST_TEST_EQ("+0.0E+00", generate_and_system_compare<PRIMA_FMT("%+.1E")>(0.0f));
    BOOST_TEST_EQ("+1.0E+00", generate_and_system_compare<PRIMA_FMT("%+.1E")>(1.0f));
    BOOST_TEST_EQ("-1.0E+00", generate_and_system_compare<PRIMA_FMT("%+.1E")>(-1.0f));
    BOOST_TEST_EQ("+1.5E+00", generate_and_system_compare<PRIMA_FMT("%+.1E")>(1.5f));
    BOOST_TEST_EQ("-1.5E+00", generate_and_system_compare<PRIMA_FMT("%+.1E")>(-1.5f));
    BOOST_TEST_EQ("5.0E-02", generate_and_system_compare<PRIMA_FMT("%.1E")>(0.05f));
    BOOST_TEST_EQ("-5.0E-02", generate_and_system_compare<PRIMA_FMT("%.1E")>(-0.05f));
    BOOST_TEST_EQ("1.000050E+05", generate_and_system_compare<PRIMA_FMT("%E")>(100005.0f));
    BOOST_TEST_EQ("-1.000050E+05", generate_and_system_compare<PRIMA_FMT("%E")>(-100005.0f));
    BOOST_TEST_EQ("NAN", generate<PRIMA_FMT("%E")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("INF", generate<PRIMA_FMT("%E")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("+NAN", generate<PRIMA_FMT("%+E")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("+INF", generate<PRIMA_FMT("%+E")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ(" NAN", generate<PRIMA_FMT("% E")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ(" INF", generate<PRIMA_FMT("% E")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("-NAN", generate<PRIMA_FMT("%E")>(-std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("-INF", generate<PRIMA_FMT("%E")>(-std::numeric_limits<float>::infinity()));

    // optimal format
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%g")>(0.0f));
    BOOST_TEST_EQ("1", generate_and_system_compare<PRIMA_FMT("%g")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("%g")>(-1.0f));
    BOOST_TEST_EQ("1.5", generate_and_system_compare<PRIMA_FMT("%g")>(1.5f));
    BOOST_TEST_EQ("-1.5", generate_and_system_compare<PRIMA_FMT("%g")>(-1.5f));
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%.3g")>(0.0f));
    BOOST_TEST_EQ("1", generate_and_system_compare<PRIMA_FMT("%.3g")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("%.3g")>(-1.0f));
    BOOST_TEST_EQ("1.5", generate_and_system_compare<PRIMA_FMT("%.3g")>(1.5f));
    BOOST_TEST_EQ("-1.5", generate_and_system_compare<PRIMA_FMT("%.3g")>(-1.5f));
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%.0g")>(0.0f));
    BOOST_TEST_EQ("1", generate_and_system_compare<PRIMA_FMT("%.0g")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("%.0g")>(-1.0f));
    BOOST_TEST_EQ("2", generate_and_system_compare<PRIMA_FMT("%.0g")>(1.5f));
    BOOST_TEST_EQ("-2", generate_and_system_compare<PRIMA_FMT("%.0g")>(-1.5f));
    BOOST_TEST_EQ("0.", generate_and_system_compare<PRIMA_FMT("%#.0g")>(0.0f));
    BOOST_TEST_EQ("1.", generate_and_system_compare<PRIMA_FMT("%#.0g")>(1.0f));
    BOOST_TEST_EQ("-1.", generate_and_system_compare<PRIMA_FMT("%#.0g")>(-1.0f));
    BOOST_TEST_EQ("2.", generate_and_system_compare<PRIMA_FMT("%#.0g")>(1.5f));
    BOOST_TEST_EQ("-2.", generate_and_system_compare<PRIMA_FMT("%#.0g")>(-1.5f));
    BOOST_TEST_EQ("0.000000", generate_and_system_compare<PRIMA_FMT("%#.7g")>(0.0f));
    BOOST_TEST_EQ("1.000000", generate_and_system_compare<PRIMA_FMT("%#.7g")>(1.0f));
    BOOST_TEST_EQ("-1.000000", generate_and_system_compare<PRIMA_FMT("%#.7g")>(-1.0f));
    BOOST_TEST_EQ("1.500000", generate_and_system_compare<PRIMA_FMT("%#.7g")>(1.5f));
    BOOST_TEST_EQ("-1.500000", generate_and_system_compare<PRIMA_FMT("%#.7g")>(-1.5f));
    BOOST_TEST_EQ(" 0", generate_and_system_compare<PRIMA_FMT("% .1g")>(0.0f));
    BOOST_TEST_EQ(" 1", generate_and_system_compare<PRIMA_FMT("% .1g")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("% .1g")>(-1.0f));
    BOOST_TEST_EQ(" 2", generate_and_system_compare<PRIMA_FMT("% .1g")>(1.5f));
    BOOST_TEST_EQ("-2", generate_and_system_compare<PRIMA_FMT("% .1g")>(-1.5f));
    BOOST_TEST_EQ("+0", generate_and_system_compare<PRIMA_FMT("%+.1g")>(0.0f));
    BOOST_TEST_EQ("+1", generate_and_system_compare<PRIMA_FMT("%+.1g")>(1.0f));
    BOOST_TEST_EQ("-1", generate_and_system_compare<PRIMA_FMT("%+.1g")>(-1.0f));
    BOOST_TEST_EQ("+2", generate_and_system_compare<PRIMA_FMT("%+.1g")>(1.5f));
    BOOST_TEST_EQ("-2", generate_and_system_compare<PRIMA_FMT("%+.1g")>(-1.5f));
    BOOST_TEST_EQ("0.05", generate_and_system_compare<PRIMA_FMT("%.1g")>(0.05f));
    BOOST_TEST_EQ("-0.05", generate_and_system_compare<PRIMA_FMT("%.1g")>(-0.05f));
    BOOST_TEST_EQ("0.0005", generate_and_system_compare<PRIMA_FMT("%.1g")>(0.0005f));
    BOOST_TEST_EQ("-0.0005", generate_and_system_compare<PRIMA_FMT("%.6g")>(-0.0005f));
    BOOST_TEST_EQ(" 0.0005", generate_and_system_compare<PRIMA_FMT("% .6g")>(0.0005f));
    BOOST_TEST_EQ("+0.0005", generate_and_system_compare<PRIMA_FMT("%+.6g")>(0.0005f));
    BOOST_TEST_EQ("5e-05", generate_and_system_compare<PRIMA_FMT("%.6g")>(0.00005f));
    BOOST_TEST_EQ("-5e-05", generate_and_system_compare<PRIMA_FMT("%.6g")>(-0.00005f));
    BOOST_TEST_EQ(" 5e-05", generate_and_system_compare<PRIMA_FMT("% .6g")>(0.00005f));
    BOOST_TEST_EQ("+5e-05", generate_and_system_compare<PRIMA_FMT("%+.6g")>(0.00005f));
    BOOST_TEST_EQ("100005", generate_and_system_compare<PRIMA_FMT("%g")>(100005.0f));
    BOOST_TEST_EQ("-100005", generate_and_system_compare<PRIMA_FMT("%g")>(-100005.0f));
    BOOST_TEST_EQ("1.00001e+06", generate<PRIMA_FMT("%g")>(1000005.0f));
    BOOST_TEST_EQ("-1.00001e+06", generate<PRIMA_FMT("%g")>(-1000005.0f));
    BOOST_TEST_EQ("1.0001e+05", generate<PRIMA_FMT("%.5g")>(100005.0f));
    BOOST_TEST_EQ("-1.0001e+05", generate<PRIMA_FMT("%.5g")>(-100005.0f));
    BOOST_TEST_EQ("1e+05", generate_and_system_compare<PRIMA_FMT("%.5g")>(100004.0f));
    BOOST_TEST_EQ("-1e+05", generate_and_system_compare<PRIMA_FMT("%.5g")>(-100004.0f));
    BOOST_TEST_EQ("nan", generate<PRIMA_FMT("%g")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("inf", generate<PRIMA_FMT("%g")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("+nan", generate<PRIMA_FMT("%+g")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("+inf", generate<PRIMA_FMT("%+g")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ(" nan", generate<PRIMA_FMT("% g")>(std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ(" inf", generate<PRIMA_FMT("% g")>(std::numeric_limits<float>::infinity()));
    BOOST_TEST_EQ("-nan", generate<PRIMA_FMT("%g")>(-std::numeric_limits<float>::quiet_NaN()));
    BOOST_TEST_EQ("-inf", generate<PRIMA_FMT("%g")>(-std::numeric_limits<float>::infinity()));
}

void int_tests()
{
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%i")>(0));
    BOOST_TEST_EQ("100", generate_and_system_compare<PRIMA_FMT("%i")>(100));
    BOOST_TEST_EQ("-9223372036854775808", generate<PRIMA_FMT("%+i")>(std::numeric_limits<std::int64_t>::min()));
    BOOST_TEST_EQ("+9223372036854775807", generate<PRIMA_FMT("%+i")>(std::numeric_limits<std::int64_t>::max()));
    BOOST_TEST_EQ("  1024", generate_and_system_compare<PRIMA_FMT("%6i")>(1024));
    BOOST_TEST_EQ("1024  ", generate_and_system_compare<PRIMA_FMT("%-6i")>(1024));
    BOOST_TEST_EQ(" -1024", generate_and_system_compare<PRIMA_FMT("%6i")>(-1024));
    BOOST_TEST_EQ("-1024 ", generate_and_system_compare<PRIMA_FMT("%-6i")>(-1024));
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
    BOOST_TEST_EQ("0100 ", generate_and_system_compare<PRIMA_FMT("%-5.4u")>(100u));
    BOOST_TEST_EQ("00100", generate_and_system_compare<PRIMA_FMT("%05u")>(100u));
    BOOST_TEST_EQ("100`", generate_and_system_compare<PRIMA_FMT("%.0u`")>(100));
    BOOST_TEST_EQ("18446744073709551615`", generate<PRIMA_FMT("%.0u`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("`", generate_and_system_compare<PRIMA_FMT("%.0u`")>(0u));

    // octal
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%o")>(0u));
    BOOST_TEST_EQ("144", generate_and_system_compare<PRIMA_FMT("%o")>(100u));
    BOOST_TEST_EQ("1777777777777777777777", generate<PRIMA_FMT("%o")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0144", generate_and_system_compare<PRIMA_FMT("%.4o")>(100u));
    BOOST_TEST_EQ(" 0144", generate_and_system_compare<PRIMA_FMT("%5.4o")>(100u));
    BOOST_TEST_EQ("0144 ", generate_and_system_compare<PRIMA_FMT("%-5.4o")>(100u));
    BOOST_TEST_EQ("00144", generate_and_system_compare<PRIMA_FMT("%05o")>(100u));
    BOOST_TEST_EQ("144`", generate_and_system_compare<PRIMA_FMT("%.0o`")>(100));
    BOOST_TEST_EQ("1777777777777777777777`", generate<PRIMA_FMT("%.0o`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("`", generate_and_system_compare<PRIMA_FMT("%.0o`")>(0u));
    BOOST_TEST_EQ("0144`", generate_and_system_compare<PRIMA_FMT("%#o`")>(100));
    BOOST_TEST_EQ("01777777777777777777777`", generate<PRIMA_FMT("%#o`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0`", generate_and_system_compare<PRIMA_FMT("%#o`")>(0u));
    BOOST_TEST_EQ("0144`", generate_and_system_compare<PRIMA_FMT("%#.0o`")>(100));
    BOOST_TEST_EQ("01777777777777777777777`", generate<PRIMA_FMT("%#.0o`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0`", generate_and_system_compare<PRIMA_FMT("%#.0o`")>(0u));
    BOOST_TEST_EQ(" 0144`", generate_and_system_compare<PRIMA_FMT("%#5.4o`")>(100u));
    BOOST_TEST_EQ("00144`", generate_and_system_compare<PRIMA_FMT("%#.5o`")>(100u));

    // lower case hex
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%x")>(0u));
    BOOST_TEST_EQ("64", generate_and_system_compare<PRIMA_FMT("%x")>(100u));
    BOOST_TEST_EQ("ffffffffffffffff", generate<PRIMA_FMT("%x")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0064", generate_and_system_compare<PRIMA_FMT("%.4x")>(100u));
    BOOST_TEST_EQ(" 0064", generate_and_system_compare<PRIMA_FMT("%5.4x")>(100u));
    BOOST_TEST_EQ("0064 ", generate_and_system_compare<PRIMA_FMT("%-5.4x")>(100u));
    BOOST_TEST_EQ("00064", generate_and_system_compare<PRIMA_FMT("%05x")>(100u));
    BOOST_TEST_EQ("64`", generate_and_system_compare<PRIMA_FMT("%.0x`")>(100));
    BOOST_TEST_EQ("ffffffffffffffff`", generate<PRIMA_FMT("%.0x`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("`", generate_and_system_compare<PRIMA_FMT("%.0x`")>(0u));
    BOOST_TEST_EQ("0x64`", generate_and_system_compare<PRIMA_FMT("%#x`")>(100));
    BOOST_TEST_EQ("0xffffffffffffffff`", generate<PRIMA_FMT("%#x`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0`", generate_and_system_compare<PRIMA_FMT("%#x`")>(0u));
    BOOST_TEST_EQ("0x64`", generate_and_system_compare<PRIMA_FMT("%#.0x`")>(100));
    BOOST_TEST_EQ("0xffffffffffffffff`", generate<PRIMA_FMT("%#.0x`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("`", generate_and_system_compare<PRIMA_FMT("%#.0x`")>(0u));
    BOOST_TEST_EQ("0x0064`", generate_and_system_compare<PRIMA_FMT("%#6.4x`")>(100u));
    BOOST_TEST_EQ("  0000`", generate_and_system_compare<PRIMA_FMT("%#6.4x`")>(0u));

    // upper case hex
    BOOST_TEST_EQ("0", generate_and_system_compare<PRIMA_FMT("%X")>(0u));
    BOOST_TEST_EQ("64", generate_and_system_compare<PRIMA_FMT("%X")>(100u));
    BOOST_TEST_EQ("FFFFFFFFFFFFFFFF", generate<PRIMA_FMT("%X")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0064", generate_and_system_compare<PRIMA_FMT("%.4X")>(100u));
    BOOST_TEST_EQ(" 0064", generate_and_system_compare<PRIMA_FMT("%5.4X")>(100u));
#ifdef PRIMA_NO_LEFT_ALIGN_BUG
    BOOST_TEST_EQ("0064 ", generate_and_system_compare<PRIMA_FMT("%-5.4X")>(100u));
#endif
    BOOST_TEST_EQ("00064", generate_and_system_compare<PRIMA_FMT("%05X")>(100u));
    BOOST_TEST_EQ("64`", generate_and_system_compare<PRIMA_FMT("%.0X`")>(100));
    BOOST_TEST_EQ("FFFFFFFFFFFFFFFF`", generate<PRIMA_FMT("%.0X`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("`", generate_and_system_compare<PRIMA_FMT("%.0X`")>(0u));
    BOOST_TEST_EQ("0X64`", generate_and_system_compare<PRIMA_FMT("%#X`")>(100));
    BOOST_TEST_EQ("0XFFFFFFFFFFFFFFFF`", generate<PRIMA_FMT("%#X`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("0`", generate_and_system_compare<PRIMA_FMT("%#X`")>(0u));
    BOOST_TEST_EQ("0X64`", generate_and_system_compare<PRIMA_FMT("%#.0X`")>(100));
    BOOST_TEST_EQ("0XFFFFFFFFFFFFFFFF`", generate<PRIMA_FMT("%#.0X`")>(std::numeric_limits<std::uint64_t>::max()));
    BOOST_TEST_EQ("`", generate_and_system_compare<PRIMA_FMT("%#.0X`")>(0u));
    BOOST_TEST_EQ("0X0064`", generate_and_system_compare<PRIMA_FMT("%#6.4X`")>(100u));
    BOOST_TEST_EQ("  0000`", generate_and_system_compare<PRIMA_FMT("%#6.4X`")>(0u));
}

int main()
{
    BOOST_TEST_EQ("<-->", generate<PRIMA_FMT("<-->")>());
    BOOST_TEST_EQ("<-%->", generate<PRIMA_FMT("<-%%->")>());
    float_tests();
    int_tests();
    string_tests();
    unsigned_tests();
    return boost::report_errors();
}
