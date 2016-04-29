#ifndef PRIMA_BASE_HPP
#define PRIMA_BASE_HPP

#ifdef PRIMA_LIMIT_FMT_SIZE
  #define BOOST_METAPARSE_LIMIT_STRING_SIZE PRIMA_LIMIT_FMT_SIZE
#endif

#include <boost/metaparse/config.hpp>

#ifndef BOOST_METAPARSE_CONFIG_NO_MPLLIBS_STRING
  #include <boost/metaparse/string.hpp>
  #define PRIMA_FMT(s) BOOST_METAPARSE_STRING((s)){}
#endif

#endif // PRIMA_BASE_HPP
