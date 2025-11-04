#include "all_your_base.h"

namespace all_your_base {

auto convert(digit_t                     from_base,
             const std::vector<digit_t>& digits,
             digit_t                     to_base) -> std::vector<digit_t>
{
    if ((from_base < static_cast<digit_t>(2)) || (to_base < static_cast<digit_t>(2)))
    {
        throw std::invalid_argument("Bases must be greater than or equal to 2");
    }

    if (digits.empty())
    {
        throw std::invalid_argument("Digit list must not be empty");
    }

    for (const auto digit : digits)
    {
        if (digit >= from_base)
        {
            throw std::invalid_argument("Digit out of range for source base");
        }
    }

    /* Convert to an intermediate value held in 64-bit unsigned storage */
    std::uint64_t value{0U};

    for (const auto digit : digits)
    {
        value = (value * static_cast<std::uint64_t>(from_base))
              + static_cast<std::uint64_t>(digit);
    }

    if (value == static_cast<std::uint64_t>(0U))
    {
        return {static_cast<digit_t>(0U)};
    }

    /* Convert the intermediate value to the requested target base */
    std::vector<digit_t> result{};

    while (value > static_cast<std::uint64_t>(0U))
    {
        const digit_t remainder =
            static_cast<digit_t>(value % static_cast<std::uint64_t>(to_base));
        result.insert(result.begin(), remainder); /* prepend to keep MSB first */
        value = value / static_cast<std::uint64_t>(to_base);
    }

    return result;
}

}  // namespace all_your_base
