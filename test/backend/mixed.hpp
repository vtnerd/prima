#ifndef PRIMA_TEST_BACKEND_MIXED_HPP
#define PRIMA_TEST_BACKEND_MIXED_HPP

#include <limits>
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
        template <typename Backend> void mixed_tests()
        {
            BOOST_TEST_EQ(
                "<-->", (prima::test::generate<PRIMA_FMT("<-->"), Backend>()));
            BOOST_TEST_EQ(
                "<-%->",
                (prima::test::generate<PRIMA_FMT("<-%%->"), Backend>()));
            BOOST_TEST_EQ(
                "Value:       6000\n",
                (prima::test::generate<PRIMA_FMT("Value: %10u\n"), Backend>(6000u)));
            BOOST_TEST_EQ(
                "Value:       6000\nValue:       7000\n",
                (prima::test::generate<PRIMA_FMT("Value: %10u\nValue: %10u\n"), Backend>(6000u, 7000u)));
            BOOST_TEST_EQ(
                "Value:     0X1770\nValue:     0x1b58\n",
                (prima::test::generate<PRIMA_FMT("Value: %#10X\nValue: %#10x\n"), Backend>(6000u, 7000u)));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_MIXED_HPP
