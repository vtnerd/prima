#ifndef PRIMA_IR_OUTPUT_MAKE_HPP
#define PRIMA_IR_OUTPUT_MAKE_HPP

#include "prima/ir/output/base.hpp"
#include "prima/ir/output/fields.hpp"
#include "prima/meta/base.hpp"

namespace prima
{
namespace ir
{
    namespace output
    {
        namespace make
        {
            template <typename Radix = types::numeric::values::radix<10>>
            using int_ = types::numeric::int_<
                meta::vector<types::values::precision<1>,
                             Radix,
                             types::numeric::values::only_print_negative_sign,
                             types::numeric::values::no_extra_blank_on_positive,
                             types::numeric::values::use_standard_format>>;

            template <typename Inner>
            using lower_case = format::lower_case<Inner>;

            template <typename Representation,
                      typename Radix = types::numeric::values::radix<10>>
            using float_ = types::numeric::real::float_<
                meta::vector<types::values::precision<6>,
                             Radix,
                             types::numeric::values::only_print_negative_sign,
                             types::numeric::values::no_extra_blank_on_positive,
                             types::numeric::values::use_standard_format,
                             Representation>>;

            using string = types::string<meta::vector<meta::void_>>;

            template <typename Inner>
            using upper_case = format::upper_case<Inner>;

            template <typename Radix = types::numeric::values::radix<10>>
            using unsigned_ = types::numeric::unsigned_<
                meta::vector<types::values::precision<1>,
                             Radix,
                             types::numeric::values::only_print_negative_sign,
                             types::numeric::values::no_extra_blank_on_positive,
                             types::numeric::values::use_standard_format>>;

            template <typename Width, typename Inner>
            using width =
                format::width<meta::vector<format::values::right_justified,
                                           format::values::pad_character<' '>,
                                           format::values::width<Width::value>>,
                              Inner>;

        } // make
    }     // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_MAKE_HPP
