#ifndef PRIMA_SPRINTF_HPP
#define PRIMA_SPRINTF_HPP

#include <utility>

#include "prima/backend/karma.hpp"
#include "prima/base.hpp"
#include "prima/frontend/sprintf.hpp"
#include "prima/meta.hpp"

namespace prima
{
namespace detail
{
    template <typename OutputIterator>
    class output_limit_iterator
        : public std::iterator<std::output_iterator_tag, void, void, void, void>
    {
    public:
        explicit output_limit_iterator(std::size_t max_characters,
                                       OutputIterator output_iterator)
            : characters_(0)
            , max_characters_(max_characters)
            , output_iterator_(output_iterator)
        {
        }

        std::size_t characters_output() const
        {
            return characters_;
        }

        output_limit_iterator& operator*()
        {
            return *this;
        }

        template <typename Elem> output_limit_iterator& operator=(Elem&& elem)
        {
            if (!reached_limit())
            {
                *output_iterator_ = std::forward<Elem>(elem);
            }
            return *this;
        }

        output_limit_iterator& operator++()
        {
            advance();
            return *this;
        }

        output_limit_iterator operator++(int)
        {
            const output_limit_iterator original(this);
            advance();
            return original;
        }

    private:
        bool reached_limit() const
        {
            return characters_ >= max_characters_;
        }

        void advance()
        {
            if (characters_ < std::numeric_limits<std::size_t>::max())
            {
                if (!reached_limit())
                {
                    ++output_iterator_;
                }
                ++characters_;
            }
        }

        std::size_t characters_;
        std::size_t max_characters_;
        OutputIterator output_iterator_;
    };
} // detail

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
template <typename Backend = backend::karma,
          typename Iterator,
          char... Format,
          typename... Args>
void sprintf(Iterator&& out, meta::string<Format...> const&, Args&&... args)
{
    Backend::template generate<
        frontend::parse_sprintf_t<meta::string<Format...>>>(
        std::forward<Iterator>(out), std::forward<Args>(args)...);
}

//! template<typename Backend = backend::karma,
//!          typename Iterator,
//!          typename Format,
//!          typename... Args>
//! std::size_t snprintf(Iterator&& out, Format const& format, std::size_t max,
//Args&&... args)
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
template <typename Backend = backend::karma,
          typename Iterator,
          char... Format,
          typename... Args>
std::size_t snprintf(Iterator&& out,
                     meta::string<Format...> const& format,
                     const std::size_t max,
                     Args&&... args)
{
    using real_iterator =
        meta::if_t<meta::or_<meta::is_rvalue_reference<Iterator&&>,
                             meta::is_const<meta::decay_t<Iterator>>>,
                   meta::remove_const_t<meta::decay_t<Iterator>>,
                   Iterator>;
    detail::output_limit_iterator<real_iterator> real_out{
        max, std::forward<Iterator>(out)};
    prima::sprintf<Backend>(real_out, format, std::forward<Args>(args)...);
    return real_out.characters_output();
}
} // prima

#endif // PRIMA_SPRINTF_HPP
