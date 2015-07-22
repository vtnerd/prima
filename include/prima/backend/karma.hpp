#ifndef PRIMA_BACKEND_KARMA_HPP
#define PRIMA_BACKEND_KARMA_HPP

#include <limits>

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
#include "prima/ir/output/base.hpp"
#include "prima/ir/output/fields.hpp"
#include "prima/meta/base.hpp"

namespace prima
{
namespace backend
{
    //! karma
    //!
    //! Output generator that uses boost::spirit::karma.
    class karma
    {
    private:
        /* Be careful with c++14 automatic return type deduction. During
         * overload selection, all such functions must be instantiated in their
         * entirety. This section uses class partial-template specialization to
         * limit the overload selection where possible. */

        ////////////////////////////////////////////////////////////////////////
        // Generic Output Functions                                           //
        ////////////////////////////////////////////////////////////////////////

        //
        // upper_case
        //
        struct upper_case
        {
            template <typename Inner, typename Case> struct impl
            {
                static auto apply(const Inner& inner)
                {
                    return boost::proto::deep_copy(
                        boost::spirit::karma::upper[inner]);
                }
            };

            template <typename Inner>
            struct impl<Inner, ir::output::values::lower_case>
            {
                static auto apply(const Inner& inner)
                {
                    return boost::proto::deep_copy(inner);
                }
            };

            template <typename Fields, typename Inner>
            static auto apply(const Inner& inner)
            {
                return impl<
                    Inner,
                    ir::get_field_t<Fields, ir::output::fields::upper_case>>::
                    apply(inner);
            }
        };

        //
        // width
        //
        struct width
        {
            template <typename, typename> struct impl;

            template <typename Justification>
            struct impl<meta::void_, Justification>
            {
                template <typename Inner>
                static auto apply(const Inner& inner, const char)
                {
                    return boost::proto::deep_copy(inner);
                }
            };

            template <unsigned Width>
            struct impl<ir::output::values::width<Width>,
                        ir::output::values::left_justified>
            {
                template <typename Inner>
                static auto apply(const Inner& inner, const char pad)
                {
                    return boost::proto::deep_copy(
                        boost::spirit::karma::left_align(Width, pad)[inner]);
                }
            };

            template <unsigned Width>
            struct impl<ir::output::values::width<Width>,
                        ir::output::values::right_justified>
            {
                template <typename Inner>
                static auto apply(const Inner& inner, const char pad)
                {
                    return boost::proto::deep_copy(
                        boost::spirit::karma::right_align(Width, pad)[inner]);
                }
            };

            template <typename Fields, typename Inner>
            static auto apply(const Inner& inner, const char pad)
            {
                namespace fields = ir::output::fields;
                using justification =
                    ir::get_field_t<Fields, fields::left_justified>;
                using width = ir::get_field_t<Fields, fields::width>;

                return impl<width, justification>::apply(inner, pad);
            }
        };

        ////////////////////////////////////////////////////////////////////////
        // IR Output Functions                                                //
        ////////////////////////////////////////////////////////////////////////

        template <typename Type> struct generate_tree;

        //
        // float
        //
        template <typename Fields>
        struct generate_tree<ir::output::float_<Fields>>
        {
            static constexpr unsigned desired_precision() noexcept
            {
                return ir::get_field_value<Fields,
                                           ir::output::fields::precision>();
            }

            static long get_exponent(const double value)
            {
                using std::log10;
                namespace traits = boost::spirit::traits;
                if (traits::test_zero(value))
                {
                    return 0;
                }
                const long raw_exp = traits::truncate_to_long::call(
                    log10(traits::get_absolute_value(value)));

                return traits::test_negative(raw_exp) ? raw_exp - 1 : raw_exp;
            }

            template <typename OutputIterator>
            static bool handle_sign(OutputIterator& sink, const bool sign)
            {
                namespace karma = boost::spirit::karma;
                constexpr const bool blank_on_positive = ir::get_field_value<
                    Fields,
                    ir::output::fields::extra_blank_on_positive>();
                constexpr const bool always_print_sign =
                    ir::get_field_value<Fields,
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

                return true;
            }

            constexpr static ir::output::values::real_format
            representation() noexcept
            {
                return ir::get_field_value<Fields,
                                           ir::output::fields::representation>();
            }

            constexpr static bool use_alternate_format() noexcept
            {
                return ir::get_field_value<
                    Fields,
                    ir::output::fields::use_alternate_format>();
            }

            struct real_policy : boost::spirit::karma::real_policies<double>
            {
                using base = boost::spirit::karma::real_policies<double>;

