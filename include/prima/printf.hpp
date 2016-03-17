#ifndef PRIMA_PRINTF_HPP
#define PRIMA_PRINTF_HPP

#include <iostream>
#include <utility>

#include "prima/base.hpp"
#include "prima/detail/constexpr_address.hpp"
#include "prima/detail/output_func.hpp"
#include "prima/detail/returns.hpp"
#include "prima/fprintf.hpp"
#include "prima/meta/base.hpp"

namespace prima
{
namespace detail
{
    template <typename Backend> struct printf
    {
        template <char... Format, typename... Args>
        auto
        operator()(meta::string<Format...> const& format, Args&&... args) const
            PRIMA_DETAIL_RETURNS(prima::fprintf.call<Backend>()(
                std::cout, format, std::forward<Args>(args)...))
    };
}

//! template <char... Format, typename... Args>
//! bool printf(meta::string<Format...> const& format, Args&&... args)
//!
//! Outputs `format` with `args` to `std::cout` using `Backend`.
//!
//! \requires `Format...` is a valid prima output format string.
//!
//! \throws Unspecified if `Backend::generate` throws.
//! \throws Unspecified if `std::cout` is configured to throw on errors.
//!
//! \returns `std::cout.good()`.
PRIMA_DETAIL_CONSTEXPR_ADDRESS(printf, detail::output_func<detail::printf>);
} // prima

#endif // PRIMA_PRINTF_HPP
