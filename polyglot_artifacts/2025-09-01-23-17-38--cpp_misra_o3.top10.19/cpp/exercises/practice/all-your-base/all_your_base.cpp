#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {


#if 0

auto convert(Base from_base,
             const std::vector<Digit>& input_digits,
             Base to_base) -> std::vector<Digit>
{
    /* Validate bases */
    if ((from_base < static_cast<Base>(2)) ||
        (to_base   < static_cast<Base>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate digits */
    for (Digit d : input_digits)
    {
        if ((d < static_cast<Digit>(0)) || (d >= static_cast<Digit>(from_base)))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Treat empty input as zero */
    if (input_digits.empty())
    {
        return std::vector<Digit>{static_cast<Digit>(0)};
    }

    /* Convert input to an unsigned 64-bit value */
    Wide value {static_cast<Wide>(0U)};
    for (Digit d : input_digits)
    {
        value = (value * static_cast<Wide>(from_base))
              + static_cast<Wide>(d);
    }

    /* Produce output digits in the target base */
    std::vector<Digit> output {};

    if (value == static_cast<Wide>(0U))
    {
        output.push_back(static_cast<Digit>(0));
    }
    else
    {
        while (value > static_cast<Wide>(0U))
        {
            Digit remainder =
                static_cast<Digit>(value % static_cast<Wide>(to_base));
            output.push_back(remainder);
            value = value / static_cast<Wide>(to_base);
        }
        std::reverse(output.begin(), output.end());
    }

    return output;
}
#endif

}  // namespace all_your_base