                template <typename OutputIterator>
                static bool dot(OutputIterator& sink,
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
                static bool exponent(OutputIterator& sink, const long n)
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
                        const auto exp = get_exponent(value);
                        constexpr const unsigned precision_ =
                            desired_precision() ? desired_precision() : 1;
                        if (exp >= -4 && exp < precision_)
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

                static bool force_sign(double)
                {
                    /* Karma doesn't do what we want for 0 values (doesn't print
                     * '+'), and doesn't add spaces on positive values, so do
                     * the sign and blank printing for karma. */
                    return false;
                }

                template <typename OutputIterator>
                static bool fraction_part(OutputIterator& sink,
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

                template <typename CharEncoding,
                          typename Tag,
                          typename OutputIterator>
                static bool
                inf(OutputIterator& sink, const double n, const bool)
                {
                    namespace traits = boost::spirit::traits;
                    return handle_sign(sink, traits::test_negative(n)) &&
                           base::inf<CharEncoding, Tag>(sink, n, false);
                }

                template <typename OutputIterator>
                static bool integer_part(OutputIterator& sink,
                                         const double n,
                                         const bool sign,
                                         const bool)
                {
                    return handle_sign(sink, sign) &&
                           base::integer_part(sink, n, sign, false);
                }

                template <typename CharEncoding,
                          typename Tag,
                          typename OutputIterator>
                static bool
                nan(OutputIterator& sink, const double n, const bool)
                {
                    namespace traits = boost::spirit::traits;
                    return handle_sign(sink, traits::test_negative(n)) &&
                           base::nan<CharEncoding, Tag>(sink, n, false);
                }

                static unsigned precision(const double value)
                {
                    switch (representation())
                    {
                    case ir::output::values::real_format::optimal:
                    {
                        constexpr const unsigned precision_ =
                            desired_precision() ? desired_precision() : 1;
                        switch (floatfield(value))
                        {
                        case fmtflags::fixed:
                            assert(get_exponent(value) >= -4);
                            assert(precision_ > get_exponent(value));
                            static_assert(
                                std::numeric_limits<unsigned>::max() <=
                                    std::numeric_limits<long long>::max(),
                                "");
                            static_assert(
                                precision_ <=
                                    std::numeric_limits<unsigned>::max() - 3,
                                "");

                            return static_cast<long long>(precision_) -
                                   (get_exponent(value) + 1);

                        case fmtflags::scientific:
                            return precision_ - 1;
                        }
                    }

                    default:
                    case ir::output::values::real_format::fixed:
                    case ir::output::values::real_format::scientific:
                        break;
                    }

                    return desired_precision();
                }

                static bool trailing_zeros(double) noexcept
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
                namespace fields = ir::output::fields;

                static_assert(meta::length_t<Fields>::value == 10,
                              "invalid fields");
                static_assert(ir::get_field_value<Fields, fields::radix>() ==
                                  10,
                              "Decimal output only for float generator");

                using float_generator =
                    boost::spirit::karma::real_generator<double, real_policy>;
                return upper_case::apply<Fields>(float_generator{});
            }
        };

        //
        // int
        //
        template <typename Fields>
        struct generate_tree<ir::output::int_<Fields>>
        {
            static auto apply()
            {
                namespace fields = ir::output::fields;

                static_assert(meta::length_t<Fields>::value == 9,
                              "invalid fields");
                static_assert(
                    !ir::get_field_value<Fields,
                                         fields::extra_blank_on_positive>(),
                    "' ' flag not yet supported for integers");
                static_assert(
                    !ir::get_field_value<Fields, fields::pad_with_zero>(),
                    "'0' flag not yet supported for integers");
                static_assert(
                    ir::get_field_value<Fields, fields::precision>() == 1,
                    "only a precision of 1 is currently supported "
                    "for integers");
                static_assert(
                    !ir::get_field_value<Fields, fields::use_alternate_format>(),
                    "'#' flag not yet supported for integers");

                using int_generator = boost::spirit::karma::int_generator<
                    int,
                    ir::get_field_value<Fields, fields::radix>(),
                    ir::get_field_value<Fields, fields::always_print_sign>()>;
                return width::apply<Fields>(int_generator{}, ' ');
            }
        };

        //
        // unsigned
        //
        template <typename Fields>
        struct generate_tree<ir::output::unsigned_<Fields>>
        {
            template <typename, typename> struct add_precision;

            template <typename Ignored>
            struct add_precision<ir::output::values::precision<1>, Ignored>
            {
                template <typename Inner>
                static const Inner& apply(const Inner& inner)
                {
                    return inner;
                }
            };

