#ifndef PRIMA_TEST_BACKEND_INT_HPP
#define PRIMA_TEST_BACKEND_INT_HPP

#include <limits>
#include <boost/detail/lightweight_test.hpp>

#include "test/generate.hpp"
#include "prima/backend/karma.hpp"
#include "prima/meta/base.hpp"

#include <boost/spirit/include/karma_format.hpp>

namespace prima
{
namespace backend
{
    namespace test
    {
        template <typename Backend> void int_tests()
        {
            {
                using test_format = PRIMA_FMT("%i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "0",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0)));
                BOOST_TEST_EQ(
                    "100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("%+i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ("+0",
                              (prima::test::generate<test_format, Backend>(0)));
                BOOST_TEST_EQ(
                    "+100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("+9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("% i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    " 0",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0)));
                BOOST_TEST_EQ(
                    " 100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ(" 9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("%6i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    " -1024",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-1024)));
                BOOST_TEST_EQ(
                    "  1024",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(1024)));
                BOOST_TEST_EQ("9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("%-6i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-1024 ",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-1024)));
                BOOST_TEST_EQ(
                    "1024  ",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(1024)));
                BOOST_TEST_EQ("9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
#ifndef PRIMA_TEST_DUPLICATE_ATTRIBUTE_BUG
                using test_format = PRIMA_FMT("%06i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-01024",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-1024)));
                BOOST_TEST_EQ(
                    "000000",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0)));
                BOOST_TEST_EQ(
                    "001024",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(1024)));
                BOOST_TEST_EQ("9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
#endif
            }
            {
                using test_format = PRIMA_FMT("%.0i`");
                BOOST_TEST_EQ("-9223372036854775808`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    "100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("9223372036854775807`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("%.2i`");
                BOOST_TEST_EQ("-9223372036854775808`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "00`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    "100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("9223372036854775807`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("%.5i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "00000",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    "00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
                using test_format = PRIMA_FMT("%+.0i`");
                BOOST_TEST_EQ("-9223372036854775808`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "+`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    "+100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("+9223372036854775807`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
#ifndef PRIMA_TEST_DUPLICATE_ATTRIBUTE_BUG
                using test_format = PRIMA_FMT("%+.5i`");
                BOOST_TEST_EQ("-9223372036854775808`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-00100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "+00000`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    "+00100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("+9223372036854775807`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
#endif
            }
            {
#ifndef PRIMA_TEST_DUPLICATE_ATTRIBUTE_BUG
                using test_format = PRIMA_FMT("%+5i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    " -100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "   +0",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    " +100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("+9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
#endif
            }
            {
                using test_format = PRIMA_FMT("% .0i`");
                BOOST_TEST_EQ("-9223372036854775808`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    " `",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    " 100`",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ(" 9223372036854775807`",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
            }
            {
#ifndef PRIMA_TEST_DUPLICATE_ATTRIBUTE_BUG
                using test_format = PRIMA_FMT("% .5i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    " 00000",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    " 00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ(" 9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
#endif
            }
            {
#ifndef PRIMA_TEST_DUPLICATE_ATTRIBUTE_BUG
                using test_format = PRIMA_FMT("%0 6i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    " 00000",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    " 00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ(" 9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
#endif
            }
            {
#ifndef PRIMA_TEST_DUPLICATE_ATTRIBUTE_BUG
                using test_format = PRIMA_FMT("%+06i");
                BOOST_TEST_EQ("-9223372036854775808",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::min())));
                BOOST_TEST_EQ(
                    "-00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(-100)));
                BOOST_TEST_EQ(
                    "+00000",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(0u)));
                BOOST_TEST_EQ(
                    "+00100",
                    (prima::test::generate_and_system_compare<test_format,
                                                              Backend>(100)));
                BOOST_TEST_EQ("+9223372036854775807",
                              (prima::test::generate<test_format, Backend>(
                                  std::numeric_limits<std::int64_t>::max())));
#endif
            }
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_INT_HPP
