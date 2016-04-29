#ifndef PRIMA_IR_OUTPUT_BASE_HPP
#define PRIMA_IR_OUTPUT_BASE_HPP

#include "prima/ir/base.hpp"
#include "prima/ir/output/fields.hpp"

namespace prima
{
namespace ir
{
    namespace output
    {
        //
        // float
        //
        template <typename Fields> struct float_
        {
            using type = float_;
            using fields = Fields;

            template <typename Test>
            friend constexpr bool has_field(float_ const&, Test const&) noexcept
            {
                namespace fields_ = ::prima::ir::output::fields;
                return is_any_field<Test,
                                    fields_::format_field,
                                    fields_::numeric_field,
                                    fields_::signed_numeric_field,
                                    fields_::real_field>::value;
            }
        };

        //
        // int
        //
        template <typename Fields> struct int_
        {
            using type = int_;
            using fields = Fields;

            template <typename Test>
            friend constexpr bool has_field(int_ const&, Test const&) noexcept
            {
                namespace fields_ = ::prima::ir::output::fields;
                return is_any_field<Test,
                                    fields_::format_field,
                                    fields_::numeric_field,
                                    fields_::signed_numeric_field>::value &&
                       Test::value != fields_::upper_case::value;
            }
        };

        //
        // string
        //
        template <typename Fields> struct string
        {
            using type = string;
            using fields = Fields;

            template <typename Test>
            friend constexpr bool has_field(string const&, Test const&) noexcept
            {
                namespace fields_ = ::prima::ir::output::fields;
                return is_field<Test, fields_::format_field>::value &&
                       Test::value != fields_::upper_case::value;
            }
        };

        //
        // unsigned
        //
        template <typename Fields> struct unsigned_
        {
            using type = unsigned_;
            using fields = Fields;

            template <typename Test>
            friend constexpr bool
            has_field(unsigned_ const&, Test const&) noexcept
            {
                namespace fields_ = ::prima::ir::output::fields;
                return is_any_field<Test,
                                    fields_::format_field,
                                    fields_::numeric_field>::value;
            }
        };
    } // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_TYPES_HPP
