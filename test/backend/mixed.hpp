#ifndef PRIMA_TEST_BACKEND_MIXED_HPP
#define PRIMA_TEST_BACKEND_MIXED_HPP

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
        template <typename Backend> void mixed_tests()
        {
            BOOST_TEST_EQ(
                "<-->", (prima::test::generate<PRIMA_FMT("<-->"), Backend>()));
            BOOST_TEST_EQ(
                "<-%->",
                (prima::test::generate<PRIMA_FMT("<-%%->"), Backend>()));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_MIXED_HPP
