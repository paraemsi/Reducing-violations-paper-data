#include "all_your_base.h"

#include <algorithm>   // for std::reverse

namespace all_your_base {

auto convert(const std::vector<std::uint32_t>& digits,
             std::uint32_t from_base,
             std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    if((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if(digits.empty())
    {
        throw std::invalid_argument("Input digit sequence may not be empty");
    }

    for(const std::uint32_t digit : digits)
    {
        if(digit >= from_base)
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Detect zero early and return the canonical form {0}. */
    bool is_zero {true};
    for(const std::uint32_t digit : digits)
    {
        if(digit != static_cast<std::uint32_t>(0U))
        {
            is_zero = false;
            break;
        }
    }

    if(is_zero)
    {
        return {static_cast<std::uint32_t>(0U)};
    }

    /* Working copy so we can perform the repeated-division algorithm in place. */
    std::vector<std::uint32_t> work_digits {digits};
    std::vector<std::uint32_t> result {};

    while(!work_digits.empty())
    {
        std::vector<std::uint32_t> new_digits {};
        std::uint64_t remainder {0U};

        for(const std::uint32_t digit : work_digits)
        {
            std::uint64_t accumulator {(remainder * static_cast<std::uint64_t>(from_base))
                                        + static_cast<std::uint64_t>(digit)};
            std::uint32_t quotient_digit {static_cast<std::uint32_t>(
                                            accumulator / static_cast<std::uint64_t>(to_base))};
            remainder = accumulator % static_cast<std::uint64_t>(to_base);

            if((!new_digits.empty()) || (quotient_digit != static_cast<std::uint32_t>(0U)))
            {
                new_digits.push_back(quotient_digit);
            }
        }

        result.push_back(static_cast<std::uint32_t>(remainder));
        work_digits = std::move(new_digits);
    }

    /* Digits were produced least-significant first; reverse to canonical order. */
    std::reverse(result.begin(), result.end());

    return result;
}


}  // namespace all_your_base
