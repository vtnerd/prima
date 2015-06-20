#ifndef PRIMA_IR_OUTPUT_FIELDS_HPP
#define PRIMA_IR_OUTPUT_FIELDS_HPP

#include "prima/meta/base.hpp"

namespace prima
{
namespace ir
{
    namespace output
    {
        namespace fields
        {
            template <unsigned Value>
            struct format_field : meta::unsigned_<Value>
            {
            };

            using left_justified = format_field<0>;
            using pad_character = format_field<1>;
            using width = format_field<2>;


            template <unsigned Value> struct type_field : meta::unsigned_<Value>
            {
            };

            using precision = type_field<0>;


            template <unsigned Value>
            struct numeric_field : meta::unsigned_<Value>
            {
            };

            using radix = numeric_field<1>;
            using use_alternate_format = numeric_field<2>;


            template <unsigned Value>
            struct signed_numeric_field : meta::unsigned_<Value>
            {
            };

            using always_print_sign = signed_numeric_field<3>;
            using extra_blank_on_positive = signed_numeric_field<4>;


            template <unsigned Value> struct real_field : meta::unsigned_<Value>
            {
            };

            using representation = real_field<5>;
        } // fields

        namespace values
        {
            //
            // format_field
            //
            using left_justified = meta::true_;
            using right_justified = meta::false_;

            template <char Value> struct pad_character : meta::char_<Value>
            {
            };

            template <char Value> struct width : meta::unsigned_<Value>
            {
            };

            //
            // type_field
            //
            template <unsigned Value> struct precision : meta::unsigned_<Value>
            {
            };

            //
            // numeric_field
            //
            template <unsigned Value> using radix = meta::unsigned_<Value>;

            using use_alternate_format = meta::true_;
            using use_standard_format = meta::false_;

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
            template <char Value> struct fixed : meta::char_<Value>
            {
            };

            template <char Value> struct scientific : meta::char_<Value>
            {
            };

            template <char Fixed, char Scientific> struct optimal
            {
                using type = optimal;
                const static char fixed = Fixed;
                const static char scientific = Scientific;
            };
        } // values
    }     // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_FIELDS_HPP
