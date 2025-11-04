#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

auto convert(std::uint32_t in_base,
             std::vector<std::uint32_t> const& in_digits,
             std::uint32_t out_base) -> std::vector<std::uint32_t>
{
    /* Preconditions */
    if ((in_base <= static_cast<std::uint32_t>(1U)) ||
        (out_base <= static_cast<std::uint32_t>(1U)))
    {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    for (auto const digit : in_digits)
    {
        if (digit >= in_base)
        {
            throw std::invalid_argument("Digit outside input base range");
        }
    }

    /* Special-case: empty input encodes the value 0 and must yield an empty
     *               digit sequence in the output base. */
    if (in_digits.empty() != false)
    {
        return {}; /* empty vector represents zero */
    }

    /* Convert input digits to an unsigned 64-bit accumulator */
    std::uint64_t value {static_cast<std::uint64_t>(0U)};
    for (auto const digit : in_digits)
    {
        value =
            (value * static_cast<std::uint64_t>(in_base)) +
            static_cast<std::uint64_t>(digit);
    }

    /* Conversion to the output base */
    if (value == static_cast<std::uint64_t>(0U))
    {
        return {}; /* zero is encoded as an empty digit sequence */
    }

    std::vector<std::uint32_t> out_digits {};
    while (value > static_cast<std::uint64_t>(0U))
    {
        std::uint32_t const remainder {
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(out_base))};
        out_digits.push_back(remainder);
        value = value / static_cast<std::uint64_t>(out_base);
    }

    /* The algorithm produced least-significant-digit first, reverse it. */
    std::reverse(out_digits.begin(), out_digits.end());

    return out_digits;
}

}  // namespace all_your_base
