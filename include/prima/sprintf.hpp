#ifndef PRIMA_SPRINTF_HPP
#define PRIMA_SPRINTF_HPP

#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/frontend/sprintf.hpp"

namespace prima
{
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
