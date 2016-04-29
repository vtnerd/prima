#ifndef PRIMA_IR_MANIP_HPP
#define PRIMA_IR_MANIP_HPP

#include "prima/ir/base.hpp"
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
            constexpr const static unsigned field_loc = 0;
            constexpr const static unsigned value_loc = 1;

            template <typename IR, typename Field, typename Value = void>
            struct apply
            {
            private:
                static_assert(ir::has_field(IR{}, Field{}),
                              "invalid field for IR element");

                using fields = typename IR::fields;

                constexpr const static unsigned holder_size =
                    meta::length_t<fields>::value;
                static_assert(Field::value < holder_size,
                              "invalid field number");

                template <typename, typename, typename> struct update;

                template <template <typename> class Type,
                          template <typename...> class Sequence,
                          typename... Replaced,
                          unsigned... Head,
                          unsigned... Tail>
                struct update<Type<Sequence<Replaced...>>,
                              meta::index_sequence<Head...>,
                              meta::index_sequence<Tail...>>
                {
                    using type = Type<Sequence<
                        meta::at_ct<fields, Head>...,
                        Value,
                        meta::at_ct<fields, Field::value + 1 + Tail>...>>;
                };

            public:
                using type =
                    typename update<IR,
                                    meta::make_index_sequence_t<Field::value>,
                                    meta::make_index_sequence_t<
                                        holder_size - Field::value - 1>>::type;
            };

            template <typename IR,
                      template <typename, typename, typename...> class Flag,
                      typename Field,
                      typename Value,
                      typename... Ignored>
            struct apply<IR, Flag<Field, Value, Ignored...>>
                : apply<IR, Field, Value>
            {
            };
        };

        template <typename Fields, typename Field, typename Value>
        using update_field =
            meta::bind<update_field_func, Fields, Field, Value>;

        template <typename Fields, typename Field, typename Value>
        using update_field_t =
            meta::invoke<update_field_func, Fields, Field, Value>;
    } // manip
} // ir
} // prima

#endif // PRIMA_IR_MANIP_HPP
