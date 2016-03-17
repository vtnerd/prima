#ifndef PRIMA_BASE_HPP
#define PRIMA_BASE_HPP

#ifdef PRIMA_LIMIT_FMT_SIZE
  #define MPLLIBS_LIMIT_STRING_SIZE PRIMA_LIMIT_FMT_SIZE
#endif

#include <mpllibs/metaparse/config.hpp>

#ifndef MPLLIBS_CONFIG_NO_MPLLIBS_STRING
  #include <mpllibs/metaparse/string.hpp>
  #define PRIMA_FMT(s) MPLLIBS_STRING((s)){}
#endif

#endif // PRIMA_BASE_HPP
