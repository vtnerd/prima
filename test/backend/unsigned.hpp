#ifndef PRIMA_TEST_BACKEND_UNSIGNED_HPP
#define PRIMA_TEST_BACKEND_UNSIGNED_HPP

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
        template <typename Backend> void unsigned_tests()
        {
            // decimal
            BOOST_TEST_EQ(
                "0",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%u"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "100",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%u"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ("18446744073709551615",
                          (prima::test::generate<PRIMA_FMT("%u"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0100",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.4u"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                " 0100",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%5.4u"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "0100 ",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%-5.4u"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "00100",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%05u"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "100`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0u`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("18446744073709551615`",
                          (prima::test::generate<PRIMA_FMT("%.0u`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0u`"),
                                                          Backend>(0u)));

            // octal
            BOOST_TEST_EQ(
                "0",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%o"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "144",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%o"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ("1777777777777777777777",
                          (prima::test::generate<PRIMA_FMT("%o"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0144",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.4o"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                " 0144",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%5.4o"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "0144 ",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%-5.4o"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "00144",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%05o"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "144`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0o`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("1777777777777777777777`",
                          (prima::test::generate<PRIMA_FMT("%.0o`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0o`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0144`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#o`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("01777777777777777777777`",
                          (prima::test::generate<PRIMA_FMT("%#o`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#o`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0144`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.0o`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("01777777777777777777777`",
                          (prima::test::generate<PRIMA_FMT("%#.0o`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.0o`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                " 0144`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#5.4o`"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "00144`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.5o`"),
                                                          Backend>(100u)));

            // lower case hex
            BOOST_TEST_EQ(
                "0",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%x"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "64",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%x"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ("ffffffffffffffff",
                          (prima::test::generate<PRIMA_FMT("%x"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0064",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.4x"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                " 0064",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%5.4x"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "0064 ",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%-5.4x"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "00064",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%05x"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "64`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0x`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("ffffffffffffffff`",
                          (prima::test::generate<PRIMA_FMT("%.0x`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0x`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0x64`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#x`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("0xffffffffffffffff`",
                          (prima::test::generate<PRIMA_FMT("%#x`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#x`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0x64`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.0x`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("0xffffffffffffffff`",
                          (prima::test::generate<PRIMA_FMT("%#.0x`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.0x`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0x0064`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#6.4x`"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "  0000`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#6.4x`"),
                                                          Backend>(0u)));

            // upper case hex
            BOOST_TEST_EQ(
                "0",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%X"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "64",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%X"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ("FFFFFFFFFFFFFFFF",
                          (prima::test::generate<PRIMA_FMT("%X"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0064",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.4X"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                " 0064",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%5.4X"),
                                                          Backend>(100u)));
#ifndef PRIMA_TEST_LEFT_ALIGN_BUG
            BOOST_TEST_EQ(
                "0064 ",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%-5.4X"),
                                                          Backend>(100u)));
#endif
            BOOST_TEST_EQ(
                "00064",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%05X"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "64`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0X`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("FFFFFFFFFFFFFFFF`",
                          (prima::test::generate<PRIMA_FMT("%.0X`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%.0X`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0X64`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#X`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("0XFFFFFFFFFFFFFFFF`",
                          (prima::test::generate<PRIMA_FMT("%#X`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "0`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#X`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0X64`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.0X`"),
                                                          Backend>(100)));
            BOOST_TEST_EQ("0XFFFFFFFFFFFFFFFF`",
                          (prima::test::generate<PRIMA_FMT("%#.0X`"), Backend>(
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ(
                "`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#.0X`"),
                                                          Backend>(0u)));
            BOOST_TEST_EQ(
                "0X0064`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#6.4X`"),
                                                          Backend>(100u)));
            BOOST_TEST_EQ(
                "  0000`",
                (prima::test::generate_and_system_compare<PRIMA_FMT("%#6.4X`"),
                                                          Backend>(0u)));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_UNSIGNED_HPP
