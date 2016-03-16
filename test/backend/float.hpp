#ifndef PRIMA_TEST_BACKEND_FLOAT_HPP
#define PRIMA_TEST_BACKEND_FLOAT_HPP

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
        template <typename Backend> void float_tests()
        {
            // fixed format
            BOOST_TEST_EQ("0.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%f"), 0.0f)));
            BOOST_TEST_EQ("1.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%f"), 1.0f)));
            BOOST_TEST_EQ("-1.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%f"), -1.0f)));
            BOOST_TEST_EQ("1.500000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%f"), 1.5f)));
            BOOST_TEST_EQ("-1.500000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%f"), -1.5f)));
            BOOST_TEST_EQ("0.000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3f"), 0.0f)));
            BOOST_TEST_EQ("1.000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3f"), 1.0f)));
            BOOST_TEST_EQ("-1.000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3f"), -1.0f)));
            BOOST_TEST_EQ("1.500",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3f"), 1.5f)));
            BOOST_TEST_EQ("-1.500",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3f"), -1.5f)));
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0f"), 0.0f)));
            BOOST_TEST_EQ("1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0f"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0f"), -1.0f)));
            BOOST_TEST_EQ("2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0f"), 1.5f)));
            BOOST_TEST_EQ("-2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0f"), -1.5f)));
            BOOST_TEST_EQ("0.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0f"), 0.0f)));
            BOOST_TEST_EQ("1.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0f"), 1.0f)));
            BOOST_TEST_EQ("-1.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0f"), -1.0f)));
            BOOST_TEST_EQ("2.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0f"), 1.5f)));
            BOOST_TEST_EQ("-2.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0f"), -1.5f)));
            BOOST_TEST_EQ("0.0000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7f"), 0.0f)));
            BOOST_TEST_EQ("1.0000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7f"), 1.0f)));
            BOOST_TEST_EQ("-1.0000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7f"), -1.0f)));
            BOOST_TEST_EQ("1.5000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7f"), 1.5f)));
            BOOST_TEST_EQ("-1.5000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7f"), -1.5f)));
            BOOST_TEST_EQ(" 0.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1f"), 0.0f)));
            BOOST_TEST_EQ(" 1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1f"), 1.0f)));
            BOOST_TEST_EQ("-1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1f"), -1.0f)));
            BOOST_TEST_EQ(" 1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1f"), 1.5f)));
            BOOST_TEST_EQ("-1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1f"), -1.5f)));
            BOOST_TEST_EQ("+0.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1f"), 0.0f)));
            BOOST_TEST_EQ("+1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1f"), 1.0f)));
            BOOST_TEST_EQ("-1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1f"), -1.0f)));
            BOOST_TEST_EQ("+1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1f"), 1.5f)));
            BOOST_TEST_EQ("-1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1f"), -1.5f)));
            BOOST_TEST_EQ("0.1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1f"), 0.05f)));
            BOOST_TEST_EQ("-0.1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1f"), -0.05f)));
            BOOST_TEST_EQ("nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%f"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%f"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("+nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+f"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("+inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+f"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ(" nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% f"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ(" inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% f"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("-nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%f"),
                              -std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("-inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%f"),
                              -std::numeric_limits<float>::infinity())));

            // fixed format (upper case)
            BOOST_TEST_EQ("0.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%F"), 0.0f)));
            BOOST_TEST_EQ("1.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%F"), 1.0f)));
            BOOST_TEST_EQ("-1.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%F"), -1.0f)));
            BOOST_TEST_EQ("1.500000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%F"), 1.5f)));
            BOOST_TEST_EQ("-1.500000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%F"), -1.5f)));
            BOOST_TEST_EQ("0.000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3F"), 0.0f)));
            BOOST_TEST_EQ("1.000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3F"), 1.0f)));
            BOOST_TEST_EQ("-1.000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3F"), -1.0f)));
            BOOST_TEST_EQ("1.500",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3F"), 1.5f)));
            BOOST_TEST_EQ("-1.500",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3F"), -1.5f)));
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0F"), 0.0f)));
            BOOST_TEST_EQ("1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0F"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0F"), -1.0f)));
            BOOST_TEST_EQ("2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0F"), 1.5f)));
            BOOST_TEST_EQ("-2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0F"), -1.5f)));
            BOOST_TEST_EQ("0.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0F"), 0.0f)));
            BOOST_TEST_EQ("1.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0F"), 1.0f)));
            BOOST_TEST_EQ("-1.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0F"), -1.0f)));
            BOOST_TEST_EQ("2.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0F"), 1.5f)));
            BOOST_TEST_EQ("-2.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0F"), -1.5f)));
            BOOST_TEST_EQ("0.0000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7F"), 0.0f)));
            BOOST_TEST_EQ("1.0000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7F"), 1.0f)));
            BOOST_TEST_EQ("-1.0000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7F"), -1.0f)));
            BOOST_TEST_EQ("1.5000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7F"), 1.5f)));
            BOOST_TEST_EQ("-1.5000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7F"), -1.5f)));
            BOOST_TEST_EQ(" 0.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1F"), 0.0f)));
            BOOST_TEST_EQ(" 1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1F"), 1.0f)));
            BOOST_TEST_EQ("-1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1F"), -1.0f)));
            BOOST_TEST_EQ(" 1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1F"), 1.5f)));
            BOOST_TEST_EQ("-1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1F"), -1.5f)));
            BOOST_TEST_EQ("+0.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1F"), 0.0f)));
            BOOST_TEST_EQ("+1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1F"), 1.0f)));
            BOOST_TEST_EQ("-1.0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1F"), -1.0f)));
            BOOST_TEST_EQ("+1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1F"), 1.5f)));
            BOOST_TEST_EQ("-1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1F"), -1.5f)));
            BOOST_TEST_EQ("0.1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1F"), 0.05f)));
            BOOST_TEST_EQ("-0.1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1F"), -0.05f)));
            BOOST_TEST_EQ("NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%F"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%F"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("+NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+F"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("+INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+F"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ(" NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% F"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ(" INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% F"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("-NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%F"),
                              -std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("-INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%F"),
                              -std::numeric_limits<float>::infinity())));

            // scientific format
            BOOST_TEST_EQ("0.000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), 0.0f)));
            BOOST_TEST_EQ("1.000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), 1.0f)));
            BOOST_TEST_EQ("-1.000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), -1.0f)));
            BOOST_TEST_EQ("1.500000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), 1.5f)));
            BOOST_TEST_EQ("-1.500000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), -1.5f)));
            BOOST_TEST_EQ("0.000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3e"), 0.0f)));
            BOOST_TEST_EQ("1.000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3e"), 1.0f)));
            BOOST_TEST_EQ("-1.000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3e"), -1.0f)));
            BOOST_TEST_EQ("1.500e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3e"), 1.5f)));
            BOOST_TEST_EQ("-1.500e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3e"), -1.5f)));
            BOOST_TEST_EQ("0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0e"), 0.0f)));
            BOOST_TEST_EQ("1e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0e"), 1.0f)));
            BOOST_TEST_EQ("-1e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0e"), -1.0f)));
            BOOST_TEST_EQ("2e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0e"), 1.5f)));
            BOOST_TEST_EQ("-2e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0e"), -1.5f)));
            BOOST_TEST_EQ("0.e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0e"), 0.0f)));
            BOOST_TEST_EQ("1.e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0e"), 1.0f)));
            BOOST_TEST_EQ("-1.e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0e"), -1.0f)));
            BOOST_TEST_EQ("2.e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0e"), 1.5f)));
            BOOST_TEST_EQ("-2.e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0e"), -1.5f)));
            BOOST_TEST_EQ("0.0000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7e"), 0.0f)));
            BOOST_TEST_EQ("1.0000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7e"), 1.0f)));
            BOOST_TEST_EQ("-1.0000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7e"), -1.0f)));
            BOOST_TEST_EQ("1.5000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7e"), 1.5f)));
            BOOST_TEST_EQ("-1.5000000e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7e"), -1.5f)));
            BOOST_TEST_EQ(" 0.0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1e"), 0.0f)));
            BOOST_TEST_EQ(" 1.0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1e"), 1.0f)));
            BOOST_TEST_EQ("-1.0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1e"), -1.0f)));
            BOOST_TEST_EQ(" 1.5e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1e"), 1.5f)));
            BOOST_TEST_EQ("-1.5e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1e"), -1.5f)));
            BOOST_TEST_EQ("+0.0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1e"), 0.0f)));
            BOOST_TEST_EQ("+1.0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1e"), 1.0f)));
            BOOST_TEST_EQ("-1.0e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1e"), -1.0f)));
            BOOST_TEST_EQ("+1.5e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1e"), 1.5f)));
            BOOST_TEST_EQ("-1.5e+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1e"), -1.5f)));
            BOOST_TEST_EQ("5.0e-02",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1e"), 0.05f)));
            BOOST_TEST_EQ("-5.0e-02",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1e"), -0.05f)));
            BOOST_TEST_EQ("1.000050e+05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), 100005.0f)));
            BOOST_TEST_EQ("-1.000050e+05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%e"), -100005.0f)));
            BOOST_TEST_EQ("nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%e"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%e"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("+nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+e"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("+inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+e"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ(" nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% e"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ(" inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% e"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("-nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%e"),
                              -std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("-inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%e"),
                              -std::numeric_limits<float>::infinity())));

            // scientific format (upper case)
            BOOST_TEST_EQ("0.000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), 0.0f)));
            BOOST_TEST_EQ("1.000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), 1.0f)));
            BOOST_TEST_EQ("-1.000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), -1.0f)));
            BOOST_TEST_EQ("1.500000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), 1.5f)));
            BOOST_TEST_EQ("-1.500000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), -1.5f)));
            BOOST_TEST_EQ("0.000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3E"), 0.0f)));
            BOOST_TEST_EQ("1.000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3E"), 1.0f)));
            BOOST_TEST_EQ("-1.000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3E"), -1.0f)));
            BOOST_TEST_EQ("1.500E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3E"), 1.5f)));
            BOOST_TEST_EQ("-1.500E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3E"), -1.5f)));
            BOOST_TEST_EQ("0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0E"), 0.0f)));
            BOOST_TEST_EQ("1E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0E"), 1.0f)));
            BOOST_TEST_EQ("-1E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0E"), -1.0f)));
            BOOST_TEST_EQ("2E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0E"), 1.5f)));
            BOOST_TEST_EQ("-2E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0E"), -1.5f)));
            BOOST_TEST_EQ("0.E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0E"), 0.0f)));
            BOOST_TEST_EQ("1.E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0E"), 1.0f)));
            BOOST_TEST_EQ("-1.E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0E"), -1.0f)));
            BOOST_TEST_EQ("2.E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0E"), 1.5f)));
            BOOST_TEST_EQ("-2.E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0E"), -1.5f)));
            BOOST_TEST_EQ("0.0000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7E"), 0.0f)));
            BOOST_TEST_EQ("1.0000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7E"), 1.0f)));
            BOOST_TEST_EQ("-1.0000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7E"), -1.0f)));
            BOOST_TEST_EQ("1.5000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7E"), 1.5f)));
            BOOST_TEST_EQ("-1.5000000E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7E"), -1.5f)));
            BOOST_TEST_EQ(" 0.0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1E"), 0.0f)));
            BOOST_TEST_EQ(" 1.0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1E"), 1.0f)));
            BOOST_TEST_EQ("-1.0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1E"), -1.0f)));
            BOOST_TEST_EQ(" 1.5E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1E"), 1.5f)));
            BOOST_TEST_EQ("-1.5E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1E"), -1.5f)));
            BOOST_TEST_EQ("+0.0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1E"), 0.0f)));
            BOOST_TEST_EQ("+1.0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1E"), 1.0f)));
            BOOST_TEST_EQ("-1.0E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1E"), -1.0f)));
            BOOST_TEST_EQ("+1.5E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1E"), 1.5f)));
            BOOST_TEST_EQ("-1.5E+00",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1E"), -1.5f)));
            BOOST_TEST_EQ("5.0E-02",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1E"), 0.05f)));
            BOOST_TEST_EQ("-5.0E-02",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1E"), -0.05f)));
            BOOST_TEST_EQ("1.000050E+05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), 100005.0f)));
            BOOST_TEST_EQ("-1.000050E+05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%E"), -100005.0f)));
            BOOST_TEST_EQ("NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%E"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%E"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("+NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+E"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("+INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+E"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ(" NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% E"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ(" INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% E"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("-NAN",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%E"),
                              -std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("-INF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%E"),
                              -std::numeric_limits<float>::infinity())));

            // optimal format
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), 0.0f)));
            BOOST_TEST_EQ("1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), -1.0f)));
            BOOST_TEST_EQ("1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), 1.5f)));
            BOOST_TEST_EQ("-1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), -1.5f)));
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3g"), 0.0f)));
            BOOST_TEST_EQ("1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3g"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3g"), -1.0f)));
            BOOST_TEST_EQ("1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3g"), 1.5f)));
            BOOST_TEST_EQ("-1.5",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.3g"), -1.5f)));
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0g"), 0.0f)));
            BOOST_TEST_EQ("1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0g"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0g"), -1.0f)));
            BOOST_TEST_EQ("2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0g"), 1.5f)));
            BOOST_TEST_EQ("-2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0g"), -1.5f)));
            BOOST_TEST_EQ("0.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0g"), 0.0f)));
            BOOST_TEST_EQ("1.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0g"), 1.0f)));
            BOOST_TEST_EQ("-1.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0g"), -1.0f)));
            BOOST_TEST_EQ("2.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0g"), 1.5f)));
            BOOST_TEST_EQ("-2.",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0g"), -1.5f)));
            BOOST_TEST_EQ("0.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7g"), 0.0f)));
            BOOST_TEST_EQ("1.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7g"), 1.0f)));
            BOOST_TEST_EQ("-1.000000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7g"), -1.0f)));
            BOOST_TEST_EQ("1.500000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7g"), 1.5f)));
            BOOST_TEST_EQ("-1.500000",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.7g"), -1.5f)));
            BOOST_TEST_EQ(" 0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1g"), 0.0f)));
            BOOST_TEST_EQ(" 1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1g"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1g"), -1.0f)));
            BOOST_TEST_EQ(" 2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1g"), 1.5f)));
            BOOST_TEST_EQ("-2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .1g"), -1.5f)));
            BOOST_TEST_EQ("+0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1g"), 0.0f)));
            BOOST_TEST_EQ("+1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1g"), 1.0f)));
            BOOST_TEST_EQ("-1",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1g"), -1.0f)));
            BOOST_TEST_EQ("+2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1g"), 1.5f)));
            BOOST_TEST_EQ("-2",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.1g"), -1.5f)));
            BOOST_TEST_EQ("0.05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1g"), 0.05f)));
            BOOST_TEST_EQ("-0.05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1g"), -0.05f)));
            BOOST_TEST_EQ("0.0005",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.1g"), 0.0005f)));
            BOOST_TEST_EQ("-0.0005",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.6g"), -0.0005f)));
            BOOST_TEST_EQ(" 0.0005",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .6g"), 0.0005f)));
            BOOST_TEST_EQ("+0.0005",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.6g"), 0.0005f)));
            BOOST_TEST_EQ("5e-05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.6g"), 0.00005f)));
            BOOST_TEST_EQ("-5e-05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.6g"), -0.00005f)));
            BOOST_TEST_EQ(" 5e-05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("% .6g"), 0.00005f)));
            BOOST_TEST_EQ("+5e-05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%+.6g"), 0.00005f)));
            BOOST_TEST_EQ("100005",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), 100005.0f)));
            BOOST_TEST_EQ("-100005",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%g"), -100005.0f)));
            BOOST_TEST_EQ("1.00001e+06",
                          (prima::test::generate<Backend>(PRIMA_FMT("%g"),
                                                          1000005.0f)));
            BOOST_TEST_EQ("-1.00001e+06",
                          (prima::test::generate<Backend>(PRIMA_FMT("%g"),
                                                          -1000005.0f)));
            BOOST_TEST_EQ("1.0001e+05",
                          (prima::test::generate<Backend>(PRIMA_FMT("%.5g"),
                                                          100005.0f)));
            BOOST_TEST_EQ("-1.0001e+05",
                          (prima::test::generate<Backend>(PRIMA_FMT("%.5g"),
                                                          -100005.0f)));
            BOOST_TEST_EQ("1e+05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.5g"), 100004.0f)));
            BOOST_TEST_EQ("-1e+05",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.5g"), -100004.0f)));
            BOOST_TEST_EQ("nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%g"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%g"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("+nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+g"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("+inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%+g"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ(" nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% g"),
                              std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ(" inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("% g"),
                              std::numeric_limits<float>::infinity())));
            BOOST_TEST_EQ("-nan",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%g"),
                              -std::numeric_limits<float>::quiet_NaN())));
            BOOST_TEST_EQ("-inf",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%g"),
                              -std::numeric_limits<float>::infinity())));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_FLOAT_HPP
