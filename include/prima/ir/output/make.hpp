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
                      typename Case = values::lower_case,
                      typename Radix = values::radix<10>>
            using float_ = ::prima::ir::output::float_<
                meta::vector<values::right_justified,
                             values::precision<6>,
                             Case,
                             meta::void_, // width
                             values::pad_with_space,
                             Radix,
                             values::use_standard_format,
                             values::only_print_negative_sign,
                             values::no_extra_blank_on_positive,
                             values::representation<Format>>>;

            template <typename Radix = values::radix<10>>
            using int_ = ::prima::ir::output::int_<
                meta::vector<values::right_justified,
                             values::precision<1>,
                             values::lower_case,
                             meta::void_, // width
                             values::pad_with_space,
                             Radix,
                             values::use_standard_format,
                             values::only_print_negative_sign,
                             values::no_extra_blank_on_positive>>;

            using string = ::prima::ir::output::string<
                meta::vector<values::right_justified,
                             meta::void_,   // precision
                             meta::void_,   // casing
                             meta::void_>>; // width

            template <typename Radix = values::radix<10>,
                      typename Case = values::lower_case>
            using unsigned_ = ::prima::ir::output::unsigned_<
                meta::vector<values::right_justified,
                             values::precision<1>,
                             Case,
                             meta::void_, // width
                             values::pad_with_space,
                             Radix,
                             values::use_standard_format>>;
        } // make
    }     // output
} // ir
} // prima

#endif // PRIMA_IR_OUTPUT_MAKE_HPP
