#ifndef PRIMA_FRONTEND_SPRINTF_HPP
#define PRIMA_FRONTEND_SPRINTF_HPP

#include <mpllibs/metaparse/always.hpp>
#include <mpllibs/metaparse/always_c.hpp>
#include <mpllibs/metaparse/any.hpp>
#include <mpllibs/metaparse/build_parser.hpp>
#include <mpllibs/metaparse/digit.hpp>
#include <mpllibs/metaparse/foldl1.hpp>
#include <mpllibs/metaparse/foldlp.hpp>
#include <mpllibs/metaparse/int_.hpp>
#include <mpllibs/metaparse/last_of.hpp>
#include <mpllibs/metaparse/lit_c.hpp>
#include <mpllibs/metaparse/one_char_except.hpp>
#include <mpllibs/metaparse/one_of.hpp>
#include <mpllibs/metaparse/return_.hpp>
#include <mpllibs/metaparse/sequence.hpp>
#include <mpllibs/metaparse/transform.hpp>

#include "prima/ir/base.hpp"
#include "prima/ir/make.hpp"
#include "prima/ir/manip.hpp"
#include "prima/ir/output/make.hpp"
#include "prima/meta/base.hpp"
#include "prima/meta/funcs.hpp"

namespace prima
{
namespace frontend
{
    namespace detail
    {
        namespace mp = mpllibs::metaparse;
        namespace oir = ir::output;

        struct generate_format_func
        {
            constexpr const static unsigned flags_loc = 0;
            constexpr const static unsigned width_loc = 1;
            constexpr const static unsigned precision_loc = 2;
            constexpr const static unsigned format_loc = 3;

            template <typename Formatting> class apply
            {
            private:
                using width = meta::at_ct<Formatting, width_loc>;
                using precision = meta::at_ct<Formatting, precision_loc>;
                using format = meta::at_ct<Formatting, format_loc>;

                static_assert(ir::has_field(format{}, oir::fields::precision{}),
                              "invalid format field");

                using normalized_precision =
                    meta::if_t<meta::is_void_<precision>,
                               meta::unsigned_<0>,
                               precision>;

                using format_with_precision = meta::eval_if_t<
                    meta::is_void_<precision>,
                    format,
                    ir::manip::update_field<
                        format,
                        oir::fields::precision,
                        oir::values::precision<normalized_precision::value>>>;

                using normalized_width =
                    meta::if_t<meta::is_void_<width>, meta::unsigned_<0>, width>;

                using format_without_flags = meta::eval_if_t<
                    meta::is_void_<width>,
                    format_with_precision,
                    ir::manip::update_field<
                        format_with_precision,
                        oir::fields::width,
                        oir::values::width<normalized_width::value>>>;

            public:
                using type = meta::fold_t<meta::at_ct<Formatting, flags_loc>,
                                          format_without_flags,
                                          ir::manip::update_field_func>;

                static_assert(ir::has_field(type{}, oir::fields::precision{}),
                              "internal error");
            };
        };

        using mp::int_;
        using char_ = mp::one_of<mp::last_of<mp::lit_c<'%'>, mp::lit_c<'%'>>,
                                 mp::one_char_except<meta::char_<'%'>>>;
        using literal = mp::foldl1<char_, ir::literal<>, meta::push_back_func>;

        using type = mp::one_of<
            mp::always<mp::one_of<mp::lit_c<'c'>, mp::lit_c<'d'>, mp::lit_c<'i'>>,
                       oir::make::int_<>>,
            mp::always_c<'a',
                         oir::make::float_<oir::values::real_format::fixed,
                                           oir::values::radix<16>>>,
            mp::always_c<'A',
                         oir::make::float_<oir::values::real_format::fixed,
                                           oir::values::upper_case,
                                           oir::values::radix<16>>>,
            mp::always_c<'e',
                         oir::make::float_<oir::values::real_format::scientific>>,
            mp::always_c<'E',
                         oir::make::float_<oir::values::real_format::scientific,
                                           oir::values::upper_case>>,
            mp::always_c<'f', oir::make::float_<oir::values::real_format::fixed>>,
            mp::always_c<'F',
                         oir::make::float_<oir::values::real_format::fixed,
                                           oir::values::upper_case>>,
            mp::always_c<'g',
                         oir::make::float_<oir::values::real_format::optimal>>,
            mp::always_c<'G',
                         oir::make::float_<oir::values::real_format::optimal>>,
            mp::always_c<'s', oir::make::string>,
            mp::always_c<'o', oir::make::unsigned_<oir::values::radix<8>>>,
            mp::always_c<'u', oir::make::unsigned_<>>,
            mp::always_c<'x', oir::make::unsigned_<oir::values::radix<16>>>,
            mp::always_c<'X',
                         oir::make::unsigned_<oir::values::radix<16>,
                                              oir::values::upper_case>>>;

        using flags = mp::any<mp::one_of<
            mp::always_c<
                '#',
                meta::vector<oir::fields::use_alternate_format, meta::true_>>,
            mp::always_c<
                ' ',
                meta::vector<oir::fields::extra_blank_on_positive, meta::true_>>,
            mp::always_c<
                '+',
                meta::vector<oir::fields::always_print_sign, meta::true_>>,
            mp::always_c<'-',
                         meta::vector<oir::fields::left_justified, meta::true_>>,
            mp::always_c<'0',
                         meta::vector<oir::fields::pad_with_zero, meta::true_>>>>;
        using width = mp::one_of<int_, mp::return_<meta::void_>>;
        using precision = mp::one_of<mp::last_of<mp::lit_c<'.'>, int_>,
                                     mp::return_<meta::void_>>;

        using format_specifier = mp::last_of<
            mp::lit_c<'%'>,
            mp::transform<mp::sequence<flags, width, precision, type>,
                          generate_format_func>>;

        using base = mp::one_of<literal, format_specifier>;

        using format = mp::foldlp<base, base, ir::make::sequence_func>;
    } // detail

    using sprintf_parser_func =
        typename detail::mp::build_parser<detail::format>::type;

    template <typename Format>
    using parse_sprintf_t = meta::invoke<sprintf_parser_func, Format>;
}
}

#endif // PRIMA_FRONTEND_SPRINTF_HPP
