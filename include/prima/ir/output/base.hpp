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
        template <typename Inner> struct upper_case
        {
            using type = upper_case;
            using inner = Inner;
        };

        template <typename Fields, typename Inner> struct width
        {
            using type = width;
            using fields = Fields;
            using inner = Inner;
        };

        template <typename Fields, typename Inner, typename Field>
        constexpr bool
        has_field(const width<Fields, Inner> &, const Field &) noexcept
        {
            namespace fields_ = ::prima::ir::output::fields;
            return is_field<Field, fields_::format_field>::value;
        }

        template <typename Fields> struct string
        {
            using type = string;
            using fields = Fields;
        };

        template <typename Fields, typename Field>
        constexpr bool has_field(const string<Fields> &, const Field &) noexcept
        {
            namespace fields_ = ::prima::ir::output::fields;
            return is_field<Field, fields_::type_field>::value;
        }

        template <typename Fields> struct int_
        {
            using type = int_;
            using fields = Fields;
        };

        template <typename Fields, typename Field>
        constexpr bool has_field(const int_<Fields> &, const Field &) noexcept
        {
            namespace fields_ = ::prima::ir::output::fields;
            return is_any_field<Field,
                                fields_::type_field,
                                fields_::numeric_field,
                                fields_::signed_numeric_field>::value;
        }

        template <typename Fields> struct unsigned_
        {
            using type = unsigned_;
            using fields = Fields;
        };

        template <typename Fields, typename Field>
        constexpr bool
        has_field(const unsigned_<Fields> &, const Field &) noexcept
        {
            namespace fields_ = ::prima::ir::output::fields;
            return is_any_field<Field,
                                fields_::type_field,
                                fields_::numeric_field>::value;
        }

        template <typename Fields> struct float_
        {
            using type = float_;
            using fields = Fields;
        };

        template <typename Fields, typename Field>
        constexpr bool has_field(const float_<Fields> &, const Field &) noexcept
        {
            namespace fields_ = ::prima::ir::output::fields;
            return is_any_field<Field,
                                fields_::type_field,
                                fields_::numeric_field,
                                fields_::signed_numeric_field,
                                fields_::real_field>::value;
        }
    } // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_TYPES_HPP
