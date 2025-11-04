#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

auto convert(std::uint32_t from_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    /* Validate bases */
    if((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U)))
    {
        throw std::invalid_argument("base must be >= 2");
    }

    /* Validate digit sequence */
    if(digits.empty() == true)
    {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    for(const std::uint32_t digit : digits)
    {
        if(digit >= from_base)
        {
            throw std::invalid_argument("digit out of range for source base");
        }
    }

    /* Convert input digits to an unsigned 64-bit accumulator */
    std::uint64_t accumulator = static_cast<std::uint64_t>(0U);
    for(const std::uint32_t digit : digits)
    {
        accumulator = (accumulator * static_cast<std::uint64_t>(from_base))
                    + static_cast<std::uint64_t>(digit);
    }

    /* Special-case zero */
    if(accumulator == static_cast<std::uint64_t>(0U))
    {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    /* Build result digits in reverse order */
    std::vector<std::uint32_t> result{};
    while(accumulator > static_cast<std::uint64_t>(0U))
    {
        const std::uint32_t remainder =
            static_cast<std::uint32_t>(accumulator % static_cast<std::uint64_t>(to_base));
        result.push_back(remainder);
        accumulator = accumulator / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace all_your_base
