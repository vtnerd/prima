#ifndef PRIMA_DETAIL_CONSTEXPR_ADDRESS_HPP
#define PRIMA_DETAIL_CONSTEXPR_ADDRESS_HPP

namespace prima
{
namespace detail
{
    template <typename T> struct static_const
    {
        constexpr const static T value = T{};
    };

    template <typename T> constexpr const T static_const<T>::value;

#define PRIMA_DETAIL_CONSTEXPR_ADDRESS(name, class_)                           \
    constexpr const auto& name = ::prima::detail::static_const<class_>::value
}
}

#endif // PRIMA_DETAIL_CONSTEXPR_ADDRESS_HPP
