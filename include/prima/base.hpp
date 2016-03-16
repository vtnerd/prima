#ifndef PRIMA_BASE_HPP
#define PRIMA_BASE_HPP

#ifdef PRIMA_LIMIT_FMT_SIZE
  #define MPLLIBS_LIMIT_STRING_SIZE PRIMA_LIMIT_FMT_SIZE
#endif

#include <mpllibs/metaparse/config.hpp>

#ifndef MPLLIBS_CONFIG_NO_MPLLIBS_STRING
  #include <mpllibs/metaparse/string.hpp>
  #define PRIMA_FMT(s) MPLLIBS_STRING((s))
#endif

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
    constexpr const auto& name = ::prima::detail::static_const<class_>::value;
} // detail
} // prima

#endif // PRIMA_BASE_HPP
