#ifndef PRIMA_IR_BASE_HPP
#define PRIMA_IR_BASE_HPP

#include "prima/meta/base.hpp"
#include "prima/meta/funcs.hpp"

namespace prima
{
namespace ir
{
    template <char... Values> using literal = meta::string<Values...>;

    template <typename Left, typename Right> struct sequence
    {
        using type = sequence;
        using left = Left;
        using right = Right;
    };

    constexpr bool is_field(...)
    {
        return false;
    }

    template <typename> constexpr bool has_field(...)
    {
        return false;
    }

    template <typename Fields, typename Field>
    using get_field_t = meta::at_t<Fields, Field>;

    template <typename Fields, typename Field> constexpr auto get_field_value()
    {
        return get_field_t<Fields, Field>::value;
    }
} // ir
} // prima

#endif // PRIMA_IR_BASE_HPP
