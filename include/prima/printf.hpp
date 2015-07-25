#ifndef PRIMA_PRINTF_HPP
#define PRIMA_PRINTF_HPP

#include <iostream>
#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/fprintf.hpp"

namespace prima
{
//! template <typename Format,
//!           typename Backend = backend::karma,
//!           typename... Args>
//! bool sprintf(Iterator&& out, Args&&... args)
//!
//! Outputs `Format` with `args` to `std::cout` using `Backend`.
//!
//! \requires `Format` is a valid prima format string.
//!
//! \throws Unspecified if `Backend::generate` throws.
//! \throws Unspecified if `std::cout` is configured to throw on errors.
//!
//! \returns `std::cout.good()`.
template <typename Format, typename Backend = backend::karma, typename... Args>
bool printf(Args&&... args)
{
    return fprintf<Format, Backend>(std::cout, std::forward<Args>(args)...);
}
} // prima

#endif // PRIMA_PRINTF_HPP
