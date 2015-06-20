#include <limits>
#include <utility>

#include <boost/detail/lightweight_test.hpp>

#include "prima/meta/base.hpp"
#include "prima/meta/funcs.hpp"

using namespace prima;

void or_tests()
{
    BOOST_TEST(!meta::or_<>::value);
    BOOST_TEST((!meta::or_<meta::false_, meta::false_, meta::false_>::value));
    BOOST_TEST((meta::or_<meta::false_, meta::false_, meta::true_>::value));
    BOOST_TEST((meta::or_<meta::true_, meta::false_, meta::true_>::value));    
}

int main()
{
    or_tests();
    return boost::report_errors();
}
