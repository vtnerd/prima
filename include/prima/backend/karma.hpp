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
        ////////////////////////////////////////////////////////////////////////
        // Generic Output Functions                                           //
        ////////////////////////////////////////////////////////////////////////

        //
        // upper_case
        //
        struct upper_case
        {
            template <typename Inner>
            static auto apply(const Inner &inner,
                              const ir::output::values::upper_case &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::upper[inner]);
            }

            template <typename Inner>
            static auto apply(const Inner &inner,
                              const ir::output::values::lower_case &)
            {
                return boost::proto::deep_copy(inner);
            }

            template <typename Fields, typename Inner>
            static auto apply(const Inner &inner)
            {
                return apply(
                    inner,
                    ir::get_field_t<Fields, ir::output::fields::upper_case>{});
            }
        };

        //
        // width
        //
        struct width
        {
            template <typename Inner, typename Justification>
            static auto apply(const Inner &inner,
                              const char,
                              const meta::void_ &,
                              const Justification &)
            {
                return boost::proto::deep_copy(inner);
            }

            template <typename Inner, unsigned Width>
            static auto apply(const Inner &inner,
                              const char pad,
                              const ir::output::values::width<Width> &,
                              const ir::output::values::left_justified &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::left_align(Width, pad)[inner]);
            }

            template <typename Inner, unsigned Width>
            static auto apply(const Inner &inner,
                              const char pad,
                              const ir::output::values::width<Width> &,
                              const ir::output::values::right_justified &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::right_align(Width, pad)[inner]);
            }

            template <typename Fields, typename Inner>
            static auto apply(const Inner &inner, const char pad)
            {
                namespace fields = ir::output::fields;
                using justification =
                    ir::get_field_t<Fields, fields::left_justified>;
                using width = ir::get_field_t<Fields, fields::width>;

                return apply(inner, pad, width{}, justification{});
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
                return traits::truncate_to_long::call(
                    log10(traits::get_absolute_value(value)));
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

                static unsigned precision(const double value)
                {
                    switch (representation())
                    {
                    default:
                    case ir::output::values::real_format::fixed:
                    case ir::output::values::real_format::scientific:
                        return desired_precision();

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
                    }
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

        //
        // unsigned
        //
        template <typename Fields>
        struct generate_tree<ir::output::unsigned_<Fields>>
        {
            template <typename Inner>
            static const Inner &
            add_precision(const Inner &inner,
                          const ir::output::values::precision<1> &)
            {
                return inner;
            }

            template <typename Inner, unsigned Precision>
            static auto add_precision(
                const Inner &inner,
                const ir::output::values::precision<Precision> &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::right_align(Precision, '0')[inner]);
            }

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
                    add_precision(uint_generator{}, precision{}), pad));
            }
        };

        //
        // literal
        //
        template <char... Characters>
        struct generate_tree<ir::literal<Characters...>>
        {
            static const char *apply()
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
            template <typename Inner>
            static const Inner &
            add_precision(const Inner &inner, const meta::void_ &)
            {
                return inner;
            }

            template <typename Inner, unsigned Precision>
            static auto add_precision(
                const Inner &inner,
                const ir::output::values::precision<Precision> &)
            {
                return boost::proto::deep_copy(
                    boost::spirit::karma::maxwidth(Precision)[inner]);
            }

            static auto apply()
            {
                namespace fields = ir::output::fields;

                static_assert(meta::length_t<Fields>::value == 4,
                              "invalid fields");

                return width::apply<Fields>(
                    add_precision(boost::spirit::karma::string,
                                  ir::get_field_t<Fields, fields::precision>{}),
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
        //! \requires `Iterator` meets the requirements of the OutputIterator
        //!  concept.
        //!
        //! \throws Iff `boost::spirit::karma::generate` throws
        //!
        //! \return True if there were no errors while writing to `iterator`.
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

        //! template <typename IR,
        //!           typename Iterator,
        //!           typename Arg,
        //!           typename... Args>
        //! static bool generate(
        //!     Iterator&& iterator, const Arg1& arg, const Args&... args)
        //!
        //! Outputs the dynamic expression `IR` to `iterator`.
        //!
        //! \requires `Iterator` meets the requirements of the OutputIterator
        //!  concept.
        //!
        //! \throws Iff `boost::spirit::karma::generate` throws
        //!
        //! \return True if there were no errors while writing to `iterator`.
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
