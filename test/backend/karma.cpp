#include <boost/detail/lightweight_test.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/version.hpp>

#define PRIMA_TEST_BOOST_MAJOR (BOOST_VERSION / 100000)
#define PRIMA_TEST_BOOST_MINOR ((BOOST_VERSION / 100) % 1000)

#if PRIMA_TEST_BOOST_MAJOR == 1 && PRIMA_TEST_BOOST_MINOR < 59
  #define PRIMA_TEST_LEFT_ALIGN_BUG
#endif

#define PRIMA_TEST_BENCH_FILE BOOST_PP_STRINGIZE(PRIMA_TEST_BENCH.hpp)
#define PRIMA_TEST_BENCH_FUNCTION BOOST_PP_CAT(PRIMA_TEST_BENCH, _tests)

#include PRIMA_TEST_BENCH_FILE
#include "prima/backend/karma.hpp"

int main()
{
    prima::backend::test::PRIMA_TEST_BENCH_FUNCTION<prima::backend::karma>();
    return boost::report_errors();
}
