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
        namespace format
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
                using ir::is_field;
                using ir::output::format::is_field;
                // disable ADL
                return (is_field)(Field{});
            }
        } // format

        namespace types
        {
            template <typename Fields> struct string
            {
                using type = string;
                using fields = Fields;
            };

            template <typename Field, typename Fields>
            constexpr bool has_field(const string<Fields> &)
            {
                using ir::is_field;
                using ir::output::types::is_field;
                // disable ADL
                return (is_field)(Field{});
            }

            namespace numeric
            {
                template <typename Fields> struct int_
                {
                    using type = int_;
                    using fields = Fields;
                };

                template <typename Field, typename Fields>
                constexpr bool has_field(const int_<Fields> &)
                {
                    using ir::is_field;
                    using ir::output::types::is_field;
                    using ir::output::types::numeric::is_field;
                    // disable ADL
                    return (is_field)(Field{});
                }

                template <typename Fields> struct unsigned_
                {
                    using type = unsigned_;
                    using fields = Fields;
                };

                template <typename Field, typename Fields>
                constexpr bool has_field(const unsigned_<Fields> &)
                {
                    using ir::is_field;
                    using ir::output::types::is_field;
                    using ir::output::types::numeric::is_field;
                    // disable ADL
                    return (is_field)(Field{});
                }

                //
                // Types expecting runtime real numeric value
                //
                namespace real
                {
                    template <typename Fields> struct float_
                    {
                        using type = float_;
                        using fields = Fields;
                    };

                    template <typename Field, typename Fields>
                    constexpr bool has_field(const float_<Fields> &)
                    {
                        using ir::is_field;
                        using ir::output::types::is_field;
                        using ir::output::types::numeric::is_field;
                        using ir::output::types::numeric::real::is_field;
                        // disable ADL
                        return (is_field)(Field{});
                    }
                } // real
            }     // numeric
        }         // types
    }             // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_TYPES_HPP
