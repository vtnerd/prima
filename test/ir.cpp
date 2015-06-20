#include <limits>
#include <utility>

#include <boost/detail/lightweight_test.hpp>
#include <boost/mpl/set.hpp>

#include "prima/ir/base.hpp"
#include "prima/ir/output/base.hpp"
#include "prima/ir/output/fields.hpp"
#include "prima/ir/output/make.hpp"
#include "prima/meta/base.hpp"

using namespace prima;

void has_field_tests()
{
    namespace fields = ir::output::fields;
    namespace make = ir::output::make;
    using ir::has_field;
    {
        constexpr const auto float_ = make::float_<meta::void_>{};
        BOOST_TEST(!has_field<fields::left_justified>(float_));
        BOOST_TEST(!has_field<fields::pad_character>(float_));
        BOOST_TEST(!has_field<fields::width>(float_));
        BOOST_TEST(has_field<fields::precision>(float_));
        BOOST_TEST(has_field<fields::radix>(float_));
        BOOST_TEST(has_field<fields::use_alternate_format>(float_));
        BOOST_TEST(has_field<fields::always_print_sign>(float_));
        BOOST_TEST(has_field<fields::extra_blank_on_positive>(float_));
        BOOST_TEST(has_field<fields::representation>(float_));
    }
    {
        constexpr const auto int_ = make::int_<>{};
        BOOST_TEST(!has_field<fields::left_justified>(int_));
        BOOST_TEST(!has_field<fields::pad_character>(int_));
        BOOST_TEST(!has_field<fields::width>(int_));
        BOOST_TEST(has_field<fields::precision>(int_));
        BOOST_TEST(has_field<fields::radix>(int_));
        BOOST_TEST(has_field<fields::use_alternate_format>(int_));
        BOOST_TEST(has_field<fields::always_print_sign>(int_));
        BOOST_TEST(has_field<fields::extra_blank_on_positive>(int_));
        BOOST_TEST(!has_field<fields::representation>(int_));
    }
    {
        constexpr const auto string = make::string{};
        BOOST_TEST(!has_field<fields::left_justified>(string));
        BOOST_TEST(!has_field<fields::pad_character>(string));
        BOOST_TEST(!has_field<fields::width>(string));
        BOOST_TEST(has_field<fields::precision>(string));
        BOOST_TEST(!has_field<fields::radix>(string));
        BOOST_TEST(!has_field<fields::use_alternate_format>(string));
        BOOST_TEST(!has_field<fields::always_print_sign>(string));
        BOOST_TEST(!has_field<fields::extra_blank_on_positive>(string));
        BOOST_TEST(!has_field<fields::representation>(string));
    }
    {
        constexpr const auto upper_case = make::upper_case<meta::void_>{};
        BOOST_TEST(!has_field<fields::left_justified>(upper_case));
        BOOST_TEST(!has_field<fields::pad_character>(upper_case));
        BOOST_TEST(!has_field<fields::width>(upper_case));
        BOOST_TEST(!has_field<fields::precision>(upper_case));
        BOOST_TEST(!has_field<fields::radix>(upper_case));
        BOOST_TEST(!has_field<fields::use_alternate_format>(upper_case));
        BOOST_TEST(!has_field<fields::always_print_sign>(upper_case));
        BOOST_TEST(!has_field<fields::extra_blank_on_positive>(upper_case));
        BOOST_TEST(!has_field<fields::representation>(upper_case));
    }
    {
        constexpr const auto unsigned_ = make::unsigned_<>{};
        BOOST_TEST(!has_field<fields::left_justified>(unsigned_));
        BOOST_TEST(!has_field<fields::pad_character>(unsigned_));
        BOOST_TEST(!has_field<fields::width>(unsigned_));
        BOOST_TEST(has_field<fields::precision>(unsigned_));
        BOOST_TEST(has_field<fields::radix>(unsigned_));
        BOOST_TEST(has_field<fields::use_alternate_format>(unsigned_));
        BOOST_TEST(!has_field<fields::always_print_sign>(unsigned_));
        BOOST_TEST(!has_field<fields::extra_blank_on_positive>(unsigned_));
        BOOST_TEST(!has_field<fields::representation>(unsigned_));
    }
    {
        constexpr const auto width =
            make::width<meta::unsigned_<2>, meta::void_>{};
        BOOST_TEST(has_field<fields::left_justified>(width));
        BOOST_TEST(has_field<fields::pad_character>(width));
        BOOST_TEST(has_field<fields::width>(width));
        BOOST_TEST(!has_field<fields::precision>(width));
        BOOST_TEST(!has_field<fields::radix>(width));
        BOOST_TEST(!has_field<fields::use_alternate_format>(width));
        BOOST_TEST(!has_field<fields::always_print_sign>(width));
        BOOST_TEST(!has_field<fields::extra_blank_on_positive>(width));
        BOOST_TEST(!has_field<fields::representation>(width));
    }
}

int main()
{
    has_field_tests();
    return boost::report_errors();
}
