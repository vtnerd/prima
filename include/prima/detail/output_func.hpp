#ifndef PRIMA_DETAIL_OUTPUT_FUNC_HPP
#define PRIMA_DETAIL_OUTPUT_FUNC_HPP

#include "prima/backend/fwd.hpp"

namespace prima
{
namespace detail
{
    template <template <typename> class Func>
    struct output_func : Func<::prima::backend::karma>
    {
        template <typename Backend> static Func<Backend> call()
        {
            return {};
        }
    };
}
}

#endif // PRIMA_DETAIL_OUTPUT_FUNC_HPP
