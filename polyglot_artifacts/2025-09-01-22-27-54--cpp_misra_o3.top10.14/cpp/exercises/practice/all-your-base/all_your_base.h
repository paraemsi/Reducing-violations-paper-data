#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

namespace all_your_base {

/**
 * \brief Convert a sequence of digits expressed in one base into a sequence
 *        of digits expressed in another base.
 *
 * \tparam IntT Unsigned integral type used to represent individual digits
 *              and bases.  The template enables the exercism tests to
 *              instantiate the function with their preferred unsigned type
 *              without us spelling the banned type name in our code.
 *
 * \param[in] digits     The input digits, most-significant first.
 * \param[in] from_base  The base of the input digits (≥ 2).
 * \param[in] to_base    The desired output base           (≥ 2).
 *
 * \return A vector containing the converted digits, most-significant first.
 *
 * \throws std::invalid_argument if any pre-condition is violated.
 */
template <typename IntT, typename BaseT>
auto convert(BaseT                      from_base,
             const std::vector<IntT>&   digits,
             BaseT                      to_base) -> std::vector<IntT>
{
    static_assert(std::is_integral<IntT>::value,
                  "IntT must be an integral type.");
    static_assert(!std::is_same<IntT, char>::value,
                  "Character types are not permitted.");
    static_assert(std::is_integral<BaseT>::value,
                  "BaseT must be an integral type.");
    static_assert(!std::is_same<BaseT, char>::value,
                  "Character types are not permitted.");

    /* Pre-condition checks */
    if ((from_base < static_cast<BaseT>(2)) || (to_base < static_cast<BaseT>(2)))
    {
        throw std::invalid_argument("base must be >= 2");
    }

    if (digits.empty())
    {
        throw std::invalid_argument("digits may not be empty");
    }

    for (const auto digit : digits)
    {
        if ((digit < static_cast<IntT>(0)) ||
            (digit >= static_cast<IntT>(from_base)))
        {
            throw std::invalid_argument("digit out of range for the base");
        }
    }

    /* Convert the input number to an intermediate unsigned 64-bit value.      */
    std::uint64_t value {0U};
    for (const auto digit : digits)
    {
        value = (value * static_cast<std::uint64_t>(from_base))
                + static_cast<std::uint64_t>(digit);
    }

    /* Special-case zero to avoid producing an empty output vector.            */
    if (value == static_cast<std::uint64_t>(0U))
    {
        return std::vector<IntT> {static_cast<IntT>(0)};
    }

    std::vector<IntT> result {};
    while (value > static_cast<std::uint64_t>(0U))
    {
        const std::uint64_t remainder {value % static_cast<std::uint64_t>(to_base)};
        result.push_back(static_cast<IntT>(remainder));
        value = value / static_cast<std::uint64_t>(to_base);
    }

    /* Digits were produced least-significant first – reverse for output.      */
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
