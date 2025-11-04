#include "all_your_base.h"

#include <vector>
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t from_base,
                                   const std::vector<std::uint32_t>& digits,
                                   std::uint32_t to_base)
{
    /* Validate bases */
    if((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U)))
    {
        throw std::invalid_argument("Bases must be at least 2");
    }

    /* Validate digits list and compute the numeric value in a wide type */
    if(digits.empty() == true)
    {
        throw std::invalid_argument("No digits provided");
    }
    if((digits.size() > static_cast<std::size_t>(1U)) &&
       (digits.front() == static_cast<std::uint32_t>(0U)))
    {
        throw std::invalid_argument("Leading zeros are not permitted");
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);
    for(const std::uint32_t digit : digits)
    {
        if(digit >= from_base)
        {
            throw std::invalid_argument("Digit out of range for input base");
        }

        value = (value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit);
    }

    /* Handle the case of the value zero */
    if(value == static_cast<std::uint64_t>(0U))
    {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    /* Convert to the target base */
    std::vector<std::uint32_t> result{};
    while(value != static_cast<std::uint64_t>(0U))
    {
        const std::uint32_t remainder = static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    /* Digits were generated least-significant first */
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
