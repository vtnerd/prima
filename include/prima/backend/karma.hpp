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
        struct generate_tree<ir::output::upper_case<Inner>>
        {
            static auto apply()
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::upper[generate_tree<Inner>::apply()]);
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::float_<Fields>>
        {
            constexpr static ir::output::values::real_format representation()
            {
                return ir::get_field_value<Fields,
                                           ir::output::fields::representation>();
            }

            constexpr static bool use_alternate_format()
            {
                return ir::get_field_value<
                    Fields,
                    ir::output::fields::use_alternate_format>();
            }

            struct real_policy : boost::spirit::karma::real_policies<double>
            {
                using base = boost::spirit::karma::real_policies<double>;

                template <typename OutputIterator>
                static bool dot(OutputIterator &sink,
                                const double fractional,
                                const unsigned precision)
                {
                    switch (representation())
                    {
                    default:
                    case ir::output::values::real_format::fixed:
                    case ir::output::values::real_format::scientific:
                        if (use_alternate_format() || 0 < precision)
                        {
                            return base::dot(sink, fractional, precision);
                        }
                        break;

                    case ir::output::values::real_format::optimal:
                        if (use_alternate_format() ||
                            !boost::spirit::traits::test_zero(fractional))
                        {
                            return base::dot(sink, fractional, precision);
                        }
                        break;
                    }

                    return true;
                }

                template <typename CharEncoding,
                          typename Tag,
                          typename OutputIterator>
                static bool exponent(OutputIterator &sink, const long n)
                {
                    namespace karma = boost::spirit::karma;

                    const long abs_n =
                        boost::spirit::traits::get_absolute_value(n);
                    bool r =
                        karma::char_inserter<CharEncoding, Tag>::call(sink,
                                                                      'e') &&
                        karma::sign_inserter::call(
                            sink,
                            boost::spirit::traits::test_zero(n),
                            boost::spirit::traits::test_negative(n),
                            true,
                            true);

                    // the C99 Standard requires at least two digits in the
                    // exponent
                    if (r && abs_n < 10)
                    {
                        r = karma::char_inserter<CharEncoding, Tag>::call(sink,
                                                                          '0');
                    }
                    return r && karma::int_inserter<10>::call(sink, abs_n);
                }

                static int floatfield(const double value)
                {
                    switch (representation())
                    {
                    default:
                    case ir::output::values::real_format::fixed:
                        return fmtflags::fixed;

                    case ir::output::values::real_format::scientific:
                        return fmtflags::scientific;

                    case ir::output::values::real_format::optimal:
                    {
                        const double abs_value =
                            boost::spirit::traits::get_absolute_value(value);
                        if ((abs_value >= 0.0001 &&
                             abs_value <= std::pow(10, precision())) ||
                            boost::spirit::traits::test_zero(value))
                        {
                            return fmtflags::fixed;
                        }
                        else
                        {
                            return fmtflags::scientific;
                        }
                    }
                    }
                }

                template <typename OutputIterator>
                static bool fraction_part(OutputIterator &sink,
                                          double n,
                                          unsigned precision_,
                                          unsigned precision)
                {
                    // allow for ADL to find the correct overload for floor and
                    // log10
                    using namespace std;
                    namespace karma = boost::spirit::karma;

                    // The following is equivalent to:
                    //    generate(sink, right_align(precision, '0')[ulong], n);
                    // but it's spelled out to avoid inter-modular dependencies.

                    double digits = (boost::spirit::traits::test_zero(n) ?
                                         0 :
                                         floor(log10(n))) +
                                    1;
                    bool r = true;
                    for (/**/; r && digits < precision_; digits = digits + 1)
                        r = karma::char_inserter<>::call(sink, '0');
                    if (precision_ && r)
                        r = karma::int_inserter<10>::call(sink, n);
                    return r;
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
                        ir::get_field_value<
                            Fields,
                            ir::output::fields::extra_blank_on_positive>();
                    constexpr const bool always_print_sign =
                        ir::get_field_value<
                            Fields,
                            ir::output::fields::always_print_sign>();

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

                static constexpr unsigned precision()
                {
                    return ir::get_field_value<Fields,
                                               ir::output::fields::precision>();
                }

                static unsigned precision(const double value)
                {
                    switch (representation())
                    {
                    default:
                    case ir::output::values::real_format::fixed:
                    case ir::output::values::real_format::scientific:
                        return precision();

                    case ir::output::values::real_format::optimal:
                        switch (floatfield(value))
                        {
                        case fmtflags::fixed:
                            return precision();

                        case fmtflags::scientific:
                            return precision() ? precision() - 1 : 0;
                        }
                    }
                }

                static bool trailing_zeros(double)
                {
                    switch (representation())
                    {
                    default:
                    case ir::output::values::real_format::fixed:
                    case ir::output::values::real_format::scientific:
                        return true;

                    case ir::output::values::real_format::optimal:
                        return use_alternate_format();
                    }
                }
            };

            static auto apply()
            {
                static_assert(
                    ir::get_field_value<Fields, ir::output::fields::radix>() ==
                        10,
                    "Decimal output only for float generator");
                using float_generator =
                    boost::spirit::karma::real_generator<double, real_policy>;
                return boost::proto::deep_copy(float_generator{});
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::int_<Fields>>
        {
            static auto apply()
            {
                namespace fields = ir::output::fields;

                static_assert(
                    !ir::get_field_value<Fields,
                                         fields::extra_blank_on_positive>(),
                    "' ' flag not yet supported for integers");
                static_assert(
                    !ir::get_field_value<Fields, fields::use_alternate_format>(),
                    "'#' flag not yet supported for integers");
                static_assert(
                    ir::get_field_value<Fields, fields::precision>() == 1,
                    "only a precision of 1 is currently supported "
                    "for integers");
                using int_generator = boost::spirit::karma::int_generator<
                    int,
                    ir::get_field_value<Fields, fields::radix>(),
                    ir::get_field_value<Fields, fields::always_print_sign>()>;
                return boost::proto::deep_copy(int_generator{});
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::unsigned_<Fields>>
        {
            using precision =
                ir::get_field_t<Fields, ir::output::fields::precision>;

            static_assert(precision::value != 0,
                          "precision of 0 is not currently allowed for "
                          "unsigned integers");
            static_assert(
                !ir::get_field_value<Fields,
                                     ir::output::fields::use_alternate_format>(),
                "'#' flag not yet supported for unsigned integers");

            static auto print_number()
            {
                constexpr auto radix =
                    ir::get_field_value<Fields, ir::output::fields::radix>();
                using uint_generator =
                    boost::spirit::karma::uint_generator<unsigned, radix>;
                return boost::proto::deep_copy(uint_generator{});
            }

            static auto with_precision(const ir::output::values::precision<1> &)
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

            static auto apply()
            {
                return with_precision(precision{});
            }
        };

        template <char... Characters>
        struct generate_tree<ir::literal<Characters...>>
        {
            static const char *apply()
            {
                constexpr const static char literal_[] = {Characters..., 0};
                return literal_;
            }
        };

        template <typename Fields>
        struct generate_tree<ir::output::string<Fields>>
        {
            static auto with_precision(const meta::void_ &)
            {
                return boost::proto::deep_copy(boost::spirit::karma::string);
            }

            template <unsigned Value>
            static auto with_precision(
                const ir::output::values::precision<Value> &)
            {
                return boost::proto::deep_copy(boost::spirit::karma::maxwidth(
                    Value)[boost::spirit::karma::string]);
            }

            static auto apply()
            {
                return with_precision(
                    ir::get_field_t<Fields, ir::output::fields::precision>{});
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
        struct generate_tree<ir::output::width<Fields, Inner>>
        {
            static auto with_justification(
                const ir::output::values::left_justified &,
                const unsigned width)
            {
                return boost::proto::deep_copy(boost::spirit::karma::left_align(
                    width, ' ')[generate_tree<Inner>::apply()]);
            }

            static auto with_justification(
                const ir::output::values::right_justified &,
                const unsigned width)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::right_align(
                        width, ' ')[generate_tree<Inner>::apply()]);
            }

            static auto apply()
            {
                namespace fields = ir::output::fields;

                using justification =
                    ir::get_field_t<Fields, fields::left_justified>;
                constexpr const auto width =
                    ir::get_field_value<Fields, fields::width>();
                constexpr const auto pad =
                    ir::get_field_value<Fields, fields::pad_character>();
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
