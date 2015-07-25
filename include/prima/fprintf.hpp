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
//! template <typename Format,
//!           typename Backend = backend::karma,
//!           typename CharT,
//!           typename Traits,
//!           typename... Args>
//! bool sprintf(std::back_ostream<CharT, Traits>& out, Args&&... args)
//!
//! Outputs `Format` with `args` to `out` using `Backend`. No NULL-termination
//! character is appended.
//!
//! \requires `Format` is a valid prima format string.
//!
//! \throws Unspecified if `Backend::generate(...)` throws.
//! \throws Unspecified if `out` is configured to throw on errors.
//!
//! \returns `out.good()`.
template <typename Format,
          typename Backend = backend::karma,
          typename CharT,
          typename Traits,
          typename... Args>
bool fprintf(std::basic_ostream<CharT, Traits>& out, Args&&... args)
{
    sprintf<Format, Backend>(std::ostream_iterator<CharT, CharT, Traits>{out},
                             std::forward<Args>(args)...);
    return out.good();
}
}

#endif // PRIMA_FPRINTF_HPP
