#include "all_your_base.h"
#if 0
#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

using digit_t = std::int32_t;

auto convert(const std::vector<digit_t>& digits,
             std::int32_t from_base,
             std::int32_t to_base) -> std::vector<digit_t>
{
    /* Validate bases */
    if ((from_base <= 1) || (to_base <= 1))
    {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    /* Validate digits */
    for (digit_t d : digits)
    {
        if ((d < 0) || (d >= from_base))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Handle zero value */
    bool is_zero = true;
    for (digit_t d : digits)
    {
        if (d != 0)
        {
            is_zero = false;
            break;
        }
    }
    if ((digits.empty()) || (is_zero))
    {
        return { static_cast<digit_t>(0) };
    }

    /* Convert using repeated division to avoid overflow */
    std::vector<digit_t> working_digits = digits;

    /* Remove leading zeros that may be present in the input */
    while ((!working_digits.empty()) && (working_digits.front() == 0))
    {
        working_digits.erase(working_digits.begin());
    }
    if (working_digits.empty())
    {
        return { static_cast<digit_t>(0) };
    }

    std::vector<digit_t> result;

    while (!working_digits.empty())
    {
        std::vector<digit_t> next_digits;
        std::uint64_t       remainder = 0U;

        for (digit_t d : working_digits)
        {
            std::uint64_t accumulator =
                (remainder * static_cast<std::uint64_t>(from_base))
                + static_cast<std::uint64_t>(d);

            digit_t quotient_digit =
                static_cast<digit_t>(accumulator
                                     / static_cast<std::uint64_t>(to_base));

            remainder = accumulator % static_cast<std::uint64_t>(to_base);

            if ((!next_digits.empty()) || (quotient_digit != 0))
            {
                next_digits.push_back(quotient_digit);
            }
        }

        result.push_back(static_cast<digit_t>(remainder));
        working_digits = next_digits;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
#endif
