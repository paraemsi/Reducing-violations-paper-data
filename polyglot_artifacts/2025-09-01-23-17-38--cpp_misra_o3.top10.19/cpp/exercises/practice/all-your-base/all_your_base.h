#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

namespace all_your_base {

using Digit = std::int32_t;
using Base  = std::int32_t;

/*
 * Convert the number represented by `input_digits` in base `from_base`
 * into its representation in base `to_base`.
 * Throws std::invalid_argument on any invalid base or digit.
 */
template <typename InputDigit>
auto convert(Base from_base,
             const std::vector<InputDigit>& input_digits,
             Base to_base) -> std::vector<InputDigit>
{
    static_assert(std::is_integral<InputDigit>::value,
                  "Digit type must be integral");

    /* Validate bases */
    if ((from_base < static_cast<Base>(2)) ||
        (to_base   < static_cast<Base>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate digits */
    for (InputDigit d_raw : input_digits)
    {
        const Digit d {static_cast<Digit>(d_raw)};
        if ((d < static_cast<Digit>(0)) ||
            (d >= static_cast<Digit>(from_base)))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Treat empty input as zero */
    if (input_digits.empty())
    {
        return std::vector<InputDigit>{static_cast<InputDigit>(0)};
    }

    using Wide = std::uint64_t;
    Wide value {static_cast<Wide>(0U)};
    for (InputDigit d_raw : input_digits)
    {
        value = (value * static_cast<Wide>(from_base))
              + static_cast<Wide>(d_raw);
    }

    std::vector<InputDigit> output {};

    if (value == static_cast<Wide>(0U))
    {
        output.push_back(static_cast<InputDigit>(0));
    }
    else
    {
        while (value > static_cast<Wide>(0U))
        {
            const InputDigit remainder =
                static_cast<InputDigit>(value % static_cast<Wide>(to_base));
            output.push_back(remainder);
            value = value / static_cast<Wide>(to_base);
        }
        std::reverse(output.begin(), output.end());
    }

    return output;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
