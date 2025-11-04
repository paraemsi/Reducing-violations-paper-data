#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <limits>

namespace all_your_base {

using base_int_t = std::int32_t;   // width-controlled alias to fixed-width type (MISRA-compliant)

/**
 * @brief Convert digits from one base to another.
 *
 * @param from_base  The base of the input digits (>= 2).
 * @param in_digits  Most-significant digit first representation in the source base.
 * @param to_base    The target base (>= 2).
 * @return           Digits representing the same numeric value in the target base.
 *
 * @throws std::invalid_argument If the bases are less than 2, the digit list is
 *                               empty, or any digit is not strictly less than
 *                               from_base.
 */
auto convert(base_int_t from_base,
             const std::vector<base_int_t>& in_digits,
             base_int_t to_base) -> std::vector<base_int_t>;

/* --------------------------------------------------------------------------
 *  Generic unsigned-vector overload – used by the Exercism test-suite.
 *  Keeps internal arithmetic in fixed-width types while allowing the API
 *  to accept std::vector<unsigned int> without violating the MISRA rule
 *  (no direct use of the raw type in the declaration).
 * ------------------------------------------------------------------------*/
template <typename Unsigned,
          typename = std::enable_if_t<std::is_unsigned_v<Unsigned>>>
auto convert(base_int_t from_base,
             const std::vector<Unsigned>& in_digits,
             base_int_t to_base) -> std::vector<Unsigned>
{
    if ((from_base < static_cast<base_int_t>(2)) ||
        (to_base   < static_cast<base_int_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (in_digits.empty()) {
        throw std::invalid_argument("Input digit list is empty");
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);

    for (const Unsigned digit : in_digits) {
        if (digit >= static_cast<Unsigned>(from_base)) {
            throw std::invalid_argument("Digit not valid for given base");
        }
        value = ((value * static_cast<std::uint64_t>(from_base)) +
                 static_cast<std::uint64_t>(digit));
    }

    if (value == static_cast<std::uint64_t>(0U)) {
        return std::vector<Unsigned>{static_cast<Unsigned>(0U)};
    }

    std::vector<Unsigned> out_digits;

    while (value > static_cast<std::uint64_t>(0U)) {
        const Unsigned remainder =
            static_cast<Unsigned>(value % static_cast<std::uint64_t>(to_base));
        out_digits.push_back(remainder);
        value /= static_cast<std::uint64_t>(to_base);
    }

    std::reverse(out_digits.begin(), out_digits.end());
    return out_digits;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
