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

        class generate_format_func
        {
        private:
            template <typename Field, typename Type>
            constexpr static bool has_field_(const Type &type)
            {
                using ir::has_field;
                return has_field<Field>(type);
            }

            template <typename Width, typename Type> struct state
            {
                using width = Width;
                using type = Type;

                struct width_with_type
                {
                    using type =
                        oir::format::width<typename Width::fields, Type>;
                };
            };

            template <bool IsWidthField,
                      typename State,
                      typename Field,
                      typename Value>
            struct next_state
            {
                using type = state<
                    typename State::width,
                    ir::manip::update_fields_t<
                        typename State::type,
                        ir::manip::update_field_t<typename State::type::fields,
                                                  Field,
                                                  Value>>>;
            };

            template <typename State, typename Field, typename Value>
            struct next_state<true, State, Field, Value>
            {
                using type = state<
                    ir::manip::update_fields_t<
                        typename State::width,
                        ir::manip::update_field_t<typename State::width::fields,
                                                  Field,
                                                  Value>>,
                    typename State::type>;
            };

            struct update_state_func
            {
                template <typename State, typename FieldValue> class apply
                {
                private:
                    using field = meta::at_ct<FieldValue, 0>;
                    constexpr const static bool is_width_field =
                        has_field_<field>(typename State::width{});
                    constexpr const static bool is_type_field =
                        has_field_<field>(typename State::type{});
                    static_assert(is_width_field != is_type_field,
                                  "invalid field");

                public:
                    using type =
                        typename next_state<is_width_field,
                                            State,
                                            field,
                                            meta::at_ct<FieldValue, 1>>::type;
                };
            };

        public:
            template <typename Sequence> class apply
            {
            private:
                using width_uint = meta::at_ct<Sequence, 1>;
                using precision_uint = meta::at_ct<Sequence, 2>;
                using output_type = meta::at_ct<Sequence, 3>;

                static_assert(
                    has_field_<oir::types::fields::precision>(output_type{}),
                    "invalid type field");

                using normalized_precision =
                    meta::if_t<meta::is_void_<precision_uint>,
                               meta::unsigned_<0>,
                               precision_uint>;

                using type_with_precision = meta::eval_if_t<
                    meta::is_void_<precision_uint>,
                    output_type,
                    meta::lazy<ir::manip::update_fields_func,
                               output_type,
                               ir::manip::update_field<
                                   typename output_type::fields,
                                   oir::types::fields::precision,
                                   oir::types::values::precision<
                                       normalized_precision::value>>>>;

                using normalized_width = meta::if_t<meta::is_void_<width_uint>,
                                                    meta::unsigned_<0>,
                                                    width_uint>;

                using start_state = meta::if_t<
                    meta::is_void_<width_uint>,
                    state<meta::void_, type_with_precision>,
                    state<oir::make::width<normalized_width, meta::void_>,
                          type_with_precision>>;

                // Fold flags. Flags invalid for type are aborted immediately
                using final_state = meta::fold_t<meta::at_ct<Sequence, 0>,
                                                 start_state,
                                                 update_state_func>;

            public:
                using type =
                    meta::eval_if_t<meta::is_void_<typename final_state::width>,
                                    final_state,
                                    typename final_state::width_with_type>;
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
                         oir::make::lower_case<oir::make::float_<
                             oir::types::numeric::real::values::fixed<'.'>,
                             oir::types::numeric::values::radix<16>>>>,
            mp::always_c<'A',
                         oir::make::upper_case<oir::make::float_<
                             oir::types::numeric::real::values::fixed<'.'>,
                             oir::types::numeric::values::radix<16>>>>,
            mp::always_c<'e',
                         oir::make::float_<
                             oir::types::numeric::real::values::scientific<'e'>>>,
            mp::always_c<'E',
                         oir::make::float_<
                             oir::types::numeric::real::values::scientific<'E'>>>,
            mp::always_c<'f',
                         oir::make::float_<
                             oir::types::numeric::real::values::fixed<'.'>>>,
            mp::always_c<'g',
                         oir::make::float_<oir::types::numeric::real::values::
                                               optimal<'.', 'e'>>>,
            mp::always_c<'G',
                         oir::make::float_<oir::types::numeric::real::values::
                                               optimal<'.', 'e'>>>,
            mp::always_c<'s', oir::make::string>,
            mp::always_c<
                'o',
                oir::make::unsigned_<oir::types::numeric::values::radix<8>>>,
            mp::always_c<'u', oir::make::unsigned_<>>,
            mp::always_c<'x',
                         oir::make::lower_case<oir::make::unsigned_<
                             oir::types::numeric::values::radix<16>>>>,
            mp::always_c<'X',
                         oir::make::upper_case<oir::make::unsigned_<
                             oir::types::numeric::values::radix<16>>>>>;

        using flags = mp::any<mp::one_of<
            mp::always_c<
                '#',
                meta::vector<oir::types::numeric::fields::use_alternate_format,
                             meta::true_>>,
            mp::always_c<
                ' ',
                meta::vector<oir::types::numeric::fields::extra_blank_on_positive,
                             meta::true_>>,
            mp::always_c<
                '+',
                meta::vector<oir::types::numeric::fields::always_print_sign,
                             meta::true_>>,
            mp::always_c<
                '-',
                meta::vector<oir::format::fields::left_justified, meta::true_>>,
            mp::always_c<'0',
                         meta::vector<oir::format::fields::pad_character,
                                      meta::char_<'0'>>>>>;
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
