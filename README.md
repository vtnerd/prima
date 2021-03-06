# prima #
Prima is an implementation of the C I/O functions that parses the format string at compile time using [boost::metaparse](https://github.com/boostorg/metaparse), and then generates input/output formatting code at _compile time_ instead of runtime. This results in [faster](#performance-benchmarks) and safer (type-checked) I/O. Prima supports multiple [backends](#backends) that do the actual I/O, making Prima a flexible C format string compiler.

> This library is a work in-progress.

## Dependencies ##
Prima currently requires Boost 1.61.

## Supported Formatting ##
#### Input ####
Not yet-implemented. Will support `boost::spirit::qi` and default to `boost::spirit::x3`.

#### Output ####
Prima output I/O matches the behavior of the standard C behavior. Some flags are compile-time errors if they have no effect or are conflicting (i.e. ' ' and '+' is a compile-time error). If a flag is _not_ supported for a type, it is a compile-time error if used.

   Format Flag   |                              Valid Argument Types                              | Supported Flags
:---------------:|--------------------------------------------------------------------------------|-----------------
       d, i      |         Any built-in signed integer type (char, short, int, etc.)              | Width, Precision, '-', '0', ' ', and '+'.
e, E, f, F, g, G |                               float, and double                                | Width, Precision, '-', '0', ' ', '+', and '#'
        u        | Any unsigned integer type (unsigned char, unsigned short, unsigned int, etc.)  | Width, Precision, '-', and '0'.
   o, x, X       |  Any unsigned integer type (unsigned char, unsigned short, unsigned int, etc.) | Width, Precision, '-', and '0'.
       s         |                           const char*, std::string                             | Width, Precision, and '-'
      
> * The length modifiers ('hh', 'll', etc.) are _not_ supported, because variadic templates are used instead of the type opaque C variadic arguments (so they are not needed).
> * Pointers can be output by converting to `std::uintptr_t` and using any of the format flags that support an unsigned integer type ("%p" is not needed).
> * A zero length width is a compile-time error.
> * The '0' flag with no specified width is a compile-time error.
> * The combination of flags '+' and ' ' is a compile-time error.
> * The combination of flags '0' and '-' is a compile-time error.
> * The combination of the '0' flag and usage of the precision field with an integer format flag (d, i, u, o, x, X) is a compile-time error.
      
## Usage ##
The prima I/O functions require a variadic compile-time string as input. A macro `PRIMA_FMT` can convert a string literal to the compile-time string in a C++11 compatible compiler. The user-literal `prima::literals::_fmt` can be used in compilers that support [literal operator templates for strings](http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2013/n3599.html):

```c++
{
    prima::printf(PRIMA_FMT("%s"), "world");
}
{
    using prima::literals;
    prima::printf("hello %s"_fmt, "world");
}
```
The user string literal `_fmt` is the preferred method, because it will have more efficient _compile_-times.

#### Output ####
##### printf #####
Behaves just like `std::printf`:

```c++
prima::printf(PRIMA_FMT("hello %s"), "world");
```

##### sprintf #####
`prima::sprintf` differs slightly from `std::sprintf`; the first argument is templated and must meet [output iterator](http://en.cppreference.com/w/cpp/concept/OutputIterator) requirements, and the output is _never_ null-terminated. Since `char*` is a valid output iterator, `prima::sprintf` can be used in place of std::sprintf or other scenarios:

```c++
{
    char buffer[100] = {0};
    // Never checks for buffer size. Does not null-terminate.
    prima::sprintf(std::begin(buffer), PRIMA_FMT("hello %s"), "world");
}
{
    std::string buffer{};
    // Throws if std::bad_alloc. Implicitly null-terminated due to std::string.
    prima::sprintf(std::back_inserter(buffer), PRIMA_FMT("hello %s"), "world");
}
```
`prima::sprintf` will also update the output iterator to one-past the last write location, iff the argument is passed as a mutable l-value.

##### snprintf #####
`prima::snprintf` differs slightly from `std::snprintf`; the first argument is templated and must meet [output iterator](http://en.cppreference.com/w/cpp/concept/OutputIterator) requirements, and the function does not stop until `size` bytes have been output. Since `char*` is a valid output iterator, `prima::sprintf` can be used in place of std::sprintf or other scenarios:

```c++
{
    char buffer[100] = {0};
    // Does not null-terminate. Stops after sizeof(buffer) bytes (not sizeof(buffer) - 1).
    prima::snprintf(std::begin(buffer), PRIMA_FMT("hello %s"), sizeof(buffer), "world");
}
{
    std::string buffer{};
    buffer.resize(100);
    // Implicitly null-terminated due to std::string. Stops after buffer.size() bytes.
    prima::snprintf(&buffer[0], PRIMA_FMT("hello %s"), buffer.size(), "world");
}
```
`prima::snprintf` will also update the output iterator to one-past the last write location, iff the argument is passed as a mutable l-value.

## Backends ##
#### Input ####
Not yet-implemented. Will support `boost::spirit::qi` and default to `boost::spirit::x3`.

#### Output ####
##### Karma #####
`boost::spirit::karma` is the only backend for output, so it is the current default. Explicit usage example:

```c++
using prima::literals;
prima::printf.call<prima::backend::karma>()("hello %s"_fmt, "world");
```

## Performance Benchmarks ##
#### OSX (libc++) - Clang 3.5 - Intel i5-3210M (2.5 GHz 3MB Cache) ####
```
Running "%f" with input -100.000000 benchmark 1000000 times for each implementation...
        std::sprintf :0.231175 microseconds per run {checksum: 3dfd240}
       std::snprintf :0.230521 microseconds per run {checksum: 3dfd240}
      prima::sprintf :0.082181 microseconds per run {checksum: 3dfd240}
     prima::snprintf :0.080238 microseconds per run {checksum: 3dfd240}
Running "%f" with input 0.000000 benchmark 1000000 times for each implementation...
        std::sprintf :0.174141 microseconds per run {checksum: 40d9900}
       std::snprintf :0.171285 microseconds per run {checksum: 40d9900}
      prima::sprintf :0.062569 microseconds per run {checksum: 40d9900}
     prima::snprintf :0.068810 microseconds per run {checksum: 40d9900}
Running "%f" with input 100.000000 benchmark 1000000 times for each implementation...
        std::sprintf :0.227993 microseconds per run {checksum: 41cdb40}
       std::snprintf :0.226350 microseconds per run {checksum: 41cdb40}
      prima::sprintf :0.072780 microseconds per run {checksum: 41cdb40}
     prima::snprintf :0.072128 microseconds per run {checksum: 41cdb40}
Running "%f" with input 1234.123413 benchmark 1000000 times for each implementation...
        std::sprintf :0.257176 microseconds per run {checksum: 41cdb40}
       std::snprintf :0.256577 microseconds per run {checksum: 41cdb40}
      prima::sprintf :0.096077 microseconds per run {checksum: 41cdb40}
     prima::snprintf :0.095936 microseconds per run {checksum: 41cdb40}

Benchmark averages:
        std::sprintf :0.222621 microseconds per run {checksum: 102721c0}
       std::snprintf :0.221183 microseconds per run {checksum: 102721c0}
      prima::sprintf :0.078402 microseconds per run {checksum: 102721c0}
     prima::snprintf :0.079278 microseconds per run {checksum: 102721c0}
```
> **Note:** This is from latest master branch, but not C++11 branch
