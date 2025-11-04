#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& input_digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>
{
    /* Validate bases */
    if ((input_base < static_cast<std::uint32_t>(2U)) ||
        (output_base < static_cast<std::uint32_t>(2U)))
    {
        throw std::invalid_argument("base must be >= 2");
    }

    /* Validate digits */
    if (input_digits.empty() == true)
    {
        throw std::invalid_argument("empty digit vector");
    }

    std::uint64_t value {0U};

    for (std::uint32_t digit : input_digits)
    {
        if (digit >= input_base)
        {
            throw std::invalid_argument("digit out of range for input base");
        }

        value = (value * static_cast<std::uint64_t>(input_base)) +
                static_cast<std::uint64_t>(digit);
    }

    /* Special handling for zero – return a single zero digit as required by
     * the exercise tests. */
    if (value == static_cast<std::uint64_t>(0U))
    {
        return {static_cast<std::uint32_t>(0U)};
    }

    /* Convert to output base */
    std::vector<std::uint32_t> result {};

    while (value > static_cast<std::uint64_t>(0U))
    {
        const std::uint32_t remainder
        {
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(output_base))
        };
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    /* Re-order to most significant digit first */
    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace all_your_base
