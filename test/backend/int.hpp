#ifndef PRIMA_TEST_BACKEND_INT_HPP
#define PRIMA_TEST_BACKEND_INT_HPP

#include <limits>
#include <boost/detail/lightweight_test.hpp>

#include "../generate.hpp"
#include "prima/backend/karma.hpp"
#include "prima/meta/base.hpp"

namespace prima
{
namespace backend
{
    namespace test
    {
        template <typename Backend> void int_tests()
        {
            BOOST_TEST_EQ(
                "0",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%i"),
                                                          Backend>(0)));
            BOOST_TEST_EQ(
                "100",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%i"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("-9223372036854775808",
                          (prima::test::generate<PRIMA_FMT("%+i"), Backend>(
                              std::numeric_limits<std::int64_t>::min())));
            BOOST_TEST_EQ(
                "+0",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%+i"),
                                                          Backend>(0)));
            BOOST_TEST_EQ("+9223372036854775807",
                          (prima::test::generate<PRIMA_FMT("%+i"), Backend>(
                              std::numeric_limits<std::int64_t>::max())));
            BOOST_TEST_EQ(
                "  1024",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%6i"),
                                                          Backend>(1024)));
            BOOST_TEST_EQ(
                "1024  ",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%-6i"),
                                                          Backend>(1024)));
            BOOST_TEST_EQ(
                " -1024",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%6i"),
                                                          Backend>(-1024)));
            BOOST_TEST_EQ(
                "-1024 ",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%-6i"),
                                                          Backend>(-1024)));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_INT_HPP
