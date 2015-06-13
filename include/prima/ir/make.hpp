#ifndef PRIMA_IR_MAKE_HPP
#define PRIMA_IR_MAKE_HPP

#include "prima/ir/base.hpp"

namespace prima
{
namespace ir
{
    namespace make
    {
        struct sequence_func
        {
            template <typename Left, typename Right> struct apply
            {
                using type = sequence<Left, Right>;
            };
        };
    }
}
}

#endif // PRIMA_IR_MAKE_HPP
