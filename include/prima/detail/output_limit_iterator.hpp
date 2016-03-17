#ifndef PRIMA_DETAIL_OUTPUT_LIMIT_ITERATOR_HPP
#define PRIMA_DETAIL_OUTPUT_LIMIT_ITERATOR_HPP

#include <cstdint>
#include <iterator>
#include <limits>
#include <utility>

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
} // prima

#endif // PRIMA_DETAIL_OUTPUT_LIMIT_ITERATOR_HPP
