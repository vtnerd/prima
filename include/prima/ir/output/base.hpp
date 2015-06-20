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
        template <typename Inner> struct lower_case
        {
            using type = lower_case;
            using inner = Inner;
        };

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

        template <typename Field, typename Fields, typename Inner>
        constexpr bool has_field(const width<Fields, Inner> &)
        {
            return is_field<Field, fields::format_field>::value;
        }

        template <typename Fields> struct string
        {
            using type = string;
            using fields = Fields;
        };

        template <typename Field, typename Fields>
        constexpr bool has_field(const string<Fields> &)
        {
            return is_field<Field, fields::type_field>::value;
        }

        template <typename Fields> struct int_
        {
            using type = int_;
            using fields = Fields;
        };

        template <typename Field, typename Fields>
        constexpr bool has_field(const int_<Fields> &)
        {
            return is_any_field<Field,
                                fields::type_field,
                                fields::numeric_field,
                                fields::signed_numeric_field>::value;
        }

        template <typename Fields> struct unsigned_
        {
            using type = unsigned_;
            using fields = Fields;
        };

        template <typename Field, typename Fields>
        constexpr bool has_field(const unsigned_<Fields> &)
        {
            return is_any_field<Field,
                                fields::type_field,
                                fields::numeric_field>::value;
        }

        template <typename Fields> struct float_
        {
            using type = float_;
            using fields = Fields;
        };

        template <typename Field, typename Fields>
        constexpr bool has_field(const float_<Fields> &)
        {
            return is_any_field<Field,
                                fields::type_field,
                                fields::numeric_field,
                                fields::signed_numeric_field,
                                fields::real_field>::value;
        }
    } // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_TYPES_HPP
