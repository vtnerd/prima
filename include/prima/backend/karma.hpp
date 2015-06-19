#ifndef PRIMA_BACKEND_KARMA_HPP
#define PRIMA_BACKEND_KARMA_HPP

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/proto/deep_copy.hpp>
#include <boost/spirit/include/karma_char.hpp>
#include <boost/spirit/include/karma_generate.hpp>
#include <boost/spirit/include/karma_int.hpp>
#include <boost/spirit/include/karma_left_alignment.hpp>
#include <boost/spirit/include/karma_maxwidth.hpp>
#include <boost/spirit/include/karma_real.hpp>
#include <boost/spirit/include/karma_right_alignment.hpp>
#include <boost/spirit/include/karma_sequence.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_uint.hpp>
#include <boost/spirit/include/karma_upper_lower_case.hpp>

#include "prima/ir/base.hpp"
#include "prima/ir/manip.hpp"
#include "prima/ir/output/base.hpp"
#include "prima/ir/output/fields.hpp"
#include "prima/meta/base.hpp"

namespace prima
{
namespace backend
{
    class karma
    {
    private:
        template <typename Type> struct generate_tree;

        template <typename Inner>
        struct generate_tree<ir::output::format::lower_case<Inner>>
        {
            static auto apply()
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::lower[generate_tree<Inner>::apply()]);
            }
        };

