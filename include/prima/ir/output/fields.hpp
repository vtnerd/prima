#ifndef PRIMA_IR_OUTPUT_FIELDS_HPP
#define PRIMA_IR_OUTPUT_FIELDS_HPP

#include "prima/meta/base.hpp"

namespace prima
{
namespace ir
{
    namespace output
    {
        namespace format
        {
            template <unsigned Value>
            struct format_field : meta::unsigned_<Value>
            {
            };

            template <unsigned Value>
            constexpr bool is_field(const format_field<Value> &)
            {
                return true;
            }

            namespace fields
            {
                using left_justified = format_field<0>;
                using pad_character = format_field<1>;
                using width = format_field<2>;
            }

            namespace values
            {
                using left_justified = meta::true_;
                using right_justified = meta::false_;

                template <char Value> struct pad_character : meta::char_<Value>
                {
                };

                template <char Value> struct width : meta::unsigned_<Value>
                {
                };
            }
        } // format

        namespace types
        {
            template <unsigned Value> struct type_field : meta::unsigned_<Value>
            {
            };

            template <unsigned Value>
            constexpr bool is_field(const type_field<Value> &)
            {
                return true;
            }

            namespace fields
            {
                using precision = type_field<0>;
            }

            namespace values
            {
                template <unsigned Value>
                struct precision : meta::unsigned_<Value>
                {
                };
            }

            namespace numeric
            {
                template <unsigned Value>
                struct numeric_field : meta::unsigned_<Value>
                {
                };

                template <unsigned Value>
                constexpr bool is_field(const numeric_field<Value> &)
                {
                    return true;
                }

                namespace fields
                {
                    using radix = numeric_field<1>;
                    using always_print_sign = numeric_field<2>;
                    using extra_blank_on_positive = numeric_field<3>;
                    using use_alternate_format = numeric_field<4>;
                }

                namespace values
                {
                    template <unsigned Value>
                    using radix = meta::unsigned_<Value>;

                    using always_print_sign = meta::true_;
                    using only_print_negative_sign = meta::false_;

                    using extra_blank_on_positive = meta::true_;
                    using no_extra_blank_on_positive = meta::false_;

                    using use_alternate_format = meta::true_;
                    using use_standard_format = meta::false_;
                }

                namespace real
                {
                    template <unsigned Value>
                    struct real_field : meta::unsigned_<Value>
                    {
                    };

                    template <unsigned Value>
                    constexpr bool is_field(const real_field<Value> &)
                    {
                        return true;
                    }

                    namespace fields
                    {
                        using representation = real_field<5>;
                    }

                    namespace values
                    {
                        template <char Value> struct fixed : meta::char_<Value>
                        {
                        };

                        template <char Value>
                        struct scientific : meta::char_<Value>
                        {
                        };

                        template <char Fixed, char Scientific> struct optimal
                        {
                            using type = optimal;
                            const static char fixed = Fixed;
                            const static char scientific = Scientific;
                        };
                    }
                } // real
            }     // numeric
        }         // types
    }             // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_FIELDS_HPP
