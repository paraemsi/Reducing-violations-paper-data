#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

auto convert(std::uint32_t from_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    /* Validate bases */
    if ((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty() == true)
    {
        throw std::invalid_argument("Input digits may not be empty");
    }

    /* Validate digits and compute combined value */
    std::uint64_t value = static_cast<std::uint64_t>(0U);

    for (const std::uint32_t digit : digits)
    {
        if (digit >= from_base)
        {
            throw std::invalid_argument("Digit out of range for input base");
        }

        value = (value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit);
    }

    std::vector<std::uint32_t> output{};

    if (value == static_cast<std::uint64_t>(0U))
    {
        output.push_back(static_cast<std::uint32_t>(0U));
        return output;
    }

    while (value > static_cast<std::uint64_t>(0U))
    {
        output.push_back(static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base)));
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(output.begin(), output.end());
    return output;
}

}  // namespace all_your_base
