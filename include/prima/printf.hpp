#ifndef PRIMA_PRINTF_HPP
#define PRIMA_PRINTF_HPP

#include <iostream>
#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/fprintf.hpp"

namespace prima
{
//! template <typename Backend = backend::karma,
//!           char... Format,
//!           typename... Args>
//! bool sprintf(Iterator&& out, Args&&... args)
//!
//! Outputs `format` with `args` to `std::cout` using `Backend`.
//!
//! \requires `Format` is a valid prima output format string.
//!
//! \throws Unspecified if `Backend::generate` throws.
//! \throws Unspecified if `std::cout` is configured to throw on errors.
//!
//! \returns `std::cout.good()`.
template <typename Backend = backend::karma, char... Format, typename... Args>
bool printf(meta::string<Format...> const& format, Args&&... args)
{
    return prima::fprintf<Backend>(std::cout,
                                   format,
                                   std::forward<Args>(args)...);
}
} // prima

#endif // PRIMA_PRINTF_HPP
