#ifndef PRIMA_IR_OUTPUT_FIELDS_HPP
#define PRIMA_IR_OUTPUT_FIELDS_HPP

#include "prima/meta/base.hpp"

namespace prima
{
namespace ir
{
    namespace output
    {
        ////////////////////////////////////////////////////////////////////////
        // Fields                                                             //
        ////////////////////////////////////////////////////////////////////////
        namespace fields
        {
            //
            // format_field
            //
            template <unsigned Value>
            struct format_field : meta::unsigned_<Value>
            {
            };

            using left_justified = format_field<0>;
            using precision = format_field<1>;
            using upper_case = format_field<2>;
            using width = format_field<3>;

            //
            // numeric_field
            //
            template <unsigned Value>
            struct numeric_field : meta::unsigned_<Value>
            {
            };

            using pad_with_zero = numeric_field<4>;
            using radix = numeric_field<5>;
            using use_alternate_format = numeric_field<6>;

            //
            // signed_numeric_field
            //
            template <unsigned Value>
            struct signed_numeric_field : meta::unsigned_<Value>
            {
            };

            using always_print_sign = signed_numeric_field<7>;
            using extra_blank_on_positive = signed_numeric_field<8>;

            //
            // real_field
            //
            template <unsigned Value> struct real_field : meta::unsigned_<Value>
            {
            };

            using representation = real_field<9>;
        } // fields

        ////////////////////////////////////////////////////////////////////////
        // Values                                                             //
        ////////////////////////////////////////////////////////////////////////
        namespace values
        {
            //
            // format_field
            //
            using left_justified = meta::true_;
            using right_justified = meta::false_;

            template <unsigned Value> struct precision : meta::unsigned_<Value>
            {
            };

            using upper_case = meta::true_;
            using lower_case = meta::false_;

            template <unsigned Value> struct width : meta::unsigned_<Value>
            {
            };

            //
            // numeric_field
            //
            template <unsigned Value> using radix = meta::unsigned_<Value>;

            using use_alternate_format = meta::true_;
            using use_standard_format = meta::false_;

            using pad_with_zero = meta::true_;
            using pad_with_space = meta::false_;

            //
            // signed_numeric_field
            //
            using always_print_sign = meta::true_;
            using only_print_negative_sign = meta::false_;

            using extra_blank_on_positive = meta::true_;
            using no_extra_blank_on_positive = meta::false_;

            //
            // real_field
            //
            enum class real_format : std::uint8_t
            {
                fixed = 0,
                scientific,
                optimal
            };

            template <real_format format> struct representation
            {
                using type = representation;
                constexpr const static real_format value = format;
            };
        } // values
    }     // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_FIELDS_HPP
