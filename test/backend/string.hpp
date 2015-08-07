#ifndef PRIMA_TEST_BACKEND_STRING_HPP
#define PRIMA_TEST_BACKEND_STRING_HPP

#include <limits>
#include <string>
#include <boost/detail/lightweight_test.hpp>

#include "test/generate.hpp"
#include "prima/backend/karma.hpp"
#include "prima/meta/base.hpp"

namespace prima
{
namespace backend
{
    namespace test
    {
        template <typename Backend> void string_tests()
        {
            BOOST_TEST_EQ(
                "|report string|",
                (prima::test::generate_and_system_compare<PRIMA_FMT("|%s|"),
                                                          Backend>(
                    "report string")));
            BOOST_TEST_EQ("|report string|",
                          (prima::test::generate<PRIMA_FMT("|%s|"), Backend>(
                              std::string{"report string"})));
            BOOST_TEST_EQ(
                "|repor|",
                (prima::test::generate_and_system_compare<PRIMA_FMT("|%.5s|"),
                                                          Backend>(
                    "report string")));
            BOOST_TEST_EQ(
                "| repor|",
                (prima::test::generate_and_system_compare<PRIMA_FMT("|%6.5s|"),
                                                          Backend>(
                    "report string")));
            BOOST_TEST_EQ("|repo   |",
                          (prima::test::generate_and_system_compare<
                              PRIMA_FMT("|%-6.4s |"),
                              Backend>("report string")));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_STRING_HPP
