#ifndef PRIMA_META_BASE_HPP
#define PRIMA_META_BASE_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/char.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>

#include <mpllibs/metaparse/string.hpp>

namespace prima
{
namespace meta
{
    using boost::mpl::bool_;
    using boost::mpl::char_;
    using boost::mpl::false_;
    using boost::mpl::identity;
    using boost::mpl::is_void_;
    using mpllibs::metaparse::string;
    using boost::mpl::true_;

    template <unsigned Value>
    using unsigned_ = boost::mpl::integral_c<unsigned, Value>;

    using boost::mpl::vector;
    using boost::mpl::void_;
}
}

#endif // PRIMA_META_BASE_HPP