            template <unsigned Precision, typename Ignored>
            struct add_precision<ir::output::values::precision<Precision>,
                                 Ignored>
            {
                template <typename Inner> static auto apply(const Inner& inner)
                {
                    return boost::proto::deep_copy(
                        boost::spirit::karma::right_align(Precision,
                                                          '0')[inner]);
                }
            };

            static auto apply()
            {
                namespace fields = ir::output::fields;
                using precision = ir::get_field_t<Fields, fields::precision>;

                static_assert(meta::length_t<Fields>::value == 7,
                              "invalid fields");
                static_assert(precision::value != 0,
                              "precision of 0 is not currently allowed for "
                              "unsigned integers");
                static_assert(
                    !ir::get_field_value<Fields, fields::use_alternate_format>(),
                    "'#' flag not yet supported for unsigned integers");

                constexpr const char pad =
                    ir::get_field_value<Fields, fields::pad_with_zero>() ? '0' :
                                                                           ' ';
                constexpr const unsigned radix =
                    ir::get_field_value<Fields, fields::radix>();

                using uint_generator =
                    boost::spirit::karma::uint_generator<unsigned, radix>;
                return upper_case::apply<Fields>(width::apply<Fields>(
                    add_precision<precision, bool>::apply(uint_generator{}),
                    pad));
            }
        };

        //
        // literal
        //
        template <char... Characters>
        struct generate_tree<ir::literal<Characters...>>
        {
            static const char* apply()
            {
                constexpr const static char literal_[] = {Characters..., 0};
                return literal_;
            }
        };

        //
        // string
        //
        template <typename Fields>
        struct generate_tree<ir::output::string<Fields>>
        {
            template <typename> struct add_precision
            {
                template <typename Inner>
                static const Inner& apply(const Inner& inner)
                {
                    return inner;
                }
            };

            template <unsigned Precision>
            struct add_precision<ir::output::values::precision<Precision>>
            {
                template <typename Inner> static auto apply(const Inner& inner)
                {
                    return boost::proto::deep_copy(
                        boost::spirit::karma::maxwidth(Precision)[inner]);
                }
            };

            static auto apply()
            {
                namespace fields = ir::output::fields;

                static_assert(meta::length_t<Fields>::value == 4,
                              "invalid fields");

                return width::apply<Fields>(
                    add_precision<ir::get_field_t<Fields, fields::precision>>::
                        apply(boost::spirit::karma::string),
                    ' ');
            }
        };

        //
        // sequence
        //
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

    public:
        //! template <typename IR, typename Iterator>
        //! static bool generate(Iterator&& iterator)
        //!
        //! Outputs the static expression `IR` to `iterator`.
        //!
        //! \requires `IR` is output from frontend::sprintf_parser_func.
        //! \requires `Iterator` meets the requirements of the OutputIterator
        //!  concept.
        //!
        //! \throws Iff `boost::spirit::karma::generate` throws
        //!
        //! \return Result of `boost::spirit::karma::generate`.
        template <typename IR, typename Iterator>
        static bool generate(Iterator&& iterator)
        {
            return boost::spirit::karma::generate(
                std::forward<Iterator>(iterator), generate_tree<IR>::apply());
        }

        /* Forwarding with Karma doesn't work with a single entry. If the
           single entry is a mutable reference (l-value or r-value) it tries to
           create a reference from a const-reference. Theres no need for
           mutable references until %n is supported, which will be tricky
           with karma anyway. */

        //! template <typename IR,
        //!           typename Iterator,
        //!           typename Arg,
        //!           typename... Args>
        //! static bool generate(
        //!     Iterator&& iterator, const Arg1& arg, const Args&... args)
        //!
        //! Outputs the dynamic expression `IR` to `iterator`.
        //!
        //! \requires `IR` is output from frontend::sprintf_parser_func.
        //! \requires `Iterator` meets the requirements of the OutputIterator
        //!  concept.
        //!
        //! \throws Iff `boost::spirit::karma::generate` throws
        //!
        //! \return Result of `boost::spirit::karma::generate`.
        template <typename IR, typename Iterator, typename Arg1, typename... Args>
        static bool
        generate(Iterator&& iterator, const Arg1& arg1, const Args&... args)
        {
            return boost::spirit::karma::generate(
                std::forward<Iterator>(iterator),
                generate_tree<IR>::apply(),
                std::tie<const Arg1&, const Args&...>(arg1, args...));
        }
    };
} // convert
} // prima

#endif // PRIMA_BACKEND_KARMA_HPP
