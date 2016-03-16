#ifndef PRIMA_FPRINTF_HPP
#define PRIMA_FPRINTF_HPP

#include <iterator>
#include <ostream>
#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/sprintf.hpp"

namespace prima
{
//! template <typename Backend = backend::karma,
//!           typename CharT,
//!           typename Traits,
//!           char... Format,
//!           typename... Args>
//! bool fprintf(std::back_ostream<CharT, Traits>& out, Args&&... args)
//!
//! Outputs `format` with `args` to `out` using `Backend`. No NULL-termination
//! character is appended.
//!
//! \requires `Format` is a valid prima output format string.
//!
//! \throws Unspecified if `Backend::generate(...)` throws.
//! \throws Unspecified if `out` is configured to throw on errors.
//!
//! \returns `out.good()`.
template <typename Backend = backend::karma,
          typename CharT,
          typename Traits,
          char... Format,
          typename... Args>
bool fprintf(std::basic_ostream<CharT, Traits>& out, meta::string<Format...> const& format, Args&&... args)
{
  prima::sprintf<Backend>(std::ostreambuf_iterator<CharT, Traits>{out},
                          format,
                          std::forward<Args>(args)...);
    return out.good();
}
}

#endif // PRIMA_FPRINTF_HPP
