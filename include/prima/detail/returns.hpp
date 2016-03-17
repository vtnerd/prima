#ifndef PRIMA_DETAIL_RETURNS_HPP
#define PRIMA_DETAIL_RETURNS_HPP

#define PRIMA_DETAIL_RETURNS(...)                                              \
    ->decltype(__VA_ARGS__)                                                    \
    {                                                                          \
        return (__VA_ARGS__);                                                  \
    }

#endif // PRIMA_DETAIL_RETURNS_HPP
