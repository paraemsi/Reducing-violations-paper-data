#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t {
    perfect,
    abundant,
    deficient
};

using number_t = std::uint32_t;

/*
 *  Determine whether the supplied positive integer `n` is
 *  perfect, abundant, or deficient according to Nicomachus.
 *
 *  Throws:
 *      std::domain_error if n <= 0 (classification undefined)
 */
auto classify(std::int64_t n) -> classification;

/*  Convenience overload so that passing a plain `int`
 *  (the usual type of an integer literal such as -1) does
 *  not rely on an implicit integral conversion.  This keeps
 *  the call-site compliant with the “argument and parameter
 *  types shall match” MISRA rule by providing an exact-type
 *  match.
 */
inline auto classify(std::int32_t n) -> classification
{
    return classify(static_cast<std::int64_t>(n));
}

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
