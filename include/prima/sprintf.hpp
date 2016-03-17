#ifndef PRIMA_SPRINTF_HPP
#define PRIMA_SPRINTF_HPP

#include <utility>

#include "prima/backend/karma.hpp" // hack include
#include "prima/base.hpp"
#include "prima/detail/constexpr_address.hpp"
#include "prima/detail/output_func.hpp"
#include "prima/detail/output_limit_iterator.hpp"
#include "prima/detail/returns.hpp"
#include "prima/frontend/sprintf.hpp"
#include "prima/meta.hpp"

namespace prima
{
namespace detail
{
    template <typename Backend> struct sprintf
    {
        template <typename Iterator, char... Format, typename... Args>
        auto operator()(Iterator&& out,
                        meta::string<Format...> const&,
                        Args&&... args) const
            PRIMA_DETAIL_RETURNS(
                Backend::template generate<
                    frontend::parse_sprintf_t<meta::string<Format...>>>(
                    std::forward<Iterator>(out), std::forward<Args>(args)...))
    };
}

//! template <typename Backend = backend::karma,
//!           typename Iterator,
//!           char... Format,
//!           typename... Args>
//! void sprintf(Iterator&& out,
//!              meta::string<Format...> const& format,
//!              Args&&... args)
//!
//! Outputs `format` with `args` to `out` using `Backend`. If `out` is a mutable
//! l-value, the iterator will be moved to one-past the last character output on
//! valid return (undefined position if exception is thrown). No
//! NULL-termination character is appended.
//!
//! \requires `Format...` is a valid prima output format string.
//! \requires `Iterator` meets the requirements of the OutputIterator concept.
//!
//! \throws Unspecified iff `Backend::generate(...)` throws.
PRIMA_DETAIL_CONSTEXPR_ADDRESS(sprintf, detail::output_func<detail::sprintf>);


namespace detail
{

    template <typename Backend> struct snprintf
    {
        template <typename Iterator, char... Format, typename... Args>
        std::size_t operator()(Iterator&& out,
                               meta::string<Format...> const& format,
                               const std::size_t max,
                               Args&&... args) const
        {
            using real_iterator =
                meta::if_t<meta::or_<meta::is_rvalue_reference<Iterator&&>,
                                     meta::is_const<meta::decay_t<Iterator>>>,
                           meta::remove_const_t<meta::decay_t<Iterator>>,
                           Iterator>;
            detail::output_limit_iterator<real_iterator> real_out{
                max, std::forward<Iterator>(out)};
            prima::sprintf.call<Backend>()(real_out,
                                           format,
                                           std::forward<Args>(args)...);
            return real_out.characters_output();
        }
    };
} // detail

//! template<typename Backend = backend::karma,
//!          typename Iterator,
//!          typename Format,
//!          typename... Args>
//! std::size_t snprintf(Iterator&& out,
//!                      meta::string<Format...> const& format,
//!                      std::size_t max,
//!                      Args&&... args)
//!
//! Outputs `format` with `args` to `out` using `Backend`, but stopping if `max`
//! characters have been output. If `out` is a mutbale l-value, the iterator
//! will be moved to one-past the last character output on valid return
//! (undefined position if exception is thrown). No NULL-termination character
//! is appended.
//!
//! \requires `Format...` is a valid prima output format string.
//! \requires `Iterator` meets the requirements of the OutputIterator concept.
//!
//! \throws Unspecified iff `Backend::generate(...)` throws.
//!
//! \returns The number of characters output. If the value exceeds `max`, it
//!     indicates how many characters are needed for output.
PRIMA_DETAIL_CONSTEXPR_ADDRESS(snprintf, detail::output_func<detail::snprintf>);
} // prima

#endif // PRIMA_SPRINTF_HPP
