#ifndef PRIMA_TEST_BACKEND_UNSIGNED_HPP
#define PRIMA_TEST_BACKEND_UNSIGNED_HPP

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
        template <typename Backend> void unsigned_tests()
        {
            // decimal
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%u"), 0u)));
            BOOST_TEST_EQ("100",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%u"), 100u)));
            BOOST_TEST_EQ("18446744073709551615",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%u"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0100",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.4u"), 100u)));
            BOOST_TEST_EQ(" 0100",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%5.4u"), 100u)));
            BOOST_TEST_EQ("0100 ",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%-5.4u"), 100u)));
            BOOST_TEST_EQ("00100",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%05u"), 100u)));
            BOOST_TEST_EQ("100`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0u`"), 100)));
            BOOST_TEST_EQ("18446744073709551615`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%.0u`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0u`"), 0u)));

            // octal
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%o"), 0u)));
            BOOST_TEST_EQ("144",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%o"), 100u)));
            BOOST_TEST_EQ("1777777777777777777777",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%o"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0144",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.4o"), 100u)));
            BOOST_TEST_EQ(" 0144",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%5.4o"), 100u)));
            BOOST_TEST_EQ("0144 ",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%-5.4o"), 100u)));
            BOOST_TEST_EQ("00144",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%05o"), 100u)));
            BOOST_TEST_EQ("144`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0o`"), 100)));
            BOOST_TEST_EQ("1777777777777777777777`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%.0o`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0o`"), 0u)));
            BOOST_TEST_EQ("0144`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#o`"), 100)));
            BOOST_TEST_EQ("01777777777777777777777`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%#o`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#o`"), 0u)));
            BOOST_TEST_EQ("0144`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0o`"), 100)));
            BOOST_TEST_EQ("01777777777777777777777`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%#.0o`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0o`"), 0u)));
            BOOST_TEST_EQ(" 0144`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#5.4o`"), 100u)));
            BOOST_TEST_EQ("00144`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.5o`"), 100u)));

            // lower case hex
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%x"), 0u)));
            BOOST_TEST_EQ("64",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%x"), 100u)));
            BOOST_TEST_EQ("ffffffffffffffff",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%x"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0064",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.4x"), 100u)));
            BOOST_TEST_EQ(" 0064",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%5.4x"), 100u)));
            BOOST_TEST_EQ("0064 ",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%-5.4x"), 100u)));
            BOOST_TEST_EQ("00064",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%05x"), 100u)));
            BOOST_TEST_EQ("64`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0x`"), 100)));
            BOOST_TEST_EQ("ffffffffffffffff`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%.0x`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0x`"), 0u)));
            BOOST_TEST_EQ("0x64`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#x`"), 100)));
            BOOST_TEST_EQ("0xffffffffffffffff`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%#x`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#x`"), 0u)));
            BOOST_TEST_EQ("0x64`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0x`"), 100)));
            BOOST_TEST_EQ("0xffffffffffffffff`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%#.0x`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0x`"), 0u)));
            BOOST_TEST_EQ("0x0064`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#6.4x`"), 100u)));
            BOOST_TEST_EQ("0x0064`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#06x`"), 100u)));
            BOOST_TEST_EQ("  0000`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#6.4x`"), 0u)));
            // upper case hex
            BOOST_TEST_EQ("0",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%X"), 0u)));
            BOOST_TEST_EQ("64",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%X"), 100u)));
            BOOST_TEST_EQ("FFFFFFFFFFFFFFFF",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%X"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0064",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.4X"), 100u)));
            BOOST_TEST_EQ(" 0064",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%5.4X"), 100u)));
            BOOST_TEST_EQ("0064 ",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%-5.4X"), 100u)));
            BOOST_TEST_EQ("00064",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%05X"), 100u)));
            BOOST_TEST_EQ("64`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0X`"), 100)));
            BOOST_TEST_EQ("FFFFFFFFFFFFFFFF`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%.0X`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%.0X`"), 0u)));
            BOOST_TEST_EQ("0X64`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#X`"), 100)));
            BOOST_TEST_EQ("0XFFFFFFFFFFFFFFFF`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%#X`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("0`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#X`"), 0u)));
            BOOST_TEST_EQ("0X64`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0X`"), 100)));
            BOOST_TEST_EQ("0XFFFFFFFFFFFFFFFF`",
                          (prima::test::generate<Backend>(
                              PRIMA_FMT("%#.0X`"),
                              std::numeric_limits<std::uint64_t>::max())));
            BOOST_TEST_EQ("`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#.0X`"), 0u)));

            BOOST_TEST_EQ("0X0064`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#6.4X`"), 100u)));
            BOOST_TEST_EQ("  0000`",
                          (prima::test::generate_and_system_compare<Backend>(
                              PRIMA_FMT("%#6.4X`"), 0u)));
        }
    } // test
} // backend
} // prima

#endif // PRIMA_TEST_BACKEND_UNSIGNED_HPP
