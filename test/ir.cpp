#include <limits>
#include <utility>

#include <boost/detail/lightweight_test.hpp>
#include <boost/mpl/set.hpp>

#include "prima/ir/base.hpp"
#include "prima/ir/output/base.hpp"
#include "prima/ir/output/fields.hpp"
#include "prima/ir/output/make.hpp"

using namespace prima;

void has_field_tests()
{
    namespace fields = ir::output::fields;
    namespace make = ir::output::make;
    namespace values = ir::output::values;

    constexpr const auto left_justified = fields::left_justified{};
    constexpr const auto precision = fields::precision{};
    constexpr const auto upper_case = fields::upper_case{};
    constexpr const auto width = fields::width{};
    constexpr const auto pad_with_zero = fields::pad_with_zero{};
    constexpr const auto radix = fields::radix{};
    constexpr const auto use_alternate_format = fields::use_alternate_format{};
    constexpr const auto always_print_sign = fields::always_print_sign{};
    constexpr const auto extra_blank_on_positive =
        fields::extra_blank_on_positive{};
    constexpr const auto representation = fields::representation{};

    {
        constexpr const auto float_ =
            make::float_<values::real_format::fixed>{};
        BOOST_TEST(ir::has_field(float_, left_justified));
        BOOST_TEST(ir::has_field(float_, precision));
        BOOST_TEST(ir::has_field(float_, upper_case));
        BOOST_TEST(ir::has_field(float_, width));
        BOOST_TEST(ir::has_field(float_, pad_with_zero));
        BOOST_TEST(ir::has_field(float_, radix));
        BOOST_TEST(ir::has_field(float_, use_alternate_format));
        BOOST_TEST(ir::has_field(float_, always_print_sign));
        BOOST_TEST(ir::has_field(float_, extra_blank_on_positive));
        BOOST_TEST(ir::has_field(float_, representation));
    }
    {
        constexpr const auto int_ = make::int_<>{};
        BOOST_TEST(ir::has_field(int_, left_justified));
        BOOST_TEST(ir::has_field(int_, precision));
        BOOST_TEST(!ir::has_field(int_, upper_case));
        BOOST_TEST(ir::has_field(int_, width));
        BOOST_TEST(ir::has_field(int_, pad_with_zero));
        BOOST_TEST(ir::has_field(int_, radix));
        BOOST_TEST(ir::has_field(int_, use_alternate_format));
        BOOST_TEST(ir::has_field(int_, always_print_sign));
        BOOST_TEST(ir::has_field(int_, extra_blank_on_positive));
        BOOST_TEST(!ir::has_field(int_, representation));
    }
    {
        constexpr const auto string = make::string{};
        BOOST_TEST(ir::has_field(string, left_justified));
        BOOST_TEST(ir::has_field(string, precision));
        BOOST_TEST(!ir::has_field(string, upper_case));
        BOOST_TEST(ir::has_field(string, width));
        BOOST_TEST(!ir::has_field(string, pad_with_zero));
        BOOST_TEST(!ir::has_field(string, radix));
        BOOST_TEST(!ir::has_field(string, use_alternate_format));
        BOOST_TEST(!ir::has_field(string, always_print_sign));
        BOOST_TEST(!ir::has_field(string, extra_blank_on_positive));
        BOOST_TEST(!ir::has_field(string, representation));
    }
    {
        constexpr const auto unsigned_ = make::unsigned_<>{};
        BOOST_TEST(ir::has_field(unsigned_, left_justified));
        BOOST_TEST(ir::has_field(unsigned_, precision));
        BOOST_TEST(ir::has_field(unsigned_, upper_case));
        BOOST_TEST(ir::has_field(unsigned_, width));
        BOOST_TEST(ir::has_field(unsigned_, pad_with_zero));
        BOOST_TEST(ir::has_field(unsigned_, radix));
        BOOST_TEST(ir::has_field(unsigned_, use_alternate_format));
        BOOST_TEST(!ir::has_field(unsigned_, always_print_sign));
        BOOST_TEST(!ir::has_field(unsigned_, extra_blank_on_positive));
        BOOST_TEST(!ir::has_field(unsigned_, representation));
    }
}

int main()
{
    has_field_tests();
    return boost::report_errors();
}
