#ifndef PRIMA_IR_MANIP_HPP
#define PRIMA_IR_MANIP_HPP

#include "prima/meta/base.hpp"
#include "prima/meta/funcs.hpp"

namespace prima
{
namespace ir
{
    namespace manip
    {
        class update_field_func
        {
        private:
            template <unsigned... Sequence> struct range_sequence
            {
                using type = range_sequence;
            };

            template <typename, unsigned, unsigned> struct expand;

            template <unsigned... Range, unsigned Start, unsigned End>
            struct expand<range_sequence<Range...>, Start, End>
            {
                static_assert(Start <= End, "bad range");
                constexpr const static unsigned current_size = sizeof...(Range);
                using type = meta::eval_if_ct<
                    current_size == End - Start,
                    range_sequence<Range...>,
                    expand<range_sequence<Range..., Start + current_size>,
                           Start,
                           End>>;
            };

            template <unsigned Start, unsigned End>
            using make_range_sequence =
                typename expand<range_sequence<>, Start, End>::type;

        public:
            template <typename Fields, typename Field, typename Value>
            class apply
            {
            private:
                using holder_size = meta::length_t<Fields>;
                static_assert(Field::value < holder_size::value,
                              "invalid field");

                template <typename, typename, typename> struct update;

                template <template <typename...> class Sequence,
                          typename... Replaced,
                          unsigned... Head,
                          unsigned... Tail>
                struct update<Sequence<Replaced...>,
                              range_sequence<Head...>,
                              range_sequence<Tail...>>
                {
                    using type = Sequence<meta::at_ct<Fields, Head>...,
                                          Value,
                                          meta::at_ct<Fields, Tail>...>;
                };

            public:
                using type = typename update<
                    Fields,
                    make_range_sequence<0, Field::value>,
                    make_range_sequence<Field::value + 1,
                                        holder_size::value>>::type;
            };
        };

        template <typename Fields, typename Field, typename Value>
        using update_field =
            meta::bind<update_field_func, Fields, Field, Value>;

        template <typename Fields, typename Field, typename Value>
        using update_field_t =
            meta::invoke<update_field_func, Fields, Field, Value>;

        struct update_fields_func
        {
            template <typename, typename> struct apply;

            template <template <typename...> class T,
                      typename Replaced,
                      typename... Rest,
                      typename Fields>
            struct apply<T<Replaced, Rest...>, Fields>
            {
                using type = T<Fields, Rest...>;
            };
        };

        template <typename Type, typename Fields>
        using update_fields_t = meta::invoke<update_fields_func, Type, Fields>;
    } // manip
} // ir
} // prima

#endif // PRIMA_IR_MANIP_HPP
