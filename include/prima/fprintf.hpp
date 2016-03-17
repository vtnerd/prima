#ifndef PRIMA_FPRINTF_HPP
#define PRIMA_FPRINTF_HPP

#include <iterator>
#include <ostream>
#include <utility>

#include "prima/base.hpp"
#include "prima/detail/constexpr_address.hpp"
#include "prima/detail/output_func.hpp"
#include "prima/detail/returns.hpp"
#include "prima/meta/base.hpp"
#include "prima/sprintf.hpp"

namespace prima
{
namespace detail
{
    template <typename Backend> struct fprintf
    {
        template <typename CharT,
                  typename Traits,
                  char... Format,
                  typename... Args>
        auto operator()(std::basic_ostream<CharT, Traits>& out,
                        meta::string<Format...> const& format,
                        Args&&... args) const
            PRIMA_DETAIL_RETURNS(prima::sprintf.call<Backend>()(
                                     std::ostreambuf_iterator<CharT, Traits>{
                                         out},
                                     format,
                                     std::forward<Args>(args)...),
                                 out.good())
    };
} // detail

//! template <typename CharT,
//!           typename Traits,
//!           char... Format,
//!           typename... Args>
//! bool fprintf(std::back_ostream<CharT, Traits>& out, Args&&... args)
//!
//! Outputs `format` with `args` to `out` using `Backend`. No NULL-termination
//! character is appended.
//!
//! \requires `Format...` is a valid prima output format string.
//!
//! \throws Unspecified if `Backend::generate(...)` throws.
//! \throws Unspecified if `out` is configured to throw on errors.
//!
//! \returns `out.good()`.
PRIMA_DETAIL_CONSTEXPR_ADDRESS(fprintf, detail::output_func<detail::fprintf>);
} // prima

#endif // PRIMA_FPRINTF_HPP
