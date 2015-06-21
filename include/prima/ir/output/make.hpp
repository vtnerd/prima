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
            template <values::real_format Format,
                      typename Radix = values::radix<10>>
            using float_ = ::prima::ir::output::float_<
                meta::vector<values::precision<6>,
                             Radix,
                             values::use_standard_format,
                             values::only_print_negative_sign,
                             values::no_extra_blank_on_positive,
                             values::representation<Format>>>;

            template <typename Radix = values::radix<10>>
            using int_ = ::prima::ir::output::int_<
                meta::vector<values::precision<1>,
                             Radix,
                             values::use_standard_format,
                             values::only_print_negative_sign,
                             values::no_extra_blank_on_positive>>;

            using string = ::prima::ir::output::string<meta::vector<meta::void_>>;

            template <typename Inner>
            using upper_case = ::prima::ir::output::upper_case<Inner>;

            template <typename Radix = values::radix<10>>
            using unsigned_ = ::prima::ir::output::unsigned_<
                meta::vector<values::precision<1>,
                             Radix,
                             values::use_standard_format>>;

            template <typename Width, typename Inner>
            using width = ::prima::ir::output::width<
                meta::vector<values::right_justified,
                             values::pad_character<' '>,
                             values::width<Width::value>>,
                Inner>;

        } // make
    }     // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_MAKE_HPP