        template <typename Inner>
        struct generate_tree<ir::output::format::upper_case<Inner>>
        {
            static auto apply()
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::upper[generate_tree<Inner>::apply()]);
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::types::numeric::real::float_<Fields>>
        {
            using representation = ir::get_field_t<
                Fields,
                ir::output::types::numeric::real::fields::representation>;

            enum class rep_type : std::uint8_t
            {
                fixed = 0,
                scientific,
                optimal
            };

            template <char Dot>
            constexpr static rep_type get_rep_type(
                const ir::output::types::numeric::real::values::fixed<Dot> &)
            {
                return rep_type::fixed;
            }

            template <char Scientific>
            constexpr static rep_type get_rep_type(
                const ir::output::types::numeric::real::values::scientific<
                    Scientific> &)
            {
                return rep_type::scientific;
            }

            template <char Dot, char Scientific>
            constexpr static rep_type
            get_rep_type(const ir::output::types::numeric::real::values::
                             optimal<Dot, Scientific> &)
            {
                return rep_type::optimal;
            }

            constexpr static rep_type get_rep_type()
            {
                return get_rep_type(representation{});
            }

            constexpr static bool use_alternate_format()
            {
                return ir::get_field_value<
                    Fields,
                    ir::output::types::numeric::fields::use_alternate_format>();
            }

            struct real_policy : boost::spirit::karma::real_policies<double>
            {
                using base = boost::spirit::karma::real_policies<double>;

                template <typename OutputIterator>
                static bool dot(OutputIterator &sink,
                                const double fractional,
                                const unsigned precision)
                {
                    namespace karma = boost::spirit::karma;

                    switch (get_rep_type())
                    {
                    default:
                    case rep_type::fixed:
                    case rep_type::scientific:
                        if (use_alternate_format() || 0 < precision)
                        {
                            return karma::char_inserter<>::call(
                                sink, representation::value);
                        }
                        break;

                    case rep_type::optimal:
                        if (use_alternate_format() ||
                            (1.0f > fractional && 0.0f <= fractional))
                        {
                            return karma::char_inserter<>::call(
                                sink, representation::value);
                        }
                        break;
                    }

                    return true;
                }

                static int floatfield(const double value)
                {
                    switch (get_rep_type())
                    {
                    default:
                    case rep_type::fixed:
                        return fmtflags::fixed;

                    case rep_type::scientific:
                        return fmtflags::scientific;

                    case rep_type::optimal:
                        if (value >= 0.0001 &&
                            value <= std::pow(10, precision(value)))
                        {
                            return fmtflags::fixed;
                        }
                        else
                        {
                            return fmtflags::scientific;
                        }
                    }
                }

                template <typename OutputIterator>
                static bool integer_part(OutputIterator &sink,
                                         const double n,
                                         const bool sign,
                                         const bool)
                {
                    namespace karma = boost::spirit::karma;

                    /* Karma doesn't do what we want for 0 values (doesn't print
                     * '+'), and doesn't add spaces on positive values, so do
                     * the sign and blank printing for karma. */
                    constexpr const bool blank_on_positive =
                        ir::get_field_value<Fields,
                                            ir::output::types::numeric::fields::
                                                extra_blank_on_positive>();
                    constexpr const bool always_print_sign = ir::get_field_value<
                        Fields,
                        ir::output::types::numeric::fields::always_print_sign>();

                    static_assert(!(blank_on_positive && always_print_sign),
                                  "invalid ir");

                    if (blank_on_positive && !sign)
                    {
                        if (!karma::char_inserter<>::call(sink, ' '))
                        {
                            return false;
                        }
                    }
                    else if (always_print_sign && !sign)
                    {
                        if (!karma::char_inserter<>::call(sink, '+'))
                        {
                            return false;
                        }
                    }

                    return base::integer_part(sink, n, sign, false);
                }

                static constexpr unsigned precision(double)
                {
                    return ir::get_field_value<
                        Fields,
                        ir::output::types::fields::precision>();
                }

                static bool trailing_zeros(double)
                {
                    switch (get_rep_type())
                    {
                    default:
                    case rep_type::fixed:
                    case rep_type::scientific:
                        return true;

                    case rep_type::optimal:
                        return !use_alternate_format();
                    }
                }
            };

            static auto apply()
            {
                using float_generator =
                    boost::spirit::karma::real_generator<double, real_policy>;
                return boost::proto::deep_copy(float_generator{});
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::types::numeric::int_<Fields>>
        {
            static auto apply()
            {
                namespace numeric_fields = ir::output::types::numeric::fields;
                static_assert(!ir::get_field_value<
                                  Fields,
                                  numeric_fields::extra_blank_on_positive>(),
                              "' ' flag not yet supported for integers");
                static_assert(
                    !ir::get_field_value<Fields,
                                         numeric_fields::use_alternate_format>(),
                    "'#' flag not yet supported for integers");
                static_assert(ir::get_field_value<
                                  Fields,
                                  ir::output::types::fields::precision>() == 1,
                              "only a precision of 1 is currently supported "
                              "for integers");
                using int_generator = boost::spirit::karma::int_generator<
                    int,
                    ir::get_field_value<Fields, numeric_fields::radix>(),
                    ir::get_field_value<Fields,
                                        numeric_fields::always_print_sign>()>;
                return boost::proto::deep_copy(int_generator{});
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::types::numeric::unsigned_<Fields>>
        {
            // \todo Remove code for '+' and ' ' flags, which are ignored by
            // unsigned types
            // \todo Detect the above in the frontend - which already needs an
            // overall
            using always_print_sign = ir::get_field_t<
                Fields,
                ir::output::types::numeric::fields::always_print_sign>;
            using precision =
                ir::get_field_t<Fields, ir::output::types::fields::precision>;

            static_assert(precision::value != 0,
                          "precision of 0 is not currently allowed for "
                          "unsigned "
                          "integers");
            static_assert(
                !ir::get_field_value<
                    Fields,
                    ir::output::types::numeric::fields::use_alternate_format>(),
                "'#' flag not yet supported for unsigned integers");

            static auto print_number()
            {
                constexpr auto radix = ir::get_field_value<
                    Fields,
                    ir::output::types::numeric::fields::radix>();
                using uint_generator =
                    boost::spirit::karma::uint_generator<unsigned, radix>;
                return boost::proto::deep_copy(uint_generator{});
            }

            static auto with_precision(
                const ir::output::types::values::precision<1> &)
            {
                return print_number();
            }

            template <typename Precision>
            static auto with_precision(const Precision &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::right_align(Precision::value,
                                                      '0')[print_number()]);
            }

            static auto print_sign(const meta::true_ &)
            {
                return boost::proto::deep_copy(boost::spirit::karma::lit("+")
                                               << with_precision(precision{}));
            }

            static auto print_sign(const meta::false_ &)
            {
                return with_precision(precision{});
            }

            static auto print_extra_blank(const meta::true_ &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::lit(" ")
                    << print_sign(always_print_sign{}));
            }

            static auto print_extra_blank(const meta::false_ &)
            {
                return print_sign(always_print_sign{});
            }

            static auto apply()
            {
                return print_extra_blank(
                    ir::get_field_t<Fields,
                                    ir::output::types::numeric::fields::
                                        extra_blank_on_positive>{});
            }
        };

        template <char... Characters>
        struct generate_tree<ir::literal<Characters...>>
        {
            static auto apply()
            {
                constexpr const static char literal_[] = {Characters..., 0};
                return literal_;
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::types::string<Fields>>
        {
            static auto with_precision(const meta::void_ &)
            {
                return boost::proto::deep_copy(boost::spirit::karma::string);
            }

            template <unsigned Value>
            static auto with_precision(
                const ir::output::types::values::precision<Value> &)
            {
                return boost::proto::deep_copy(boost::spirit::karma::maxwidth(
                    Value)[boost::spirit::karma::string]);
            }

            static auto apply()
            {
                return with_precision(
                    ir::get_field_t<Fields,
                                    ir::output::types::fields::precision>{});
            }
        };

        template <typename Left, typename Right>
        struct generate_tree<ir::sequence<Left, Right>>
        {
            static auto apply()
            {
                return boost::proto::deep_copy(
                    generate_tree<Left>::apply()
                    << generate_tree<Right>::apply());
            }
        };

        template <typename Fields, typename Inner>
        struct generate_tree<ir::output::format::width<Fields, Inner>>
        {
            static auto with_justification(
                const ir::output::format::values::left_justified &,
                const unsigned width)
            {
                return boost::proto::deep_copy(boost::spirit::karma::left_align(
                    width, ' ')[generate_tree<Inner>::apply()]);
            }

            static auto with_justification(
                const ir::output::format::values::right_justified &,
                const unsigned width)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::right_align(
                        width, ' ')[generate_tree<Inner>::apply()]);
            }

            static auto apply()
            {
                namespace fmt_fields = ir::output::format::fields;

                using justification =
                    ir::get_field_t<Fields, fmt_fields::left_justified>;
                constexpr const auto width =
                    ir::get_field_value<Fields, fmt_fields::width>();
                constexpr const auto pad =
                    ir::get_field_value<Fields, fmt_fields::pad_character>();
                static_assert(pad == ' ',
                              "'0' flag is currently not supported");

                return with_justification(justification{}, width);
            }
        };

    public:
        template <typename IR, typename Iterator>
        static bool generate(Iterator &&iterator)
        {
            return boost::spirit::karma::generate(
                std::forward<Iterator>(iterator), generate_tree<IR>::apply());
        }

        /* Forwarding with Karma doesn't work with a single entry. If the
           single entry is a mutable reference (l-value or r-value) it tries to
           create a reference from a const-reference. Theres no need for
           mutable references until %n is supported, which will be tricky
           with karma anyway. */
        template <typename IR, typename Iterator, typename Arg1, typename... Args>
        static bool
        generate(Iterator &&iterator, const Arg1 &arg1, const Args &... args)
        {
            return boost::spirit::karma::generate(
                std::forward<Iterator>(iterator),
                generate_tree<IR>::apply(),
                std::tie<const Arg1 &, const Args &...>(arg1, args...));
        }
    };
} // convert
} // prima

#endif // PRIMA_BACKEND_KARMA_HPP
