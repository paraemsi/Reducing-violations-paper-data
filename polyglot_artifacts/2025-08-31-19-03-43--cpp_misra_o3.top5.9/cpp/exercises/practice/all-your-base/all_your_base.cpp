#include "all_your_base.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

auto convert(std::int32_t from_base,
             const std::vector<std::uint32_t>& digits,
             std::int32_t to_base) -> std::vector<std::uint32_t>
{
    if((from_base <= static_cast<std::int32_t>(1)) || (to_base <= static_cast<std::int32_t>(1)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if(digits.empty())
    {
        throw std::invalid_argument("Digits vector must not be empty");
    }

    if((digits.size() > static_cast<std::size_t>(1U)) && (digits.front() == static_cast<std::uint32_t>(0U)))
    {
        throw std::invalid_argument("Leading zeros are not allowed");
    }

    for(const std::uint32_t digit : digits)
    {
        if(digit >= static_cast<std::uint32_t>(from_base))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);
    for(const std::uint32_t digit : digits)
    {
        value = (value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit);
    }

    std::vector<std::uint32_t> result;

    if(value == static_cast<std::uint64_t>(0U))
    {
        result.push_back(static_cast<std::uint32_t>(0U));
        return result;
    }

    while(value > static_cast<std::uint64_t>(0U))
    {
        const std::uint32_t remainder =
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base)); // NOLINT deliberate narrowing
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
