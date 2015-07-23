#ifndef PRIMA_SPRINTF_HPP
#define PRIMA_SPRINTF_HPP

#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/frontend/sprintf.hpp"

namespace prima
{
//! template <typename Format,
//!           typename Backend = backend::karma,
//!           typename Iterator,
//!           typename... Args>
//! bool sprintf(Iterator&& out, Args&&... args)
//!
//! Outputs `Format` with `args` to `out` using `Backend`.
//!
//! \requires `Format` is a valid prima format string.
//! \requires `Iterator` meets the requirements of the OutputIterator concept.
//!
//! \throws Iff `Backend::generate` throws.
//!
//! \return Result of `Backend::generate`.
template <typename Format,
          typename Backend = backend::karma,
          typename Iterator,
          typename... Args>
bool sprintf(Iterator&& out, Args&&... args)
{
    return Backend::template generate<frontend::parse_sprintf_t<Format>>(
        std::forward<Iterator>(out), std::forward<Args>(args)...);
}
}

#endif // PRIMA_SPRINTF_HPP
