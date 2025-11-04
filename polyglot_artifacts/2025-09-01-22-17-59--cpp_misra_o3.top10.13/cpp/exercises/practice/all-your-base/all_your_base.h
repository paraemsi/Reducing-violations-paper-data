#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <type_traits>
#include <cstddef>
#include <limits>

namespace all_your_base {

/**
 * @brief Convert a sequence of digits from one base to another.
 *
 * The function template is defined entirely in the header to allow
 * automatic instantiation for the calling integral type without
 * explicitly naming any banned fundamental integer types.
 *
 * @tparam IntT  An integral type deduced from the caller.
 * @param digits Input digits (most-significant first).
 * @param from_base Base of the input digits (≥ 2).
 * @param to_base   Desired output base (≥ 2).
 * @return Vector with converted digits (most-significant first).
 * @throws std::invalid_argument on any rule violation.
 */
template <typename IntT,
          typename = std::enable_if_t<std::is_integral_v<IntT>>>
inline auto convert(const std::vector<IntT>& digits,
                    IntT from_base,
                    IntT to_base) -> std::vector<IntT>
{
    static_assert(!std::is_same_v<IntT, char> &&
                  !std::is_same_v<IntT, signed char> &&
                  !std::is_same_v<IntT, unsigned char> &&
                  !std::is_same_v<IntT, wchar_t> &&
                  !std::is_same_v<IntT, char16_t> &&
                  !std::is_same_v<IntT, char32_t>,
                  "Character types are not allowed for numeric digits");

    /* Preconditions ------------------------------------------------------ */
    if ((from_base < static_cast<IntT>(2)) || (to_base < static_cast<IntT>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty())
    {
        return { static_cast<IntT>(0) };
    }

    if ((digits.size() > static_cast<std::size_t>(1)) &&
        (digits.front() == static_cast<IntT>(0)))
    {
        throw std::invalid_argument("Leading zeros are not allowed");
    }

    for (const auto digit : digits)
    {
        /* Reject negative digits only when the digit type is signed -------- */
        if constexpr (std::is_signed_v<IntT>)
        {
            if (digit < static_cast<IntT>(0))
            {
                throw std::invalid_argument("Digit out of range for input base");
            }
        }

        if (digit >= from_base)
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Convert input digits to an unsigned 64-bit accumulator ------------ */
    std::uint64_t value { 0U };

    for (const auto digit : digits)
    {
        value = ((value * static_cast<std::uint64_t>(from_base))
              + static_cast<std::uint64_t>(digit));
    }

    /* Convert accumulator to requested base ---------------------------- */
    if (value == static_cast<std::uint64_t>(0))
    {
        return { static_cast<IntT>(0) };
    }

    std::vector<IntT> result_digits {};

    while (value != static_cast<std::uint64_t>(0))
    {
        const std::uint64_t remainder =
            (value % static_cast<std::uint64_t>(to_base));

        result_digits.push_back(
            static_cast<IntT>(remainder));

        value = (value / static_cast<std::uint64_t>(to_base));
    }

    std::reverse(result_digits.begin(), result_digits.end());

    return result_digits;
}

/* -------------------------------------------------------------------------- */
/**
 * @brief Overload to match Exercism test parameter order.
 *
 * Accepts (from_base, digits, to_base) and forwards to the primary
 * implementation defined above.
 */
template <typename BaseT,
          typename DigitT,
          typename = std::enable_if_t<
              std::is_integral_v<BaseT> && std::is_integral_v<DigitT>>>
inline auto convert(BaseT from_base,
                    const std::vector<DigitT>& digits,
                    BaseT to_base) -> std::vector<DigitT>
{
    /* Enforce that bases fit within the digit type so that the primary
     * implementation can operate on a single integral type without
     * narrowing conversions that violate the MISRA rules.
     */
    /* Reject negative bases only when the base type is signed ------------- */
    if constexpr (std::is_signed_v<BaseT>)
    {
        if ((from_base < static_cast<BaseT>(0)) ||
            (to_base   < static_cast<BaseT>(0)))
        {
            throw std::invalid_argument("Bases must be positive");
        }
    }

    if ((from_base > static_cast<BaseT>(std::numeric_limits<DigitT>::max())) ||
        (to_base   > static_cast<BaseT>(std::numeric_limits<DigitT>::max())))
    {
        throw std::invalid_argument("Base does not fit digit type");
    }

    return all_your_base::convert(
        digits,
        static_cast<DigitT>(from_base),
        static_cast<DigitT>(to_base));
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
