#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace all_your_base {

/*  Convert a sequence of digits expressed in `from_base`
    to the corresponding sequence of digits expressed in `to_base`.
    Throws std::invalid_argument for:
      • bases < 2
      • empty input
      • any digit that is not strictly less than `from_base`
*/
auto convert(const std::vector<std::uint32_t>& input_digits,
             std::uint32_t                         from_base,
             std::uint32_t                         to_base) -> std::vector<std::uint32_t>;

/*  Generic wrapper enabling calls with any integral digit type
    (e.g., int) while keeping the core implementation strictly
    on fixed-width unsigned integers. */
template <typename T,
          typename = std::enable_if_t<
              std::is_integral<T>::value
              && !std::is_same<T, char>::value
              && !std::is_same<T, signed char>::value
              && !std::is_same<T, unsigned char>::value
              && !std::is_same<T, wchar_t>::value
              && !std::is_same<T, char16_t>::value
              && !std::is_same<T, char32_t>::value>>
inline auto convert(const std::vector<T>& input_digits,
                    std::uint32_t            from_base,
                    std::uint32_t            to_base) -> std::vector<std::uint32_t>
{
    std::vector<std::uint32_t> promoted_digits {};
    promoted_digits.reserve(input_digits.size());

    for(const T d : input_digits) {
        if(d < static_cast<T>(0)) {
            throw std::invalid_argument("Digit cannot be negative");
        }
        /*  Explicit cast justified: value verified non-negative and
            std::uint32_t is wide enough to hold it. */
        promoted_digits.push_back(static_cast<std::uint32_t>(d));
    }

    return all_your_base::convert(promoted_digits, from_base, to_base);
}

/* ------------------------------------------------------------------ */
/*  Alternative overloads that match the parameter order used by the  */
/*  Exercism test-suite:                                              */
/*        convert(from_base, input_digits, to_base)                   */
/* ------------------------------------------------------------------ */

/*  Primary fixed-width overload */
inline auto convert(std::uint32_t                         from_base,
                    const std::vector<std::uint32_t>&     input_digits,
                    std::uint32_t                         to_base) -> std::vector<std::uint32_t>
{
    return all_your_base::convert(input_digits, from_base, to_base);
}

/*  Templated overload mirroring the generic wrapper for arbitrary
    integral digit types, but with the parameter order expected by the
    tests. */
template <typename T,
          typename = std::enable_if_t<
              std::is_integral<T>::value
              && !std::is_same<T, char>::value
              && !std::is_same<T, signed char>::value
              && !std::is_same<T, unsigned char>::value
              && !std::is_same<T, wchar_t>::value
              && !std::is_same<T, char16_t>::value
              && !std::is_same<T, char32_t>::value>>
inline auto convert(std::uint32_t              from_base,
                    const std::vector<T>&      input_digits,
                    std::uint32_t              to_base) -> std::vector<std::uint32_t>
{
    return all_your_base::convert(input_digits, from_base, to_base);
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
