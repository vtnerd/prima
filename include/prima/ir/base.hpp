#ifndef PRIMA_IR_BASE_HPP
#define PRIMA_IR_BASE_HPP

#include "prima/meta/base.hpp"
#include "prima/meta/funcs.hpp"

namespace prima
{
namespace ir
{
    ////////////////////////////////////////////////////////////////////////////
    // Basic IR Elements                                                      //
    ////////////////////////////////////////////////////////////////////////////
    template <char... Values> using literal = meta::string<Values...>;

    template <typename Left, typename Right> struct sequence
    {
        using type = sequence;
        using left = Left;
        using right = Right;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Basic IR Functions                                                     //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Fields, typename Field>
    using get_field_t = meta::at_t<Fields, Field>;

    template <typename Fields, typename Field>
    constexpr auto get_field_value() noexcept
    {
        return get_field_t<Fields, Field>::value;
    }

    namespace detail
    {
        constexpr bool has_field(...) noexcept
        {
            return false;
        }

        struct has_field_impl
        {
            template <typename Type, typename Field>
            constexpr bool
            operator()(const Type& type, const Field& field) const noexcept
            {
                return has_field(type, field);
            }
        };
    }

    PRIMA_DETAIL_CONSTEXPR_ADDRESS(has_field, detail::has_field_impl);

    template <template <unsigned> class Field> struct is_field_func
    {
        template <typename> struct apply : meta::false_
        {
        };

        template <unsigned N> struct apply<Field<N>> : meta::true_
        {
        };
    };

    template <typename Test, template <unsigned> class Field>
    using is_field = meta::bind<is_field_func<Field>, Test>;

    template <typename Test, template <unsigned> class... Fields>
    using is_any_field = meta::or_<is_field<Test, Fields>...>;
} // ir
} // prima

#endif // PRIMA_IR_BASE_HPP
