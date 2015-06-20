#ifndef PRIMA_META_FUNCS_HPP
#define PRIMA_META_FUNCS_HPP

#include <cstdint>

#include <boost/mpl/at.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>

#include "prima/meta/base.hpp"

namespace prima
{
namespace meta
{
    template <typename Sequence, typename Location>
    using at_t = typename boost::mpl::at<Sequence, Location>::type;

    template <typename Sequence, unsigned Location>
    using at_ct = typename boost::mpl::at_c<Sequence, Location>::type;

    template <typename F, typename... A>
    using bind = typename F::template apply<A...>;

    template <typename Condition, typename IfTrue, typename IfFalse>
    using eval_if_t =
        typename boost::mpl::eval_if<Condition, IfTrue, IfFalse>::type;

    template <bool Condition, typename IfTrue, typename IfFalse>
    using eval_if_ct =
        typename boost::mpl::eval_if_c<Condition, IfTrue, IfFalse>::type;

    template <typename Sequence, typename Initial, typename Operation>
    using fold_t =
        typename boost::mpl::fold<Sequence, Initial, Operation>::type;

    template <typename Condition, typename IfTrue, typename IfFalse>
    using if_t = typename boost::mpl::if_<Condition, IfTrue, IfFalse>::type;

    template <typename F, typename... A>
    using invoke = typename F::template apply<A...>::type;

    template <typename Condition>
    using is_void = boost::mpl::is_void_<Condition>;

    template <typename F, typename... A> struct lazy
    {
        using type = invoke<F, typename A::type...>;
    };

    template <typename Sequence>
    using length_t = typename boost::mpl::size<Sequence>::type;

    struct or_func
    {
        template <typename...> struct apply : meta::false_
        {
        };

        template <typename Test, typename... Tests>
        struct apply<Test, Tests...>
            : eval_if_t<Test, meta::true_, bind<or_func, Tests...>>
        {
        };
    };

    template <typename... Tests> using or_ = bind<or_func, Tests...>;

    struct push_back_func
    {
        template <typename Sequence, typename Value> struct apply
        {
            using type = typename boost::mpl::push_back<Sequence, Value>::type;
        };
    };
} // meta
} // prima

#endif // PRIMA_META_FUNCS_HPP
