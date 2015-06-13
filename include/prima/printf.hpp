#ifndef PRIMA_PRINTF_HPP
#define PRIMA_PRINTF_HPP

#include <iostream>
#include <iterator>
#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/sprintf.hpp"

namespace prima
{
template <typename Format, typename Backend = backend::karma, typename... Args>
bool printf(Args&&... args)
{
    return sprintf<Format, Backend>(std::ostream_iterator<char>(std::cout),
                                    std::forward<Args>(args)...);
}
} // prima

#endif // PRIMA_PRINTF_HPP
