#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

auto convert(const std::vector<std::uint32_t>& digits,
             std::uint32_t from_base,
             std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    if((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U)))
    {
        throw std::invalid_argument("base must be >= 2");
    }

    if(digits.empty())
    {
        throw std::invalid_argument("digits must not be empty");
    }

    std::vector<std::uint32_t> trimmed_digits{};
    trimmed_digits.reserve(digits.size());
    bool significant_found{false};

    for(const std::uint32_t digit : digits)
    {
        if(digit >= from_base)
        {
            throw std::invalid_argument("digit out of range for input base");
        }

        if((digit != static_cast<std::uint32_t>(0U)) || (significant_found))
        {
            trimmed_digits.push_back(digit);
            significant_found = true;
        }
    }

    if(trimmed_digits.empty())
    {
        return {static_cast<std::uint32_t>(0U)};
    }

    std::uint64_t value{0U};

    for(const std::uint32_t digit : trimmed_digits)
    {
        value = (value * static_cast<std::uint64_t>(from_base)) +
                static_cast<std::uint64_t>(digit);
    }

    std::vector<std::uint32_t> output_digits{};

    while(value > static_cast<std::uint64_t>(0U))
    {
        const std::uint32_t remainder =
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base));
        output_digits.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(output_digits.begin(), output_digits.end());

    return output_digits;
}


}  // namespace all_your_base
