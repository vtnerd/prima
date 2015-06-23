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
        struct update_field_func
        {
            template <typename Fields, typename Field, typename Value>
            class apply
            {
            private:
                constexpr const static auto holder_size =
                    meta::length_t<Fields>::value;
                static_assert(Field::value < holder_size, "invalid field");

                template <typename, typename, typename> struct update;

                template <template <typename...> class Sequence,
                          typename... Replaced,
                          unsigned... Head,
                          unsigned... Tail>
                struct update<Sequence<Replaced...>,
                              meta::index_sequence<Head...>,
                              meta::index_sequence<Tail...>>
                {
                    using type = Sequence<
                        meta::at_ct<Fields, Head>...,
                        Value,
                        meta::at_ct<Fields, Field::value + 1 + Tail>...>;
                };

            public:
                using type =
                    typename update<Fields,
                                    meta::make_index_sequence_t<Field::value>,
                                    meta::make_index_sequence_t<
                                        holder_size - Field::value + 1>>::type;
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
