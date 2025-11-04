#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace all_your_base {

namespace detail {

/* Core implementation shared by both overloads.
 * DigitT must be an unsigned integral type; BaseT must be integral.
 */
template <typename DigitT, typename BaseT>
inline std::vector<DigitT> convert_impl(const std::vector<DigitT>& digits, BaseT in_base, BaseT out_base)
{
    static_assert(std::is_integral<DigitT>::value && std::is_unsigned<DigitT>::value, "DigitT must be an unsigned integral type");
    static_assert(std::is_integral<BaseT>::value, "BaseT must be an integral type");

    if ((in_base < static_cast<BaseT>(2)) || (out_base < static_cast<BaseT>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty()) {
        return std::vector<DigitT>{};
    }

    bool all_zero = true;
    for (std::size_t i = static_cast<std::size_t>(0U); i < digits.size(); ++i) {
        const DigitT d = digits[i];

        if ((static_cast<std::uint64_t>(d)) >= (static_cast<std::uint64_t>(in_base))) {
            throw std::invalid_argument("Digit out of range for input base");
        }

        if (d != static_cast<DigitT>(0)) {
            all_zero = false;
        } else {
            // no action
        }
    }

    if (all_zero) {
        return std::vector<DigitT>{ static_cast<DigitT>(0) };
    }

    std::vector<DigitT> src = digits;
    std::vector<DigitT> result;
    result.reserve(digits.size());

    while (!src.empty()) {
        std::vector<DigitT> quotient;
        quotient.reserve(src.size());

        bool started = false;
        std::uint64_t remainder = static_cast<std::uint64_t>(0);

        for (std::size_t i = static_cast<std::size_t>(0U); i < src.size(); ++i) {
            const DigitT di = src[i];
            const std::uint64_t acc =
                (remainder * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(di);

            const DigitT qdigit = static_cast<DigitT>(acc / static_cast<std::uint64_t>(out_base));
            remainder = (acc % static_cast<std::uint64_t>(out_base));

            if ((qdigit != static_cast<DigitT>(0)) || (started)) {
                quotient.push_back(qdigit);
                started = true;
            } else {
                // skip leading zero in quotient
            }
        }

        result.push_back(static_cast<DigitT>(remainder));
        src.swap(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace detail

// Overload 1: digits first (common variant)
template <typename DigitT, typename BaseT>
inline std::vector<DigitT> convert(const std::vector<DigitT>& digits, BaseT in_base, BaseT out_base)
{
    return detail::convert_impl<DigitT, BaseT>(digits, in_base, out_base);
}

// Overload 2: base first (alternative variant used by some test suites)
template <typename DigitT, typename BaseT>
inline std::vector<DigitT> convert(BaseT in_base, const std::vector<DigitT>& digits, BaseT out_base)
{
    return detail::convert_impl<DigitT, BaseT>(digits, in_base, out_base);
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
